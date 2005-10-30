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
#include "CSGeo.h" // HOLDS CSGeo

extern "C" {
#include "proj_api.h" // USES PROJ4
};

#include <iostream> // USES std::istream, std::ostream

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::Projector::Projector(void) :
  _projection("tmerc"),
  _units("m"),
  _projOptions(""),
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
// Copy constructor
spatialdata::geocoords::Projector::Projector(const Projector& p) :
  _projection(p._projection),
  _units(p._units),
  _projOptions(p._projOptions),
  _pProj(0)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Initialize projector.
void 
spatialdata::geocoords::Projector::initialize(const CSGeo& csGeo)
{ // initialize
  const char* ellipsoid = csGeo.ellipsoid();
  const char* datumHoriz = csGeo.datumHoriz();

  std::ostringstream args;
  args
    << "+proj=" << _projection
    << " +ellps=" << ellipsoid
    << " +datum=" << datumHoriz
    << " +units=" << _units
    << " " << _projOptions;
  
  pj_free(_pProj);
  _pProj = pj_init_plus(args.str().c_str());
  if (0 == _pProj) {
    std::ostringstream msg;
    msg << "Error while initializing projection:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << ellipsoid << "\n"
	<< "  horizontal datum: " << datumHoriz << "\n"
	<< "  units: " << _units << "\n"
	<< "  proj options: " << _projOptions << "\n";
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
	<< "  units: " << _units << "\n"
	<< "  proj options: " << _projOptions << "\n";
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
	<< "  units: " << _units << "\n"
	<< "  proj options: " << _projOptions << "\n"
	<< "  x: " << x << "\n"
	<< "  y: " << y << "\n";
    throw std::runtime_error(msg.str());
  } // if

  const double radToDeg = 180.0 / M_PI;
  *pLon = lonlat.u * radToDeg;
  *pLat = lonlat.v * radToDeg;
} // invproject

// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::Projector::pickle(std::ostream& s) const
{ // pickle
  s << "projector {\n"
    << "  projection = " << _projection << "\n"
    << "  units = " << _units << "\n";
  if (_projOptions != "")
    s << "  proj-options = " << _projOptions << "\n";
  else
    s << "  proj-options = none\n";
  s << "}\n";
} // pickle

// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void 
spatialdata::geocoords::Projector::unpickle(std::istream& s)
{ // unpickle
  std::string token;
  const int maxIgnore = 128;
  char buffer[maxIgnore];

  s.ignore(maxIgnore, '{');
  s >> token;
  while (s.good() && token != "}") {
    s.ignore(maxIgnore, '=');
    if (0 == strcasecmp(token.c_str(), "projection")) {
      s >> _projection;
    } else if (0 == strcasecmp(token.c_str(), "units")) {
      s >> _units;
    } else if (0 == strcasecmp(token.c_str(), "proj-options")) {
      s >> std::ws;
      s.get(buffer, maxIgnore, '\n');
      if (0 != strcasecmp("none", buffer))
	_projOptions = buffer;
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a Projector token.\n"
	  << "Known Projector token:\n"
	  << "  projection, units, proj-options";
      throw std::runtime_error(msg.str().c_str());
    } // else
    s >> token;
  } // while
  if (!s.good())
    throw std::runtime_error("I/O error while parsing Projector settings.");
} // unpickle

// version
// $Id: Projector.cc,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
