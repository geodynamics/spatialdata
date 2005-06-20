// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

#include "Geoid.h" // implementation of class methods

#include <math.h> // USES sin(), cos(), atan(), sqrt(), M_PI_2

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

#include "journal/debug.h" // USES journal::debug_t

// ----------------------------------------------------------------------
namespace spatialdata {
  class WGSConstants;
}; // namespace spatialdata

class spatialdata::WGSConstants {
public:

  static const double E2;
  static const double AE;
  static const double GEQT;
  static const double K;
  static const double GM;
  static const double OMEGA;
  static const double RF;
}; // WGSConstants
const double spatialdata::WGSConstants::GM = 0.3986004418E+15;
const double spatialdata::WGSConstants::AE = 6378137.0;
const double spatialdata::WGSConstants::OMEGA = 7.292115E-05;
const double spatialdata::WGSConstants::RF = 298.257223563;
const double spatialdata::WGSConstants::E2 = 0.00669437999013;
const double spatialdata::WGSConstants::GEQT = 9.7803253359;
const double spatialdata::WGSConstants::K = 0.00193185265246;

// ----------------------------------------------------------------------
const int spatialdata::Geoid::_NUMMODES = 360;
#include "data/egm96.dat"
#include "data/corrcoef.dat"

// ----------------------------------------------------------------------
// Default constructor.
spatialdata::Geoid::Geoid(void) :
  _pHC(0),
  _pHS(0),
  _pCC(0),
  _pCS(0),
  _pRoots(0),
  _pInvRoots(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::Geoid::~Geoid(void)
{ // destructor
  delete[] _pHC; _pHC = 0;
  delete[] _pHS; _pHS = 0;
  delete[] _pCC; _pCC = 0;
  delete[] _pCS; _pCS = 0;
  delete[] _pRoots; _pRoots = 0;
  delete[] _pInvRoots; _pInvRoots = 0;
} // destructor

// ----------------------------------------------------------------------
// Initialize
void
spatialdata::Geoid::initialize(void)
{ // initialize
  _setHCHS();
  _setCCCS();
  _calcRoots();
} // initialize

// ----------------------------------------------------------------------
// Compute elevation with respect to WGS ellipsoid relative to
//  elevation with respect to MSL.
double
spatialdata::Geoid::elevation(const double lon,
			      const double lat) const
{ // elevation
  // compute the geocentric latitude, geocentric radius, and normal gravity
  double latGeocent = 0.0;
  double radiusGeocent = 0.0;
  double normalGrav = 0.0;
  _geocentricLat(&latGeocent, &radiusGeocent, &normalGrav, lon, lat);
  latGeocent = M_PI_2 - latGeocent;

  const int coefSize = (_NUMMODES+1)*(_NUMMODES+2)/2;
  double* pLegCoef = new double[coefSize];
  for (int i=0; i < coefSize; ++i)
    pLegCoef[i] = 0.0;

  const int legSize = _NUMMODES+1;
  double* pLegFn = new double[legSize];
  for (int j=0; j < legSize; ++j) {
    const int order = j;
    _calcLegFn(&pLegFn, order, latGeocent);
    for (int i=j; i < legSize; ++i) {
      const int iCoef = i*(i+1)/2 + order;
      pLegCoef[iCoef] = pLegFn[i];
    } // for
  } // for
  delete[] pLegFn; pLegFn = 0;

  double* pCosML = new double[_NUMMODES+1];
  double* pSinML = new double[_NUMMODES+1];
  _calcML(&pCosML, &pSinML, lon);

  const double elev = 
    _calcElev(pLegCoef, pCosML, pSinML, radiusGeocent, normalGrav);

  delete[] pCosML; pCosML = 0;
  delete[] pSinML; pSinML = 0;

  return elev;
} // elevation

// ----------------------------------------------------------------------
// 
double
spatialdata::Geoid::_calcElev(const double* pLegCoef,
			      const double* pCosML,
			      const double* pSinML,
			      const double radiusGeocent,
			      const double normalGrav) const
{ // _calcElev
  FIREWALL(0 != _pHC);
  FIREWALL(0 != _pHS);
  FIREWALL(0 != _pCC);
  FIREWALL(0 != _pCS);

  const double ar = WGSConstants::AE / radiusGeocent;
  double arCoef = ar;
  double ac = 0.0;
  double a = 0.0;

  int k = 2;
  const int numModes = _NUMMODES;
  for (int iMode=1; iMode < numModes; ++iMode) {
    arCoef *= ar;
    ++k;
    double sum = pLegCoef[k]*_pHC[k];
    double sumc = pLegCoef[k]*_pCC[k];
    for (int m=0; m <= iMode; ++m) {
      ++k;
      const double tmpc = _pCC[k]*pCosML[m] + _pCS[k]*pSinML[m];
      const double tmp = _pHC[k]*pCosML[m] + _pHS[k]*pSinML[m];
      sumc += pLegCoef[k]*tmpc;
      sum += pLegCoef[k]*tmp;
    } // for
    ac += sumc;
    a += sum*arCoef;
  } // for
  ac += _pCC[0] + pLegCoef[1]*_pCC[1] + 
    pLegCoef[2]*(_pCC[2]*pCosML[0]+_pCS[2]*pSinML[0]);
  const double haco = ac / 100.0;
  const double elev = a*WGSConstants::GM / (normalGrav*radiusGeocent) +
    haco - 0.53;

  return elev;
} // _calcElev

// ----------------------------------------------------------------------
// Compute geocentric latitude, geocentric radius and normal gravity
void
spatialdata::Geoid::_geocentricLat(double* pLatGeocent,
				   double* pRadiusGeocent,
				   double* pNormalGrav,
				   const double lon,
				   const double lat) const
{ // _geocentricLat
  FIREWALL(0 != pLatGeocent);
  FIREWALL(0 != pRadiusGeocent);
  FIREWALL(0 != pNormalGrav);

  const double elevRef = 0.0;

  const double e2 = WGSConstants::E2;
  const double ae = WGSConstants::AE;
  const double geqt = WGSConstants::GEQT;
  const double k = WGSConstants::K;

  const double sinlat2 = sin(lat)*sin(lat);
  const double f1 = sqrt(1.0-e2*sinlat2);

  const double n = ae / f1;
  const double t2 = (n + elevRef) * cos(lat);
  const double x = t2 * cos(lon);
  const double y = t2 * sin(lon);
  const double z = (n*(1-e2)+elevRef)*sin(lat);

  *pLatGeocent = atan(z/sqrt(x*x+y*y));
  *pRadiusGeocent = sqrt(x*x + y*y + z*z);
  *pNormalGrav = geqt*(1.0 + k*sinlat2) / f1;
} // _geocentricLat

// ----------------------------------------------------------------------
// ????
void
spatialdata::Geoid::_calcML(double** ppCosML,
			    double** ppSinML,
			    const double lon) const
{ // _calcML
  FIREWALL(0 != *ppSinML);
  FIREWALL(0 != *ppCosML);

  const double sinLon = sin(lon);
  const double cosLon = cos(lon);

  const int size = _NUMMODES + 1;

  double* pVals = *ppSinML;
  pVals[0] = sinLon;
  pVals[1] = 2.0*sinLon*cosLon;
  for (int i=2; i < size; ++i)
    pVals[i] = 2.0*cosLon * pVals[i-1] - pVals[i-2];

  pVals = *ppCosML;
  pVals[0] = cosLon;
  pVals[1] = 2.0*cosLon*cosLon - 1.0;
  for (int i=2; i < size; ++i)
    pVals[i] = 2.0*cosLon * pVals[i-1] - pVals[i-2];  
} // _calcML

// ----------------------------------------------------------------------
// ????
void
spatialdata::Geoid::_setCCCS(void)
{ // _setCCCS
  const int ccSize = _NUMMODES*(_NUMMODES+1)/2 + _NUMMODES+1;

  delete[] _pCC; _pCC = new double[ccSize];
  for (int i=0, j=0; i < ccSize; ++i, j+=2) {
    FIREWALL(j < 2*65341);
    _pCC[i] = _CORRCOEF[j];
    }
  
  const int csSize = ccSize;
  delete[] _pCS; _pCS = new double[csSize];
  for (int i=0, j=1; i < csSize; ++i, j+=2) {
    FIREWALL(j < 2*65341);
    _pCS[i] = _CORRCOEF[j];
  }
} // _setCCCS
  
// ----------------------------------------------------------------------
// ????
void
spatialdata::Geoid::_setHCHS(void)
{ // _setHCHS
  const int hcSize = _NUMMODES*(_NUMMODES+1)/2 + _NUMMODES+1;
  delete[] _pHC; _pHC = new double[hcSize];
  for (int i=3, j=0; i < hcSize; ++i, j+=2)
    _pHC[i] = _EGM96[j];

  const int hsSize = hcSize;
  delete[] _pHS; _pHS = new double[hsSize];
  for (int i=3, j=1; i < hsSize; ++i, j+=2)
    _pHS[i] = _EGM96[j];
  
  const double j2 = 0.108262982131E-02;
  const double j4 = -.237091120053E-05;
  const double j6 = 0.608346498882E-08;
  const double j8 = -0.142681087920E-10;
  const double j10 = 0.121439275882E-13;

  _pHC[3] += j2/sqrt(5.0);
  _pHC[10] += j4/3.0;
  _pHC[21] += j6/sqrt(13.0);
  _pHC[36] += j8/sqrt(17.0);
  _pHC[55] += j10/sqrt(21.0);
} // _setHCHS

// ----------------------------------------------------------------------
// ????
void
spatialdata::Geoid::_calcRoots(void)
{ // _calcRoots
  const int size = 2 * _NUMMODES + 1;
  
  delete[] _pRoots; _pRoots = new double[size];
  delete[] _pInvRoots; _pInvRoots = new double[size];
  for (int i=0; i < size; ++i) {
    const double val = sqrt(i+1);
    _pRoots[i] = val;
    _pInvRoots[i] = 1.0 / val;
  } // for
} // _calcRoots

// ----------------------------------------------------------------------
// Compute normalized legendre function.
void
spatialdata::Geoid::_calcLegFn(double** ppLegFn,
			       const int order,
			       const double latGeocent) const
{ // _calcLegFn
  FIREWALL(0 != ppLegFn);
  FIREWALL(0 != *ppLegFn);

  double* pLegFn = *ppLegFn;
  const int legSize = _NUMMODES+1;

  const int order1 = order + 1;
  const int order2 = order + 2;
  const int order3 = order + 3;

  const double cosLat = cos(latGeocent);
  const double sinLat = sin(latGeocent);

  double* pRlnn = new double[legSize];
  pRlnn[0] = 1.0;
  pRlnn[1] = sinLat*_pRoots[2];
  for (int i=2; i < order1; ++i) {
    const int i2 = 2*i;
    pRlnn[i] = _pRoots[i2] * _pInvRoots[i2-1] * sinLat * pRlnn[i-1];
  } // for
  
  if (0 == order) {
    pLegFn[0] = 1.0;
    pLegFn[1] = cosLat*_pRoots[2];
  } else if (1 == order) {
    pLegFn[1] = pRlnn[1];
    pLegFn[2] = _pRoots[4]*cosLat*pLegFn[1];
  } // if
  
  pLegFn[order1-1] = pRlnn[order1-1];
  if (order2-1 < legSize) {
    pLegFn[order2-1] = _pRoots[order1*2] * cosLat * pLegFn[order1-1];
    for (int i=order2; i < legSize; ++i) {
      if (order > 1 || i > order+1) {
	const int i2 = 2*i;
	pLegFn[i] = _pRoots[i2] * _pInvRoots[i+order-1] * _pInvRoots[i-order-1] *
	  (_pRoots[i2-2] * cosLat*pLegFn[i-1] - 
	   _pRoots[i+order-2] * _pRoots[i-order-2] * 
	   _pInvRoots[i2-4] * pLegFn[i-2]);
      } // if
    } // for
  } // if
} // _calcLegFn

// version
// $Id: Geoid.cc,v 1.1 2005/06/19 19:23:22 baagaard Exp $

// End of file 
