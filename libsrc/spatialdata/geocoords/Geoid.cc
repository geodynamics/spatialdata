// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "Geoid.hh" // implementation of class methods

#include <math.h> // USES sin(), cos(), atan(), sqrt(), M_PI_2

#include <fstream> // USES std::ifstream

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

#if defined(WORDS_BIGENDIAN)
#define NATIVE_BIG_ENDIAN
#else
#define NATIVE_LITTLE_ENDIAN
#endif


#define MAKEDATAFILE(file) #file
#define SETDATAFILE(dir,file) MAKEDATAFILE(dir/file)

// ----------------------------------------------------------------------
const double spatialdata::geocoords::Geoid::_south = -90.0 * M_PI / 180.0;
const double spatialdata::geocoords::Geoid::_north = 90.0 * M_PI / 180.0;
const double spatialdata::geocoords::Geoid::_west = 0.0 * M_PI / 180.0;
const double spatialdata::geocoords::Geoid::_east = 360.0 * M_PI / 180.0;
const double spatialdata::geocoords::Geoid::_dLat = 0.25 * M_PI / 180.0;
const double spatialdata::geocoords::Geoid::_dLon = 0.25 * M_PI / 180.0;

const int spatialdata::geocoords::Geoid::_numInterp = 4;
const int spatialdata::geocoords::Geoid::_numExtraEdge = 
  spatialdata::geocoords::Geoid::_numInterp;
const int spatialdata::geocoords::Geoid::_numGridEW = 
  1440 + 2 * spatialdata::geocoords::Geoid::_numExtraEdge;
const int spatialdata::geocoords::Geoid::_numGridNS = 721;

const char* spatialdata::geocoords::Geoid::_filename =
  SETDATAFILE(DATADIR,ww15mgh.dac);

// ----------------------------------------------------------------------
// Default constructor.
spatialdata::geocoords::Geoid::Geoid(void) :
  _pGridVals(0),
  _initialized(false)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::Geoid::~Geoid(void)
{ // destructor
  delete[] _pGridVals; _pGridVals = 0;
} // destructor

// ----------------------------------------------------------------------
// Compute elevation with respect to WGS ellipsoid relative to
//  elevation with respect to MSL.
double
spatialdata::geocoords::Geoid::elevation(const double lon,
					 const double lat) const
{ // elevation
  /* Use EGM96 to get difference between MSL and geoid.
   *
   * Lemoine, F.G., S.C. Kenyon, J.K. Factor, R.G. Trimmer,
   * N.K. Pavlis, D.S. Chinn, C.M. Cox, S.M. Klosko, S.B. Luthcke,
   * M.H. Torrence, Y.M. Wang, R.G. Williamson, E.C. Pavlis, R.H. Rapp
   * and T.R. Olson, The Development of the Joint NASA GSFC and the
   * National Imagery and Mapping Agency (NIMA) Geopotential Model
   * EGM96, NASA Technical Report NASA/TP-1998-206861, NASA Goddard
   * Space Flight Center, Greenbelt, Maryland, 20771 USA.
   */

  const double lon360 = (lon > 0.0) ? lon : lon + 2*M_PI;

  const double xLon = (lon360 - _west + _numExtraEdge*_dLon) / _dLon;
  const double xLat = (lat - _south) / _dLat;

  const int iLon = int(xLon);
  const int iLat = int(xLat);
  const int oLon = iLon - _numInterp / 2 + 1;
  const int oLat = iLat - _numInterp / 2 + 1;

  double valsNS[_numInterp];
  double valsEW[_numInterp];
  double moments[_numInterp];
  for (int iNS=0; iNS < _numInterp; ++iNS) {
    const int jNS = oLat + iNS;
    const int offset = _numGridEW * jNS;
    for (int iEW=0; iEW < _numInterp; ++iEW) {
      const int jEW = oLon + iEW;
      valsEW[iEW] = _pGridVals[offset+jEW];
    } // for
    _splineMoments(moments, valsEW);
    const double coord = xLon - oLon + 1;
    valsNS[iNS] = _splineInterp(coord, valsEW, moments);
  } // for
  _splineMoments(moments, valsNS);
  const double coord = xLat - oLat + 1;
  const double elev = _splineInterp(coord, valsNS, moments);
  return elev;
} // elevation

// ----------------------------------------------------------------------
// Read grid values.
void
spatialdata::geocoords::Geoid::_readGrid(void)
{ // _readGrid
  std::ifstream filein(_filename);
  if (!filein.is_open() || !filein.good()) {
    std::ostringstream msg;
    msg << "Could not open geoid grid file '" << _filename << "'.";
    throw std::runtime_error(msg.str().c_str());
  } // if

  const int numBufferEW = _numGridEW - 2 * _numExtraEdge;
  const int numBufferNS = _numGridNS;
  const int bufferSize = numBufferEW * numBufferNS;
  int16_t* buffer = (bufferSize > 0) ? new int16_t[bufferSize] : 0;

  filein.read((char*) buffer, bufferSize*sizeof(int16_t));
  _endianBigToNative(&buffer, bufferSize);
  
  const int gridSize = _numGridNS * _numGridEW;
  delete[] _pGridVals; 
  _pGridVals = (gridSize > 0) ? new double[gridSize] : 0;

  for (int i=0; i < _numGridNS; ++i) {
    const int gNS = _numGridNS - i - 1;
    const int bNS = i;
    for (int j=0; j < numBufferEW; ++j) {
      const int gEW = _numExtraEdge + j;
      const int bEW = j;
      _pGridVals[_numGridEW*gNS+gEW] = 
	double(buffer[numBufferEW*bNS+bEW]) / 100.0;
    } // for
    for (int j=0; j < _numExtraEdge; ++j) {
      const int gEW = j;
      const int bEW = numBufferEW - _numExtraEdge + j;
      _pGridVals[_numGridEW*gNS+gEW] = 
	double(buffer[numBufferEW*bNS+bEW]) / 100.0;
    } // for    
    for (int j=0; j < _numExtraEdge; ++j) {
      const int gEW = _numGridEW - _numExtraEdge + j;
      const int bEW = j;
      _pGridVals[_numGridEW*gNS+gEW] = 
	double(buffer[numBufferEW*bNS+bEW]) / 100.0;
    } // for
  } // for

  delete[] buffer; buffer = 0;
} // _readGrid

// ----------------------------------------------------------------------
// Interpolate using spline.
double
spatialdata::geocoords::Geoid::_splineInterp(const double coord,
					     const double* pVals,
					     const double* pMoments) const
{ // _splineInterp
  const int size = _numInterp;
  const double min = 1.0;
  const double max = size;
  double value = 0;
  if (coord < min) 
    value = pVals[0] + (coord-min)*(pVals[1]-pVals[0]-pMoments[1]/6.0);
  else if (coord > max) {
    const int iMax = size-1;
    value = pVals[iMax] + 
      (coord-max)*(pVals[iMax]-pVals[iMax-1]+pMoments[iMax]/6.0);
  } else {
    const int i = _splineFrac(coord) - 1;
    const double min = i + 1;
    const double coef = coord - min;
    value = pVals[i] +
      coef * ((pVals[i+1]-pVals[i]-pMoments[i]/3.0-pMoments[i+1]/6.0) +
	      coef * (pMoments[i]/2.0 +
		      coef * (pMoments[i+1]-pMoments[i])/6.0));
  } // else
  return value;
} // _splineInterp

// ----------------------------------------------------------------------
// Compute the spline moments.
void
spatialdata::geocoords::Geoid::_splineMoments(double* pMom,
					      const double* pVals) const
{ // _splineMoments
  double tmp[_numInterp];

  tmp[0] = 0.0;
  pMom[0] = 0.0;
  const int size = _numInterp;
  const int iMax = size-1;
  for (int i=1; i < iMax; ++i) {
    const double v = tmp[i-1]/2.0 + 2.0;
    tmp[i] = -0.5/v;
    pMom[i] = (3.0*(pVals[i+1]-2.0*pVals[i]+pVals[i-1]) - pMom[i-1]/2.0) / v;
  } // for
  pMom[iMax] = 0.0;
  for (int i=size-2; i > 0; --i)
    pMom[i] += tmp[i]*pMom[i+1];
} // _splineMoments

// ----------------------------------------------------------------------
// Use spline interpolation to compute elevation at point from grid.
int
spatialdata::geocoords::Geoid::_splineFrac(const double value) const
{ // _splineFrac
  int valueInt = int(value);
  if (value < 0 && value != double(valueInt))
    --valueInt;
  return valueInt;
} // _splinefrac

// ----------------------------------------------------------------------
// Convert array of int16_t values from big endian to native int16_t type.
void
spatialdata::geocoords::Geoid::_endianBigToNative(int16_t** ppVals,
						  const int numVals)
{ // _endianBigToNative
#if defined(NATIVE_LITTLE_ENDIAN)
  for (int i=0; i < numVals; ++i) {
    char* buf = (char*) (*ppVals + i);
    char tmp = buf[1];
    buf[1] = buf[0];
    buf[0] = tmp;
  } // for
#endif
} // _endianBigToNative

// version
// $Id$

// End of file 
