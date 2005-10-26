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
#include "CSGeo.h" // implementation of class methods

#include "Geoid.h" // USES Geoid

#include <math.h> // USES M_PI
#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

extern "C" {
#include "proj_api.h" // USES PROJ4
}

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
spatialdata::geocoords::Geoid spatialdata::geocoords::CSGeo::_geoid = Geoid();

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSGeo::CSGeo(void) :
  _toMeters(1.0),
  _ellipsoid("WGS84"),
  _datumHoriz("WGS84"),
  _datumVert("ellipsoid"),
  _pCS(0),
  _isGeocentric(false)
{ // constructor
  csType(GEOGRAPHIC);
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSGeo::~CSGeo(void)
{ // destructor
  pj_free(_pCS);
  _pCS = 0;
} // destructor

// ----------------------------------------------------------------------
// Initialize coordinate system.
void 
spatialdata::geocoords::CSGeo::initialize(void)
{ // initialize
  pj_free(_pCS);
  std::string csString = _projCSString();
  _pCS = pj_init_plus(csString.c_str());
  if (0 == _pCS) {
    std::ostringstream msg;
    msg << "Error while initializing coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  proj string: " << csString << "\n";
    throw std::runtime_error(msg.str());
  } // if
  _geoid.initialize();
} // initialize

// ----------------------------------------------------------------------
// Convert coordinates to PROJ4 useable form.
void
spatialdata::geocoords::CSGeo::toProjForm(double** ppCoords,
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

    if (!is2D && _toMeters != 1.0)
      for (int i=2; i < size; i += numCoords)
	(*ppCoords)[i] *= _toMeters;
  } else {
    const int numCoords = (is2D) ? 2 : 3;
    const int size = numCoords * numLocs;
    for (int i=0; i < size; ++i)
      (*ppCoords)[i] *= _toMeters;
  } // else
} // toProjForm

// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CSGeo::fromProjForm(double** ppCoords,
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

    if (!is2D && _toMeters != 1.0)
      for (int i=2; i < size; i += numCoords)
	(*ppCoords)[i] /= _toMeters;
  } else {
    const int numCoords = (is2D) ? 2 : 3;
    const int size = numCoords * numLocs;
    for (int i=0; i < size; ++i)
      (*ppCoords)[i] /= _toMeters;
  } // else
} // fromProjForm

// ----------------------------------------------------------------------
// Get the PROJ4 string associated with the coordinate system.
std::string 
spatialdata::geocoords::CSGeo::_projCSString(void) const
{ // _projCSString
  // The common proj form uses meters so proj units are meters

  std::ostringstream args;
  const char* proj = (_isGeocentric) ? "geocent" : "latlong";
  args
    << "+proj=" << proj
    << " +ellps=" << _ellipsoid
    << " +datum=" << _datumHoriz
    << " +units=m";
  return std::string(args.str());
} // _projCSString

// version
// $Id$

// End of file 
