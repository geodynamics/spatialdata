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

#include "GeoLocalConverter.h" // implementation of class methods

#include "GeoCoordSys.h" // USES GeoCoordSys
#include "GeoCSConverter.h" // USES GeoCSConverter

extern "C" {
#include "proj_api.h" // USES PROJ4
};

#include <math.h> // USES M_PI, sin(), cos()
#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
// Default constructor
spatialdata::GeoLocalConverter::GeoLocalConverter(const GeoCoordSys& cs) :
  _originLon(0),
  _originLat(0),
  _originElev(0),
  _originX(0),
  _originY(0),
  _originZ(0),
  _localOrientation(0),
  _csSrc(cs)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::GeoLocalConverter::~GeoLocalConverter(void)
{ // destructor
  delete[] _localOrientation; _localOrientation = 0;
} // destructor

// ----------------------------------------------------------------------
// Set origin of local cartesian coordinate system.
void
spatialdata::GeoLocalConverter::localOrigin(const double lon,
					    const double lat,
					    const double elev)
{ // localOrigin
  _originLon = lon;
  _originLat = lat;
  _originElev = elev;

  const int numCoords = 3;
  const int numLocs = 2;
  double* pCoords = new double[numCoords*numLocs];

  // Convert origin and point above origin to WGS84
  const double degToRad = M_PI / 180.0;
  // origin
  pCoords[0] = lon * degToRad;
  pCoords[1] = lat * degToRad;
  pCoords[2] = elev;
  // point above origin
  const double delev = 25.0e+3;
  pCoords[3] = pCoords[0];
  pCoords[4] = pCoords[1];
  pCoords[5] = elev + delev;
  GeoCoordSys cs(_csSrc);
  _geoToWGS84(&pCoords, numLocs, &cs);

  // save longitude in WGS84
  const double lonWGS84 = pCoords[0];

  // convert origin and point above origin to ECEF
  _wgs84ToECEF(&pCoords, numLocs, &cs);

  // Create unit vector for local +z direction; local +z direction is
  // normal to Earth's surface at origin; use point above origin to
  // find normal to Earth's surface at origin; make unit vector
  const double dx = pCoords[3] - pCoords[0];
  const double dy = pCoords[4] - pCoords[1];
  const double dz = pCoords[5] - pCoords[2];
  const double mag = sqrt(dx*dx + dy*dy + dz*dz);
  const double z0 = dx / mag;
  const double z1 = dy / mag;
  const double z2 = dz / mag;

  // Create unit vector for local +x direction; local +x direction is
  // in ECEF xy plane, parallel to lines of equal latitude
  const double x0 = -sin(lonWGS84);
  const double x1 = cos(lonWGS84);
  const double x2 = 0.0;

  // Create unit vector for local +y direction; local +y direction is
  // cross product of z and x directions
  const double y0 = z1*x2 - x1*z2;
  const double y1 = z2*x0 - x2*z0;
  const double y2 = z0*x1 - x0*z1;

  delete[] _localOrientation; _localOrientation = new double[9];
  _localOrientation[0] = x0;
  _localOrientation[1] = x1;
  _localOrientation[2] = x2;
  _localOrientation[3] = y0;
  _localOrientation[4] = y1;
  _localOrientation[5] = y2;
  _localOrientation[6] = z0;
  _localOrientation[7] = z1;
  _localOrientation[8] = z2;

  _originX = 0.0;
  _originY = 0.0;
  _originZ = 0.0;

  _ecefToLocal(&pCoords, numLocs, &cs);

  _originX = pCoords[0];
  _originY = pCoords[1];
  _originZ = pCoords[2];


  delete[] pCoords; pCoords = 0;
} // localOrigin

// ----------------------------------------------------------------------
// Convert coordinates from geographic coordinate system to local
// cartesian coordinate system.
void
spatialdata::GeoLocalConverter::convert(double** ppDest,
					const int numLocs,
					const double elevToMeters,
					const bool invert) const
{ // convert
  FIREWALL(0 != ppDest);
  FIREWALL( (0 != *ppDest && 0 < numLocs) ||
	    (0 == *ppDest && 0 == numLocs) );
  FIREWALL(0 != _csSrc.coordsys());

  GeoCoordSys cs(_csSrc);

  if (pj_is_latlong(_csSrc.coordsys())) {
    const double degToRad = M_PI / 180.0;
    for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
      (*ppDest)[index++] *= degToRad; // lon
      (*ppDest)[index++] *= degToRad; // lat
      (*ppDest)[index++] *= elevToMeters; // convert elev to m
    } // for
  } // if

  if (!invert) {
    _geoToWGS84(ppDest, numLocs, &cs);
    _wgs84ToECEF(ppDest, numLocs, &cs);
    _ecefToLocal(ppDest, numLocs, &cs);
  } else {
    _ecefToLocal(ppDest, numLocs, &cs, invert); 
    _wgs84ToECEF(ppDest, numLocs, &cs, invert);
    _geoToWGS84(ppDest, numLocs, &cs, invert);
  } // else
} // convert

// ----------------------------------------------------------------------
// Convert geographic coordinates to lat/lon with WGS64 datum and
// ellipsoid.
void
spatialdata::GeoLocalConverter::_geoToWGS84(double** const ppCoords,
					    const int numLocs,
					    GeoCoordSys* pCS,
					    const bool invert) const
{ // _geoToWGS84
  FIREWALL(0 != ppCoords);
  FIREWALL(0 != pCS);

  GeoCoordSys csDest;
  csDest.projection("latlong");
  csDest.ellipsoid("WGS84");
  csDest.datumHoriz("WGS84");
  csDest.datumVert("WGS84 ellipsoid");
  csDest.units("m");
  csDest.initialize();

  if ( !(csDest == *pCS) ) {
    const GeoCoordSys* pCSTo = (!invert) ? &csDest : pCS;
    const GeoCoordSys* pCSFrom = (!invert) ? pCS : &csDest;
    GeoCSConverter csConverter(*pCSTo, *pCSFrom);
    const bool isDeg = false;
    csConverter.convert(ppCoords, numLocs, isDeg);
  } // if
  *pCS = csDest;
} // _geoToWGS84

// ----------------------------------------------------------------------
// Convert geographic coordinates in lat/lon with WGS64 datum and
//  ellipsoid to ECEF cartesian coordinates.
void
spatialdata::GeoLocalConverter::_wgs84ToECEF(double** const ppCoords,
					     const int numLocs,
					     GeoCoordSys* pCS,
					     const bool invert) const
{ // _wgs84ToECEF
  FIREWALL(0 != ppCoords);
  FIREWALL(0 != pCS);

  GeoCoordSys csDest;
  csDest.projection("geocent");
  csDest.ellipsoid("WGS84");
  csDest.datumHoriz("WGS84");
  csDest.datumVert("WGS84 ellipsoid");
  csDest.units("m");
  csDest.initialize();

  const GeoCoordSys* pCSTo = (!invert) ? &csDest : pCS;
  const GeoCoordSys* pCSFrom = (!invert) ? pCS : &csDest;
  GeoCSConverter csConverter(*pCSTo, *pCSFrom);

  const bool isDeg = false;
  csConverter.convert(ppCoords, numLocs, isDeg);
  *pCS = csDest;
} // _wgs84ToECEF

// ----------------------------------------------------------------------
// Convert ECEF cartesian coordinates to local cartesian coordinates.
void
spatialdata::GeoLocalConverter::_ecefToLocal(double** const ppCoords,
					     const int numLocs,
					     GeoCoordSys* pCS,
					     const bool invert) const
{ // _ecefToLocal
  FIREWALL(0 != ppCoords);
  FIREWALL(0 != pCS);

  if (!invert) {
    for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
      const double xOld = (*ppCoords)[index  ];
      const double yOld = (*ppCoords)[index+1];
      const double zOld = (*ppCoords)[index+2];
      (*ppCoords)[index++] = 
	_localOrientation[0]*xOld +
	_localOrientation[1]*yOld +
	_localOrientation[2]*zOld - _originX;
      (*ppCoords)[index++] = 
	_localOrientation[3]*xOld +
	_localOrientation[4]*yOld +
	_localOrientation[5]*zOld - _originY;
      (*ppCoords)[index++] = 
	_localOrientation[6]*xOld +
	_localOrientation[7]*yOld +
	_localOrientation[8]*zOld - _originZ;
    } // for
  } else {
    for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
      // add origin to old to invert
      const double xOld = (*ppCoords)[index  ] + _originX;
      const double yOld = (*ppCoords)[index+1] + _originY;
      const double zOld = (*ppCoords)[index+2] + _originZ;
      // multiply by transpose of direction cosines to invert
      (*ppCoords)[index++] = 
	_localOrientation[0]*xOld +
	_localOrientation[3]*yOld +
	_localOrientation[6]*zOld;
      (*ppCoords)[index++] = 
	_localOrientation[1]*xOld +
	_localOrientation[4]*yOld +
	_localOrientation[7]*zOld;
      (*ppCoords)[index++] = 
	_localOrientation[2]*xOld +
	_localOrientation[5]*yOld +
	_localOrientation[8]*zOld;
    } // for
  } // else
} // _ecefToLocal

// version
// $Id: GeoLocalConverter.cc,v 1.5 2005/07/02 00:23:25 baagaard Exp $

// End of file 
