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

#include "CSGeoLocalCart.hh" // implementation of class methods

extern "C" {
#include "proj.h" // USES PROJ
}

#include "Geoid.hh" // USES Geoid

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <math.h> // USES M_PI, sin(), cos(), sqrt()
#include <iostream> // USES std::istream, std::ostream

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSGeoLocalCart::CSGeoLocalCart(void) :
  _originLon(0),
  _originLat(0),
  _originElev(0),
  _originX(0),
  _originY(0),
  _originZ(0)
{ // constructor
  CSGeo::isGeocentric(true);
  CSGeo::setSpaceDim(3);
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSGeoLocalCart::~CSGeoLocalCart(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Copy constructor
spatialdata::geocoords::CSGeoLocalCart::CSGeoLocalCart(const CSGeoLocalCart& cs) :
  CSGeo(cs),
  _originLon(cs._originLon),
  _originLat(cs._originLat),
  _originElev(cs._originElev),
  _originX(cs._originX),
  _originY(cs._originY),
  _originZ(cs._originZ)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Get origin of local cartesian coordinate system.
void
spatialdata::geocoords::CSGeoLocalCart::origin(double* pLon,
					       double* pLat,
					       double* pElev)
{ // origin
  assert(0 != pLon);
  assert(0 != pLat);
  assert(0 != pElev);
  *pLon = _originLon;
  *pLat = _originLat;
  *pElev = _originElev;
} // origin

// ----------------------------------------------------------------------
// Initialize the coordinate system.
void
spatialdata::geocoords::CSGeoLocalCart::initialize(void)
{ // initialize
  CSGeo::initialize();

  const double degToRad = M_PI / 180.0;

  // convert local origin to WGS84
  double lonWGS84 = 0;
  double latWGS84 = 0;
  _geoToWGS84(&lonWGS84, &latWGS84, 
	      _originLon*degToRad, _originLat*degToRad,
	      ellipsoid(), datumHoriz());

  double originElev = _originElev;
  if (0 != strcasecmp(datumVert(), "ellipsoid")) {
      if (0 == strcasecmp(datumVert(), "mean sea level")) {
	  // change vertical datum to WGS84 ellipsoid
	  const double geoidHt = geoid().elevation(lonWGS84, latWGS84);
	  originElev += geoidHt / toMeters();
      } else {
	  std::ostringstream msg;
	  msg << "Do not know how to convert from vertical datum '"
	      << datumVert() << "' to 'ellipsoid'.";
	  throw std::runtime_error(msg.str());	
      } // else
  } // if

  // convert origin and point above origin to ECEF
  double originECEFX = 0;
  double originECEFY = 0;
  double originECEFZ = 0;
  _wgs84ToECEF(&originECEFX, &originECEFY, &originECEFZ,
	       lonWGS84, latWGS84, originElev);
  double aboveOriginECEFX = 0;
  double aboveOriginECEFY = 0;
  double aboveOriginECEFZ = 0;
  const double elevAbove = 25.0e+3;
  _wgs84ToECEF(&aboveOriginECEFX, &aboveOriginECEFY, &aboveOriginECEFZ,
	       lonWGS84, latWGS84, originElev+elevAbove);

  // Create unit vector for local +z direction; local +z direction is
  // normal to Earth's surface at origin; use point above origin to
  // find normal to Earth's surface at origin; make unit vector
  const double dx = aboveOriginECEFX - originECEFX;
  const double dy = aboveOriginECEFY - originECEFY;
  const double dz = aboveOriginECEFZ - originECEFZ;
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

  _localOrientation[0] = x0;
  _localOrientation[1] = x1;
  _localOrientation[2] = x2;
  _localOrientation[3] = y0;
  _localOrientation[4] = y1;
  _localOrientation[5] = y2;
  _localOrientation[6] = z0;
  _localOrientation[7] = z1;
  _localOrientation[8] = z2;

  _originX = 
    _localOrientation[0]*originECEFX +
    _localOrientation[1]*originECEFY +
    _localOrientation[2]*originECEFZ;
  _originY = 
    _localOrientation[3]*originECEFX +
    _localOrientation[4]*originECEFY +
    _localOrientation[5]*originECEFZ;
  _originZ =
    _localOrientation[6]*originECEFX +
    _localOrientation[7]*originECEFY +
    _localOrientation[8]*originECEFZ;

  _originX *= toMeters();
  _originY *= toMeters();
  _originZ *= toMeters();
} // initialize

// ----------------------------------------------------------------------
// Convert coordinates to PROJ4 useable form.
void
spatialdata::geocoords::CSGeoLocalCart::toProjForm(double* coords,
						   const int numLocs,
						   const int numDims) const
{ // toProjForm
  assert( (0 < numLocs && 0 != coords) ||
	  (0 == numLocs && 0 == coords));
  assert(0 != _localOrientation);

  if (numDims != spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if

  const double scale = toMeters();
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    // add origin to old to invert
    const double xOld = coords[index  ]*scale + _originX;
    const double yOld = coords[index+1]*scale + _originY;
    const double zOld = coords[index+2]*scale + _originZ;
    // multiply by transpose of direction cosines to invert
    coords[index++] = 
      _localOrientation[0]*xOld +
      _localOrientation[3]*yOld +
      _localOrientation[6]*zOld;
    coords[index++] = 
      _localOrientation[1]*xOld +
      _localOrientation[4]*yOld +
      _localOrientation[7]*zOld;
    coords[index++] = 
      _localOrientation[2]*xOld +
      _localOrientation[5]*yOld +
      _localOrientation[8]*zOld;
  } // for
} // toProjForm
  
// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CSGeoLocalCart::fromProjForm(double* coords,
						     const int numLocs,
						     const int numDims) const
{ // fromProjForm
  assert( (0 < numLocs && 0 != coords) ||
	  (0 == numLocs && 0 == coords) );
  assert(0 != _localOrientation);

  if (numDims != spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if

  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    const double xOld = coords[index  ];
    const double yOld = coords[index+1];
    const double zOld = coords[index+2];
    coords[index++] = 
      _localOrientation[0]*xOld +
      _localOrientation[1]*yOld +
      _localOrientation[2]*zOld - _originX;
    coords[index++] = 
      _localOrientation[3]*xOld +
      _localOrientation[4]*yOld +
      _localOrientation[5]*zOld - _originY;
    coords[index++] = 
      _localOrientation[6]*xOld +
      _localOrientation[7]*yOld +
      _localOrientation[8]*zOld - _originZ;
  } // for

  const int size = numLocs * numDims;
  const double scale = toMeters();
  for (int i=0; i < size; ++i)
    coords[i] /= scale;
} // fromProjForm

// ----------------------------------------------------------------------
// Get outward radial direction.
void
spatialdata::geocoords::CSGeoLocalCart::radialDir(double* dir,
						  const double* coords,
						  const int numLocs,
						  const int numDims) const
{ // radialDir
  assert( (0 < numLocs && 0 != dir) ||
	  (0 == numLocs && 0 == dir) );
  assert( (0 < numLocs && 0 != coords) ||
	  (0 == numLocs && 0 == coords) );

  if (numDims != spaceDim()) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions of coordinates ("
      << numDims << ") does not match number of spatial dimensions ("
      << spaceDim() << ") of coordinate system.";
    throw std::runtime_error(msg.str());
  } // if
  assert(3 == spaceDim());

  const double scale = toMeters();
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc, index+=numDims) {
    // Convert to ECEF
    // Get coordinates relative to origin
    const double x = coords[index  ]*scale + _originX;
    const double y = coords[index+1]*scale + _originY;
    const double z = coords[index+2]*scale + _originZ;
    // Rotate into ECEF
    const double xECEF = 
      _localOrientation[0]*x +
      _localOrientation[3]*y +
      _localOrientation[6]*z;
    const double yECEF = 
      _localOrientation[1]*x +
      _localOrientation[4]*y +
      _localOrientation[7]*z;
    const double zECEF = 
      _localOrientation[2]*x +
      _localOrientation[5]*y +
      _localOrientation[8]*z;

    const double mag = sqrt(xECEF*xECEF + yECEF*yECEF + zECEF*zECEF);
    const double dirX = xECEF / mag;
    const double dirY = yECEF / mag;
    const double dirZ = zECEF / mag;

    dir[index  ] = 
      _localOrientation[0]*dirX +
      _localOrientation[1]*dirY +
      _localOrientation[2]*dirZ;
    dir[index+1] = 
      _localOrientation[3]*dirX +
      _localOrientation[4]*dirY +
      _localOrientation[5]*dirZ;
    dir[index+2] = 
      _localOrientation[6]*dirX +
      _localOrientation[7]*dirY +
      _localOrientation[8]*dirZ;
  } // for
} // radialDir

// ----------------------------------------------------------------------
// Convert coordinates to WGS84.
void
spatialdata::geocoords::CSGeoLocalCart::_geoToWGS84(double* pLonWGS84,
						    double* pLatWGS84,
						    const double lon,
						    const double lat,
						    const char* ellipsoid,
						    const char* datumHoriz) const
{ // _geoToWGS84
  assert(0 != pLonWGS84);
  assert(0 != pLatWGS84);
  assert(0 != ellipsoid);
  assert(0 != datumHoriz);

  // convert lon/lat in rad to lon/lat in rad in WGS84
  if (0 != strcasecmp(datumHoriz, "WGS84") ||
      0 != strcasecmp(ellipsoid, "WGS84")) {
    std::ostringstream projString;
    projString
      << "+proj=latlong"
      << " +ellps=" << ellipsoid
      << " +datum=" << datumHoriz
      << " +units=m";
    projPJ csSrc = 
      pj_init_plus(projString.str().c_str());
    if (0 == csSrc) {
      std::ostringstream msg;
      msg << "Error while initializing source coordinate system:\n"
	  << "  " << pj_strerrno(pj_errno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
    projPJ csWGS84 = 
      pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +units=m");
    if (0 == csWGS84) {
      std::ostringstream msg;
      msg << "Error while initializing WGS84 coordinate system:\n"
	  << "  " << pj_strerrno(pj_errno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
    const int numLocs = 1;
    const int numCoords = 2;
    *pLonWGS84 = lon;
    *pLatWGS84 = lat;
    const int pjerrno = pj_transform(csSrc, csWGS84,
				     numLocs, numCoords, 
				     pLonWGS84, pLatWGS84, 0);
    pj_free(csSrc);
    pj_free(csWGS84);
    if (0 != pjerrno) {
      std::ostringstream msg;
      msg << "Error while converting coordinates:\n"
	  << "  " << pj_strerrno(pjerrno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
  } else {
    *pLonWGS84 = lon;
    *pLatWGS84 = lat;
  } // else
} // _geoToWGS84

// ----------------------------------------------------------------------
// Convert coordinates from WGS84 to ECEF.
void
spatialdata::geocoords::CSGeoLocalCart::_wgs84ToECEF(double* pECEFX,
						     double* pECEFY,
						     double* pECEFZ,
						     const double lonWGS84,
						     const double latWGS84,
						     const double elevWGS84) const
{ // _wgs84ToECEF
  assert(0 != pECEFX);
  assert(0 != pECEFY);
  assert(0 != pECEFZ);

  // convert lon/lat in rad in WGS84 to ECEF in m
  projPJ csWGS84 = 
    pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +units=m");
  if (0 == csWGS84) {
    std::ostringstream msg;
    msg << "Error while initializing WGS84 coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
  projPJ csECEF = 
    pj_init_plus("+proj=geocent +ellps=WGS84 +datum=WGS84 +units=m");
  if (0 == csECEF) {
    std::ostringstream msg;
    msg << "Error while initializing ECEF coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
  const int numLocs = 1;
  const int numCoords = 3;
  *pECEFX = lonWGS84;
  *pECEFY = latWGS84;
  *pECEFZ = elevWGS84;
  const int pjerrno = pj_transform(csWGS84, csECEF,
				   numLocs, numCoords, 
				   pECEFX, pECEFY, pECEFZ);
  pj_free(csWGS84);
  pj_free(csECEF);
  if (0 != pjerrno) {
    std::ostringstream msg;
    msg << "Error while converting coordinates:\n"
	<< "  " << pj_strerrno(pjerrno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
} // _wgs84ToECEF

// ----------------------------------------------------------------------
// Get the PROJ4 string associated with the coordinate system.
std::string 
spatialdata::geocoords::CSGeoLocalCart::_projCSString(void) const
{ // _projCSString
  const char* args = "+proj=geocent +ellps=WGS84 +datum=WGS84 +units=m";
  return std::string(args);
} // _projCSString

// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSGeoLocalCart::pickle(std::ostream& s) const
{ // pickle
  s << "geo-local-cartesian {\n"
    << "  to-meters = " << toMeters() << "\n"
    << "  ellipsoid = " << ellipsoid() << "\n"
    << "  datum-horiz = " << datumHoriz() << "\n"
    << "  datum-vert = " << datumVert() << "\n"
    << "  origin-lon = " << _originLon << "\n"
    << "  origin-lat = " << _originLat << "\n"
    << "  origin-elev = " << _originElev << "\n"
    << "}\n";
} // pickle

// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void 
spatialdata::geocoords::CSGeoLocalCart::unpickle(std::istream& s)
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
    } else if (0 == strcasecmp(token.c_str(), "origin-elev")) {
      buffer >> _originElev;
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a CSGeoLocalCart token.\n"
	  << "Known CSGeoLocalCart token:\n"
	  << "  to-meters, ellipsoid, datum-horiz, datum-vert\n"
	  << "  origin-lon, origin-lat, origin-elev\n";
      throw std::runtime_error(msg.str().c_str());
    } // else
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
  } // while
  if (token != "}")
    throw std::runtime_error("I/O error while parsing CSGeoLocalCart "
			     "settings.");
} // unpickle


// End of file 
