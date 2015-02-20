// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "CSGeoProj.hh" // implementation of class methods

#include "Projector.hh" // USES Projector
#include "Converter.hh" // USES Converter

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <math.h> // USES M_PI, sin(), cos()
#include <iostream> // USES std::istream, std::ostream

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSGeoProj::CSGeoProj(void) :
  _originLon(0.0),
  _originLat(0.0),
  _originX(0.0),
  _originY(0.0),
  _rotAngle(0.0),
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
  _originLon(cs._originLon),
  _originLat(cs._originLat),
  _originX(cs._originX),
  _originY(cs._originY),
  _rotAngle(cs._rotAngle),
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
// Set origin of local projected coordinate system.
void
spatialdata::geocoords::CSGeoProj::origin(const double lon,
					  const double lat)
{ // origin
  if (lon < -360.0 || lon > 360.0 || lat < -360.0 || lat > 360.0) {
    std::ostringstream msg;
    msg << "Longitude (" << lon << ") and latitude (" << lat 
	<< ") must be between in the range [-360.0, 360.0].";
    throw std::runtime_error(msg.str());
  } // if

  _originLon = lon;
  _originLat = lat;
  _originX = 0.0;
  _originY = 0.0;
} // origin

// ----------------------------------------------------------------------
// Get origin of local projected coordinate system.
void
spatialdata::geocoords::CSGeoProj::origin(double* pLon,
					  double* pLat)
{ // origin
  assert(pLon);
  assert(pLat);
  
  *pLon = _originLon;
  *pLat = _originLat;
} // origin

// ----------------------------------------------------------------------
// Set rotation angle (CCW from east) of local x axis.
void
spatialdata::geocoords::CSGeoProj::rotationAngle(const double angle)
{ // rotationAngle
  if (angle < -360.0 || angle > 360.0) {
    std::ostringstream msg;
    msg << "Rotation angle (" << angle 
	<< ") must be between in the range [-360.0, 360.0].";
    throw std::runtime_error(msg.str());
  } // if

  _rotAngle = angle;
} // rotationAngle

// ----------------------------------------------------------------------
// Get rotation angle (CCW from east) of local x axis.
double
spatialdata::geocoords::CSGeoProj::rotationAngle(void) const
{ // rotationAngle
  return _rotAngle;
} // rotationAngle

// ----------------------------------------------------------------------
// Initialize the coordinate system.
void
spatialdata::geocoords::CSGeoProj::initialize(void)
{ // initialize
  CSGeo::initialize();
  
  assert(0 != _pProjector);
  _pProjector->initialize(*this);

  // Convert origin in lon/lat to projected coordinate system.
  _originX = 0.0;
  _originY = 0.0;
  if (_originLon != 0.0 || _originLat != 0.0) {
    CSGeo csSrc;
    csSrc.ellipsoid("WGS84");
    csSrc.datumHoriz("WGS84");
    csSrc.datumVert(this->datumVert());
    csSrc.toMeters(this->toMeters());
    csSrc.setSpaceDim(2);
    csSrc.initialize();

    CSGeoProj csDest;
    csDest.ellipsoid(this->ellipsoid());
    csDest.datumHoriz(this->datumHoriz());
    csDest.datumVert(this->datumVert());
    csDest.toMeters(this->toMeters());
    csDest.setSpaceDim(2);
    assert(_pProjector);
    csDest.projector(*_pProjector);
    csDest.initialize();

    double originCoords[2] = { _originLon, _originLat };
    Converter::convert(originCoords, 1, 2, &csDest, &csSrc);
    _originX = originCoords[0];
    _originY = originCoords[1];
  } // if
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

  const double angleRad = M_PI * _rotAngle / 180.0;
  for (int i=0; i < numLocs; ++i) {
    const double xOld = coords[i*numDims  ];
    const double yOld = coords[i*numDims+1];

    coords[i*numDims  ] = _originX + cos(angleRad)*xOld - sin(angleRad)*yOld;
    coords[i*numDims+1] = _originY + sin(angleRad)*xOld + cos(angleRad)*yOld;
  } // for

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

  const double angleRad = M_PI * _rotAngle / 180.0;
  for (int i=0; i < numLocs; ++i) {
    const double xRel = coords[i*numDims  ] - _originX;
    const double yRel = coords[i*numDims+1] - _originY;

    coords[i*numDims  ] = cos(angleRad)*xRel + sin(angleRad)*yRel;
    coords[i*numDims+1] = -sin(angleRad)*xRel + cos(angleRad)*yRel;
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
    << "  origin-lon = " << _originLon << "\n"
    << "  origin-lat = " << _originLat << "\n"
    << "  rotation-angle = " << rotationAngle() << "\n"
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
    } else if (0 == strcasecmp(token.c_str(), "origin-lon")) {
      buffer >> _originLon;
    } else if (0 == strcasecmp(token.c_str(), "origin-lat")) {
      buffer >> _originLat;
    } else if (0 == strcasecmp(token.c_str(), "rotation-angle")) {
      buffer >> _rotAngle;
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
