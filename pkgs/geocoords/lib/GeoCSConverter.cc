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

#include <iostream>
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
  const int pjerrno = pj_transform(_csSrc.coordsys(), _csDest.coordsys(),
				   numLocs, offset, pX, pY, pZ);
  if (0 != pjerrno) {
    std::ostringstream msg;
    msg << "Error while converting coordinates:\n"
	<< "  " << pj_strerrno(pjerrno) << "\n";
    throw std::runtime_error(msg.str());
  } // if

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

// version
// $Id: GeoCSConverter.cc,v 1.2 2005/06/01 16:51:34 baagaard Exp $

// End of file 
