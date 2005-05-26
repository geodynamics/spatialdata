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

#include "Projector.h" // implementation of class methods

extern "C" {
#include "proj_api.h" // USES PROJ4
};

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
spatialdata::Projector::Projector(void) :
  _projection("aea"),
  _ellipsoid("WGS84"),
  _datum("WGS84"),
  _units("m"),
  _pProj(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::Projector::~Projector(void)
{ // destructor
  pj_free(_pProj);
} // destructor

// ----------------------------------------------------------------------
// Initialize projector.
void 
spatialdata::Projector::initialize(void)
{ // initialize
  std::ostringstream args;
  args
    << "+proj=" << _projection
    << " +ellps=" << _ellipsoid
    << " +datum=" << _datum
    << " +units=" << _units;
  
  pj_free(_pProj);
  _pProj = pj_init_plus(args.str().c_str());
  if (0 == _pProj) {
    std::ostringstream msg;
    msg << "Error while initializing projection:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << _ellipsoid << "\n"
	<< "  datum: " << _datum << "\n"
	<< "  units: " << _units << "\n";
    throw std::runtime_error(msg.str());
  } // if
} // initialize

// ----------------------------------------------------------------------
// Project geographic coordinates.
void
spatialdata::Projector::project(double* pX,
				double* pY,
				const double lon,
				const double lat)
{ // project
  FIREWALL(0 != pX);
  FIREWALL(0 != pY);
  FIREWALL(0 != _pProj);
  
  projUV lonlat;
  lonlat.u = lon * DEG_TO_RAD;
  lonlat.v = lat * DEG_TO_RAD;
  projUV xy = pj_fwd(lonlat, _pProj);
  if (HUGE_VAL == xy.u) {
    std::ostringstream msg;
    msg << "Error while projecting location.\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << _ellipsoid << "\n"
	<< "  datum: " << _datum << "\n"
	<< "  units: " << _units << "\n"
	<< "  longitude: " << lon << "\n"
	<< "  latitude: " << lat << "\n";
    throw std::runtime_error(msg.str());
  } // if
  *pX = xy.u;
  *pY = xy.v;
} // project

// ----------------------------------------------------------------------
// Get geographic coordinates of projected location.
void
spatialdata::Projector::invproject(double* pLon,
				   double* pLat,
				   const double x,
				   const double y)
{ // invproject
  FIREWALL(0 != pLon);
  FIREWALL(0 != pLat);
  FIREWALL(0 != _pProj);
  
  projUV xy;
  xy.u = x;
  xy.v = y;
  projUV lonlat = pj_inv(xy, _pProj);
  if (HUGE_VAL == lonlat.u) {
    std::ostringstream msg;
    msg << "Error while getting geographic coordinates of projected "
      "location.\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << _ellipsoid << "\n"
	<< "  datum: " << _datum << "\n"
	<< "  units: " << _units << "\n"
	<< "  x: " << x << "\n"
	<< "  y: " << y << "\n";
    throw std::runtime_error(msg.str());
  } // if

  *pLon = lonlat.u * RAD_TO_DEG;
  *pLat = lonlat.v * RAD_TO_DEG;
} // invproject

// version
// $Id: Projector.cc,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
