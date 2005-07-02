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

#include "GeoCSConverter.h" // implementation of class methods

#include "GeoCoordSys.h" // USES GeoCoordSys
#include "Geoid.h" // Geoid

extern "C" {
#include "proj_api.h" // USES PROJ4
};

#include <string.h> // USES memcpy()
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
spatialdata::GeoCSConverter::GeoCSConverter(const GeoCoordSys& csDest,
					    const GeoCoordSys& csSrc) :
  _csDest(csDest),
  _csSrc(csSrc)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::GeoCSConverter::~GeoCSConverter(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Convert coordinates.
void
spatialdata::GeoCSConverter::convert(double** ppDest,
				     const int numLocs,
				     const bool isDeg,
				     const bool is2D) const
{ // convert
  FIREWALL(0 != ppDest);
  FIREWALL( (0 != *ppDest && 0 < numLocs) ||
	    (0 == *ppDest && 0 == numLocs) );
  FIREWALL(0 != _csSrc.coordsys());
  FIREWALL(0 != _csDest.coordsys());

  const int numCoords = (is2D) ? 2 : 3;

  if (isDeg) {
    const double degToRad = M_PI / 180.0;
    if (is2D) {
      const int size = numLocs*numCoords;
      for (int i=0; i < size; ++i)
	(*ppDest)[i] *= degToRad;
    } else
      for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
	(*ppDest)[index++] *= degToRad;
	(*ppDest)[index++] *= degToRad;
	++index; // skip vertical
      } // for
  } // if

  const int offset = numCoords;

  double* pX = (*ppDest) + 0; // lon
  double* pY = (*ppDest) + 1; // lat
  double* pZ = (is2D) ? 0 : (*ppDest) + 2;

  // Change vertical datum if datums are different
  // and source coordinates use WGS84 horizontal datum
  bool vertDatumChanged = false;
  if (!is2D &&
      0 != strcasecmp(_csSrc.datumVert(), _csDest.datumVert()) && 
      0 == strcasecmp(_csSrc.datumHoriz(), "WGS84") &&
      pj_is_latlong(_csSrc.coordsys())) {
    vertDatumChanged = true;
    _elevToGeoidHt(ppDest, numLocs);
  } // if

  const int pjerrno = pj_transform(_csSrc.coordsys(), _csDest.coordsys(),
				   numLocs, offset, pX, pY, pZ);
  if (0 != pjerrno) {
    std::ostringstream msg;
    msg << "Error while converting coordinates:\n"
	<< "  " << pj_strerrno(pjerrno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
  
  // Convert vertical datum if datums are different, datum hasn't
  // already been converted, and destination coordinates use WGS84
  // horizontal datum
  if (!is2D &&
      strcasecmp(_csSrc.datumVert(), _csDest.datumVert()) &&
      !vertDatumChanged)
    if (0 == strcasecmp(_csDest.datumHoriz(), "WGS84"))
      _elevToGeoidHt(ppDest, numLocs);
    else {
      std::ostringstream msg;
      msg << "Could not convert b/t coordinate system, because I do not "
	  << "know how to convert b/t vertical datums when neither "
	  << "the source nor destination horizontal datum is WGS84.";
      throw std::runtime_error(msg.str());
    } // else
  
  if (isDeg && pj_is_latlong(_csDest.coordsys())) {
    const double radToDeg = 180.0 / M_PI;
    if (is2D) {
      const int size = numLocs*numCoords;
      for (int i=0; i < size; ++i)
	(*ppDest)[i] *= radToDeg;
    } else
      for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
	(*ppDest)[index++] *= radToDeg;
	(*ppDest)[index++] *= radToDeg;
	++index; // skip vertical
      } // for
  } // if

} // convert

// ----------------------------------------------------------------------
// Convert vertical datum b/t elevation wrt WGS ellipsoid and mean sea level.
void
spatialdata::GeoCSConverter::_elevToGeoidHt(double** ppDest,
					    const int numLocs) const
{ // _elevtoGeoidHt
  FIREWALL(0 != ppDest);
  FIREWALL( (0 != *ppDest && 0 < numLocs) ||
	    (0 == *ppDest && 0 == numLocs) );
  FIREWALL(0 != _csSrc.coordsys());
  FIREWALL(0 != _csDest.coordsys());

  if (!pj_is_latlong(_csSrc.coordsys()) ||
      !pj_is_latlong(_csDest.coordsys())) {
    const char* msg =
      "Could not convert b/t coordinate systems, because I do not know how "
      "to convert b/t vertical datums not in lat/lon.";
    throw std::runtime_error(msg);
  } // if

  bool invert = false;
  if (0 == strcasecmp(_csSrc.datumVert(), "MSL") &&
      0 == strcasecmp(_csDest.datumVert(), "WGS84 ellipsoid"))
    invert = false;
  else if (0 == strcasecmp(_csSrc.datumVert(), "WGS84 ellipsoid") &&
	   0 == strcasecmp(_csDest.datumVert(), "MSL"))
    invert = true;
  else {
    std::ostringstream msg;
    msg << "Do not know how to convert b/t vertical datums '"
	<< _csSrc.datumVert() << "' and '"
	<< _csDest.datumVert() << "'.";
    throw std::runtime_error(msg.str());	
  } // else

    
  Geoid geoid;
  geoid.initialize();
  const int numCoords = 3;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc, index+=numCoords) {
    const double geoidHt = geoid.elevation((*ppDest)[index], 
					   (*ppDest)[index+1]);
    (*ppDest)[index+2] += (!invert) ? geoidHt : -geoidHt;
  } // for
} // _elevToGeoidHt

// version
// $Id: GeoCSConverter.cc,v 1.3 2005/07/02 00:23:25 baagaard Exp $

// End of file 
