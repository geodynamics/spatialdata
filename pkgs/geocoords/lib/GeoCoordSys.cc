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

#include "GeoCoordSys.h" // implementation of class methods

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
spatialdata::GeoCoordSys::GeoCoordSys(void) :
  _projection("aea"),
  _ellipsoid("WGS84"),
  _datum("WGS84"),
  _units("m"),
  _pCS(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::GeoCoordSys::~GeoCoordSys(void)
{ // destructor
  pj_free(_pCS);
} // destructor

// ----------------------------------------------------------------------
// Copy constructor.
spatialdata::GeoCoordSys::GeoCoordSys(const GeoCoordSys& cs) :
  _projection(cs._projection),
  _ellipsoid(cs._ellipsoid),
  _datum(cs._datum),
  _units(cs._units),
  _pCS(0)
{ // copy constructor
  // initialize if cs has already been initialized
  if (0 != cs._pCS)
    initialize();
} // copy constructor

// ----------------------------------------------------------------------
// operator=
const spatialdata::GeoCoordSys&
spatialdata::GeoCoordSys::operator=(const GeoCoordSys& cs)
{ // operator=
  if (this != &cs) {
    _projection = cs._projection;
    _ellipsoid = cs._ellipsoid;
    _datum = cs._datum;
    _units = cs._units;
    if (0 != cs._pCS)
      initialize();
  } // if

  return *this;
} // operator=

// ----------------------------------------------------------------------
// Initialize projector.
void 
spatialdata::GeoCoordSys::initialize(void)
{ // initialize
  std::ostringstream args;
  args
    << "+proj=" << _projection
    << " +ellps=" << _ellipsoid
    << " +datum=" << _datum
    << " +units=" << _units;
  
  pj_free(_pCS);
  _pCS = pj_init_plus(args.str().c_str());
  if (0 == _pCS) {
    std::ostringstream msg;
    msg << "Error while initializing coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  projection: " << _projection << "\n"
	<< "  ellipsoid: " << _ellipsoid << "\n"
	<< "  datum: " << _datum << "\n"
	<< "  units: " << _units << "\n";
    throw std::runtime_error(msg.str());
  } // if
} // initialize

// ----------------------------------------------------------------------
// Are coordinate systems the same?
bool
spatialdata::operator==(const spatialdata::GeoCoordSys& a,
			const spatialdata::GeoCoordSys& b)
{ // operator==
  return ( 0 == strcmp(a._projection, b._projection) &&
	   0 == strcmp(a._ellipsoid, b._ellipsoid) &&
	   0 == strcmp(a._datum, b._datum) &&
	   0 == strcmp(a._units, b._units) );
} // operator==

// version
// $Id: GeoCoordSys.cc,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
