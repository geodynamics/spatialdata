// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "Projector.hh" // implementation of class methods

#include "CoordSys.hh" // HOLDS CoordSysGeo
#include "CSGeo.hh" // HOLDS CSGeo

extern "C" {
#include "proj_api.h" // USES PROJ4
};

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <iostream> // USES std::istream, std::ostream

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringstream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

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
spatialdata::geocoords::Projector::project(double* coords,
					   const int numLocs,
					   const int numDims)
{ // project
  assert(0 != coords);
  assert(0 != _pProj);
  
  projUV lonlat;
  const double degToRad = M_PI / 180.0;
  for (int i=0; i < numLocs; ++i) {
    lonlat.u = coords[i*numDims  ] * degToRad;
    lonlat.v = coords[i*numDims+1] * degToRad;
    projUV xy = pj_fwd(lonlat, _pProj);
    if (HUGE_VAL == xy.u) {
      std::ostringstream msg;
      msg << "Error while projecting location.\n"
	  << "  " << pj_strerrno(pj_errno) << "\n"
	  << "  projection: " << _projection << "\n"
	  << "  units: " << _units << "\n"
	  << "  proj options: " << _projOptions << "\n"
	  << "  lon: " << lonlat.u << "\n"
	  << "  lat: " << lonlat.v << "\n";
      throw std::runtime_error(msg.str());
    } // if
    coords[i*numDims  ] = xy.u;
    coords[i*numDims+1] = xy.v;
  } // for
} // project

// ----------------------------------------------------------------------
// Get geographic coordinates of projected location.
void
spatialdata::geocoords::Projector::invproject(double* coords,
					      const int numLocs,
					      const int numDims)
{ // invproject
  assert(0 != coords);
  assert(0 != _pProj);
  
  const double radToDeg = 180.0 / M_PI;
  projUV xy;
  for (int i=0; i < numLocs; ++i) {
    xy.u = coords[i*numDims  ];
    xy.v = coords[i*numDims+1];
    projUV lonlat = pj_inv(xy, _pProj);
    if (HUGE_VAL == lonlat.u) {
      std::ostringstream msg;
      msg << "Error while getting geographic coordinates of projected "
	"location.\n"
	  << "  " << pj_strerrno(pj_errno) << "\n"
	  << "  projection: " << _projection << "\n"
	  << "  units: " << _units << "\n"
	  << "  proj options: " << _projOptions << "\n"
	  << "  x: " << xy.u << "\n"
	  << "  y: " << xy.v << "\n";
      throw std::runtime_error(msg.str());
    } // if
    coords[i*numDims  ] = lonlat.u * radToDeg;
    coords[i*numDims+1] = lonlat.v * radToDeg;
  } // for
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
  utils::LineParser parser(s, "//");
  parser.eatwhitespace(true);

  std::string token;
  std::istringstream buffer;
  const int maxIgnore = 256;
  char cbuffer[maxIgnore];

  parser.ignore('{');
  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  while (buffer.good() && token != "}") {
    buffer.ignore(maxIgnore, '=');
    if (0 == strcasecmp(token.c_str(), "projection")) {
      buffer >> _projection;
    } else if (0 == strcasecmp(token.c_str(), "units")) {
      buffer >> _units;
    } else if (0 == strcasecmp(token.c_str(), "proj-options")) {
      buffer >> std::ws;
      buffer.get(cbuffer, maxIgnore, '\n');
      if (0 != strcasecmp("none", cbuffer))
	_projOptions = cbuffer;
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a Projector token.\n"
	  << "Known Projector token:\n"
	  << "  projection, units, proj-options";
      throw std::runtime_error(msg.str().c_str());
    } // else
  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  } // while
  if (token != "}")
    throw std::runtime_error("I/O error while parsing Projector settings.");
} // unpickle


// End of file 
