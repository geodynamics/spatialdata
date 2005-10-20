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

#include "CoordSys.h" // HOLDS CoordSysGeo
#include "CoordSysGeo.h" // HOLDS CoordSysGeo

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
spatialdata::geocoords::Projector::Projector(const CoordSysGeo& coordSys) :
  _projection("aea"),
  _units("m"),
  _coordSys(coordSys),
  _pProj(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::Projector::~Projector(void)
{ // destructor
  pj_free(_pProj);
} // destructor

// ----------------------------------------------------------------------
// Initialize projector.
void 
spatialdata::geocoords::Projector::initialize(void)
{ // initialize
  const char* ellipsoid = _coordSys.ellipsoid();
  const char* datumHoriz = _coordSys.datumHoriz();

  std::ostringstream args;
  args
    << "+proj=" << _projection
    << " +ellps=" << ellipsoid
    << " +datum=" << datumHoriz
    << " +units=" << _units;
  
  pj_free(_pProj);
  _pProj = pj_init_plus(args.str().c_str());
  if (0 == _pProj) {
    std::ostringstream msg;
    msg << "Error while initializing projection:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << ellipsoid << "\n"
	<< "  horizontal datum: " << datumHoriz << "\n"
	<< "  units: " << _units << "\n";
    throw std::runtime_error(msg.str());
  } // if
} // initialize

// ----------------------------------------------------------------------
// Project geographic coordinates.
void
spatialdata::geocoords::Projector::project(double* pX,
					   double* pY,
					   const double lon,
					   const double lat)
{ // project
  FIREWALL(0 != pX);
  FIREWALL(0 != pY);
  FIREWALL(0 != _pProj);
  
  projUV lonlat;
  const double degToRad = M_PI / 180.0;
  lonlat.u = lon * degToRad;
  lonlat.v = lat * degToRad;
  projUV xy = pj_fwd(lonlat, _pProj);
  if (HUGE_VAL == xy.u) {
    std::ostringstream msg;
    msg << "Error while projecting location.\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << _coordSys.ellipsoid() << "\n"
	<< "  datum: " << _coordSys.datumHoriz() << "\n"
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
spatialdata::geocoords::Projector::invproject(double* pLon,
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
	<< "  ellipsoid: " << _coordSys.ellipsoid() << "\n"
	<< "  datum: " << _coordSys.datumHoriz() << "\n"
	<< "  units: " << _units << "\n"
	<< "  x: " << x << "\n"
	<< "  y: " << y << "\n";
    throw std::runtime_error(msg.str());
  } // if

  const double radToDeg = 180.0 / M_PI;
  *pLon = lonlat.u * radToDeg;
  *pLat = lonlat.v * radToDeg;
} // invproject

// version
// $Id: Projector.cc,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
