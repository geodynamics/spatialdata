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

#include "CSGeoProj.hh" // implementation of class methods

#include "Projector.hh" // USES Projector

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <iostream> // USES std::istream, std::ostream

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSGeoProj::CSGeoProj(void) :
  _pProjector(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSGeoProj::~CSGeoProj(void)
{ // destructor
  delete _pProjector; _pProjector = 0;
} // destructor

// ----------------------------------------------------------------------
// Copy constructor
spatialdata::geocoords::CSGeoProj::CSGeoProj(const CSGeoProj& cs) :
  CSGeo(cs),
  _pProjector(0)
{ // copy constructor
  if (0 != cs._pProjector)
    _pProjector = new Projector(*cs._pProjector);
} // copy constructor

// ----------------------------------------------------------------------
// Set projector.
void
spatialdata::geocoords::CSGeoProj::projector(const Projector& projector)
{ // projector
  _pProjector = new Projector(projector);
} // projector

// ----------------------------------------------------------------------
// Initialize the coordinate system.
void
spatialdata::geocoords::CSGeoProj::initialize(void)
{ // initialize
  CSGeo::initialize();
  
  assert(0 != _pProjector);
  _pProjector->initialize(*this);
} // initialize

// ----------------------------------------------------------------------
// Convert coordinates to PROJ4 useable form.
void
spatialdata::geocoords::CSGeoProj::toProjForm(double* coords,
					      const int numLocs,
					      const int numDims) const
{ // toProjForm
  assert( (0 < numLocs && 0 != coords) ||
	  (0 == numLocs && 0 == coords));
  assert(0 != _pProjector);
  if (numDims != spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if

  _pProjector->invproject(coords, numLocs, numDims);
  CSGeo::toProjForm(coords, numLocs, numDims);
} // toProjForm
  
// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CSGeoProj::fromProjForm(double* coords,
						const int numLocs,
						const int numDims) const
{ // fromProjForm
  assert( (0 < numLocs && 0 != coords) ||
	  (0 == numLocs && 0 == coords));
  assert(0 != _pProjector);
  if (numDims != spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if

  CSGeo::fromProjForm(coords, numLocs, numDims);
  _pProjector->project(coords, numLocs, numDims);
} // fromProjForm
  
// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSGeoProj::pickle(std::ostream& s) const
{ // pickle
  s << "geo-projected {\n"
    << "  to-meters = " << toMeters() << "\n"
    << "  ellipsoid = " << ellipsoid() << "\n"
    << "  datum-horiz = " << datumHoriz() << "\n"
    << "  datum-vert = " << datumVert() << "\n"
    << "  projector = ";
  _pProjector->pickle(s);
  s << "}\n";
} // pickle

// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void 
spatialdata::geocoords::CSGeoProj::unpickle(std::istream& s)
{ // unpickle
  utils::LineParser parser(s, "//");
  parser.eatwhitespace(true);

  std::string token;
  std::istringstream buffer;
  const int maxIgnore = 256;
  char cbuffer[maxIgnore];
  double val;
  std::string name;

  parser.ignore('{');
  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  while (buffer.good() && token != "}") {
    buffer.ignore(maxIgnore, '=');
    if (0 == strcasecmp(token.c_str(), "to-meters")) {
      buffer >> val;
      toMeters(val);
    } else if (0 == strcasecmp(token.c_str(), "ellipsoid")) {
      buffer >> name;
      ellipsoid(name.c_str());
    } else if (0 == strcasecmp(token.c_str(), "datum-horiz")) {
      buffer >> std::ws;
      buffer.get(cbuffer, maxIgnore, '\n');
      datumHoriz(cbuffer);
    } else if (0 == strcasecmp(token.c_str(), "datum-vert")) {
      buffer >> std::ws;
      buffer.get(cbuffer, maxIgnore, '\n');
      datumVert(cbuffer);
    } else if (0 == strcasecmp(token.c_str(), "projector")) {
      std::string rbuffer(buffer.str());
      int start = token.length();
      int end = rbuffer.length();
      for (int i=start; i < end; ++i)
	if ('=' == rbuffer[i])
	  start = i+1;
      for (int i=end-1; i >= start; --i) {
	s.putback(rbuffer[i]);
      } // for
      s.clear();
      if (0 == _pProjector)
	_pProjector = new Projector;
      _pProjector->unpickle(s);
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a CSGeoProj token.\n"
	  << "Known CSGeoProj token:\n"
	  << "  to-meters, ellipsoid, datum-horiz, datum-vert, projector\n";
      throw std::runtime_error(msg.str().c_str());
    } // else
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
  } // while
  if (token != "}")
    throw std::runtime_error("I/O error while parsing CSGeoProj "
			     "settings.");
} // unpickle


// End of file 
