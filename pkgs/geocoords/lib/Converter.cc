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

#include "Converter.h" // implementation of class methods

#include "CoordSys.h" // implementation of class methods

extern "C" {
#include "proj_api.h" // USES PROJ4
}

#include "Geoid.h" // USES Geoid

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

// ----------------------------------------------------------------------
// Convert coordinates from source coordinate system to destination
// coordinate system.
void
spatialdata::geocoords::Converter::convert(double** ppCoords,
					   const int numLocs,
					   const CoordSys& csDest,
					   const CoordSys& csSrc,
					   bool is2D)
{ // convert
  FIREWALL(0 != ppCoords);
  FIREWALL(0 != *ppCoords);

  csSrc.toProjForm(ppCoords, numLocs, is2D);

  const int numCoords = is2D ? 2 : 3;
  double* pX = (*ppCoords) + 0; // lon
  double* pY = (*ppCoords) + 1; // lat
  double* pZ = (is2D) ? 0 : (*ppCoords) + 2;

  const char* srcDatumVert = csSrc.projDatumVert();
  const char* destDatumVert = csDest.projDatumVert();
  if (!is2D && 0 != strcasecmp(srcDatumVert, destDatumVert)) {
    bool isMSLToWGS84 = true;
    if (0 == strcasecmp(srcDatumVert, "mean sea level") &&
	0 == strcasecmp(destDatumVert, "WGS84 ellipsoid"))
      isMSLToWGS84 = true;
    else if (0 == strcasecmp(srcDatumVert, "WGS84 ellipsoid") &&
	     0 == strcasecmp(destDatumVert, "mean sea level"))
      isMSLToWGS84 = false;
    else {
      std::ostringstream msg;
      msg << "Do not know how to convert b/t vertical datums '"
	  << srcDatumVert << "' and '"
	  << destDatumVert << "'.";
      throw std::runtime_error(msg.str());	
    } // else
    
    // convert to lon/lat in rad in WGS84
    projPJ csWGS84 = 
      pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +units=m");
    if (0 == csWGS84) {
      std::ostringstream msg;
      msg << "Error while initializing WGS84 coordinate system:\n"
	  << "  " << pj_strerrno(pj_errno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
    int pjerrno = pj_transform(csSrc.projCoordSys(), csWGS84,
				     numLocs, numCoords, 
				     pX, pY, pZ);
    if (0 != pjerrno) {
      std::ostringstream msg;
      msg << "Error while converting coordinates to WGS84:\n"
	  << "  " << pj_strerrno(pjerrno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
    Geoid geoid;
    geoid.initialize();
    const int size = numLocs * numCoords;
    const double elevToMeters = csSrc.elevToMeters();
    for (int i=0; i < size; i+=3) {
      const double geoidHt = geoid.elevation((*ppCoords)[i], (*ppCoords)[i+1]);
      (*ppCoords)[i+2] += (isMSLToWGS84) ? 
	geoidHt/elevToMeters : 
	-geoidHt/elevToMeters;
    } // for

    pjerrno = pj_transform(csWGS84, csDest.projCoordSys(), 
			   numLocs, numCoords, pX, pY, pZ);
    if (0 != pjerrno) {
      std::ostringstream msg;
      msg << "Error while converting coordinates:\n"
	  << "  " << pj_strerrno(pjerrno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
  } else {
    const int pjerrno = 
      pj_transform(csSrc.projCoordSys(), csDest.projCoordSys(),
		   numLocs, numCoords, pX, pY, pZ);
    if (0 != pjerrno) {
      std::ostringstream msg;
      msg << "Error while converting coordinates:\n"
	  << "  " << pj_strerrno(pjerrno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
  } // else

  csDest.fromProjForm(ppCoords, numLocs, is2D);
} // convert

// version
// $Id$

// End of file 
