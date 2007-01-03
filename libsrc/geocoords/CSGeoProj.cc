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

#include <iostream> // USES std::istream, std::ostream

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
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
  if (numDims != CSGeo::spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << CSGeo::spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if

  const int size = numLocs * numDims;
  for (int i=0; i < size; i += numDims) {
    double lon = 0;
    double lat = 0;
    _pProjector->invproject(&lon, &lat, coords[i  ], coords[i+1]);
    coords[i  ] = lon;
    coords[i+1] = lat;
  } // for

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
  if (numDims != CSGeo::spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << CSGeo::spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if

  CSGeo::fromProjForm(coords, numLocs, numDims);

  const int size = numLocs * numDims;
  for (int i=0; i < size; i += numDims) {
    double x = 0;
    double y = 0;
    _pProjector->project(&x, &y, coords[i  ], coords[i+1]);
    coords[i  ] = x;
    coords[i+1] = y;
  } // for
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
  std::string token;
  const int maxIgnore = 128;

  char buffer[maxIgnore];
  double val;
  std::string name;

  s.ignore(maxIgnore, '{');
  s >> token;
  while (s.good() && token != "}") {
    s.ignore(maxIgnore, '=');
    if (0 == strcasecmp(token.c_str(), "to-meters")) {
      s >> val;
      toMeters(val);
    } else if (0 == strcasecmp(token.c_str(), "ellipsoid")) {
      s >> name;
      ellipsoid(name);
    } else if (0 == strcasecmp(token.c_str(), "datum-horiz")) {
      s >> std::ws;
      s.get(buffer, maxIgnore, '\n');
      datumHoriz(buffer);
    } else if (0 == strcasecmp(token.c_str(), "datum-vert")) {
      s >> std::ws;
      s.get(buffer, maxIgnore, '\n');
      datumVert(buffer);
    } else if (0 == strcasecmp(token.c_str(), "projector")) {
      s >> name;
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
    s >> token;
  } // while
  if (!s.good())
    throw std::runtime_error("I/O error while parsing CSGeoProj "
			     "settings.");
} // unpickle

// version
// $Id$

// End of file 
