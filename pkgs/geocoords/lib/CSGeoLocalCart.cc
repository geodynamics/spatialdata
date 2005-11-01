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

#include "CoordSys.h" // ISA CoordSysGeo
#include "CSGeo.h" // implementation of class methods
#include "CSGeoLocalCart.h" // implementation of class methods

extern "C" {
#include "proj_api.h" // USES PROJ4
}

#include "Geoid.h" // USES Geoid

#include <math.h> // USES M_PI, sin(), cos()
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
spatialdata::geocoords::CSGeoLocalCart::CSGeoLocalCart(void) :
  _originLon(0),
  _originLat(0),
  _originElev(0),
  _originX(0),
  _originY(0),
  _originZ(0),
  _localOrientation(0)
{ // constructor
  CSGeo::isGeocentric(true);
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSGeoLocalCart::~CSGeoLocalCart(void)
{ // destructor
  delete[] _localOrientation; _localOrientation = 0;
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
  _originZ(cs._originZ),
  _localOrientation(0)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Set origin of local cartesian coordinate system.
void
spatialdata::geocoords::CSGeoLocalCart::origin(const double lon,
					       const double lat,
					       const double elev)
{ // origin
  _originLon = lon;
  _originLat = lat;
  _originElev = elev;
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
  if (0 != strcasecmp(datumVert(), "ellipsoid"))
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

  delete[] _localOrientation; _localOrientation = new double[9];
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
spatialdata::geocoords::CSGeoLocalCart::toProjForm(double** ppCoords,
						   const int numLocs,
						   bool is2D) const
{ // toProjForm
  const double scale = toMeters();
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    // add origin to old to invert
    const double xOld = (*ppCoords)[index  ]*scale + _originX;
    const double yOld = (*ppCoords)[index+1]*scale + _originY;
    const double zOld = (*ppCoords)[index+2]*scale + _originZ;
    // multiply by transpose of direction cosines to invert
    (*ppCoords)[index++] = 
      _localOrientation[0]*xOld +
      _localOrientation[3]*yOld +
      _localOrientation[6]*zOld;
    (*ppCoords)[index++] = 
      _localOrientation[1]*xOld +
      _localOrientation[4]*yOld +
      _localOrientation[7]*zOld;
    (*ppCoords)[index++] = 
      _localOrientation[2]*xOld +
	_localOrientation[5]*yOld +
      _localOrientation[8]*zOld;
  } // for
} // toProjForm
  
// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CSGeoLocalCart::fromProjForm(double** ppCoords,
						     const int numLocs,
						     bool is2D) const
{ // fromProjForm
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    const double xOld = (*ppCoords)[index  ];
    const double yOld = (*ppCoords)[index+1];
    const double zOld = (*ppCoords)[index+2];
    (*ppCoords)[index++] = 
      _localOrientation[0]*xOld +
      _localOrientation[1]*yOld +
      _localOrientation[2]*zOld - _originX;
    (*ppCoords)[index++] = 
      _localOrientation[3]*xOld +
      _localOrientation[4]*yOld +
      _localOrientation[5]*zOld - _originY;
    (*ppCoords)[index++] = 
      _localOrientation[6]*xOld +
      _localOrientation[7]*yOld +
      _localOrientation[8]*zOld - _originZ;
  } // for

  const int numCoords = (is2D) ? 2 : 3;
  const int size = numLocs * numCoords;
  const double scale = toMeters();
  for (int i=0; i < size; ++i)
    (*ppCoords)[i] /= scale;
} // fromProjForm
  
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
  FIREWALL(0 != pLonWGS84);
  FIREWALL(0 != pLatWGS84);

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
  FIREWALL(0 != pECEFX);
  FIREWALL(0 != pECEFY);
  FIREWALL(0 != pECEFZ);

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
  const char* projString =
    "+proj=geocent +ellps=WGS84 +datum=WGS84 +units=m";
  return std::string(projString);
} // initialize

// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSGeoLocalCart::pickle(std::ostream& s) const
{ // pickle
  s << "geographic {\n"
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
    } else if (0 == strcasecmp(token.c_str(), "origin-lon")) {
      s >> _originLon;
    } else if (0 == strcasecmp(token.c_str(), "origin-lat")) {
      s >> _originLat;
    } else if (0 == strcasecmp(token.c_str(), "origin-elev")) {
      s >> _originElev;
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a CSGeoLocalCart token.\n"
	  << "Known CSGeoLocalCart token:\n"
	  << "  to-meters, ellipsoid, datum-horiz, datum-vert\n"
	  << "  origin-lon, origin-lat, origin-elev\n";
      throw std::runtime_error(msg.str().c_str());
    } // else
    s >> token;
  } // while
  if (!s.good())
    throw std::runtime_error("I/O error while parsing CSGeoLocalCart "
			     "settings.");
} // unpickle

// version
// $Id$

// End of file 
