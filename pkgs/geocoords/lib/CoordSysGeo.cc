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

#include "CoordSys.h" // ISA Coordsys
#include "CoordSysGeo.h" // implementation of class methods

#include <math.h> // USES M_PI
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
spatialdata::geocoords::CoordSysGeo::CoordSysGeo(void) :
  _elevToMeters(1.0),
  _ellipsoid("WGS84"),
  _datumHoriz("WGS84"),
  _datumVert("WGS84 ellipsoid"),
  _isGeocentric(false)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CoordSysGeo::~CoordSysGeo(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Convert coordinates to PROJ4 useable form.
void
spatialdata::geocoords::CoordSysGeo::toProjForm(double** ppCoords,
						const int numLocs,
						bool is2D) const
{ // toProjForm
  if (!_isGeocentric) {
    // convert deg to rad
    const int numCoords = (is2D) ? 2 : 3;
    const int size = numCoords * numLocs;

    const double degToRad = M_PI / 180.0;
    for (int i=0; i < size; i += numCoords) {
      (*ppCoords)[i  ] *= degToRad;
      (*ppCoords)[i+1] *= degToRad;
    } // for
  } // if
} // toProjForm

// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CoordSysGeo::fromProjForm(double** ppCoords,
						  const int numLocs,
						  bool is2D) const
{ // fromProjForm
  if (!_isGeocentric) {
    // convert rad to deg
    const int numCoords = (is2D) ? 2 : 3;
    const int size = numCoords * numLocs;

    const double radToDeg = 180.0 / M_PI;
    for (int i=0; i < size; i += numCoords) {
      (*ppCoords)[i  ] *= radToDeg;
      (*ppCoords)[i+1] *= radToDeg;
    } // for
  } // if
} // fromProjForm

// ----------------------------------------------------------------------
// Get the PROJ4 string associated with the coordinate system.
std::string 
spatialdata::geocoords::CoordSysGeo::_projCSString(void) const
{ // _projCSString
  std::ostringstream args;
  const char* proj = (_isGeocentric) ? "geocent" : "latlong";
  args
    << "+proj=" << proj
    << " +ellps=" << _ellipsoid
    << " +datum=" << _datumHoriz
    << " +units=m";
  return std::string(args.str());
} // initialize

// version
// $Id$

// End of file 
