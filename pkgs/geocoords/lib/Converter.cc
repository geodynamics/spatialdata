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

#include "CoordSys.h" // USES CoordSys
#include "CSGeo.h" // USES CSGeo
#include "CSCart.h" // USES CSCart

extern "C" {
#include "proj_api.h" // USES PROJ4
}

#include "Geoid.h" // USES Geoid

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
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
					   const CoordSys* pCSDest,
					   const CoordSys* pCSSrc,
					   bool is2D)
{ // convert
  FIREWALL(0 != ppCoords);
  FIREWALL(0 != *ppCoords);
  FIREWALL(0 != pCSDest);
  FIREWALL(0 != pCSSrc);

  if (pCSSrc->csType() != pCSDest->csType())
    throw std::runtime_error("Cannot convert between coordinate systems "
			     "of different types.");

  switch (pCSSrc->csType())
    { // switch 
    case spatialdata::geocoords::CoordSys::GEOGRAPHIC :
      { // GEOGRAPHIC
	const CSGeo* pGeoDest = dynamic_cast<const CSGeo*>(pCSDest);
	const CSGeo* pGeoSrc = dynamic_cast<const CSGeo*>(pCSSrc);
	_convert(ppCoords, numLocs, *pGeoDest, *pGeoSrc, is2D);
	break;
      } // GEOGRAPHIC
    case spatialdata::geocoords::CoordSys::CARTESIAN :
      { // GEOGRAPHIC
	const CSCart* pCartDest = dynamic_cast<const CSCart*>(pCSDest);
	const CSCart* pCartSrc = dynamic_cast<const CSCart*>(pCSSrc);
	_convert(ppCoords, numLocs, *pCartDest, *pCartSrc, is2D);
	break;
      } // GEOGRAPHIC
    default :
      throw std::runtime_error("Could not parse coordinate system type.");
    } // switch
} // convert

// ----------------------------------------------------------------------
// Convert coordinates from source geographic coordinate system to
// destination geographic coordinate system.
void
spatialdata::geocoords::Converter::_convert(double** ppCoords,
					    const int numLocs,
					    const CSGeo& csDest,
					    const CSGeo& csSrc,
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
	0 == strcasecmp(destDatumVert, "ellipsoid"))
      isMSLToWGS84 = true;
    else if (0 == strcasecmp(srcDatumVert, "ellipsoid") &&
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
    const int size = numLocs * numCoords;
    for (int i=0; i < size; i+=3) {
      const double geoidHt = 
	CSGeo::geoid().elevation((*ppCoords)[i], (*ppCoords)[i+1]);
      (*ppCoords)[i+2] += (isMSLToWGS84) ? geoidHt : -geoidHt;
    } // for

    pjerrno = pj_transform(csWGS84, csDest.projCoordSys(), 
			   numLocs, numCoords, pX, pY, pZ);
    if (0 != pjerrno) {
      std::ostringstream msg;
      msg << "Error while converting coordinates:\n"
	  << "  " << pj_strerrno(pjerrno) << "\n";
      throw std::runtime_error(msg.str());
    } // if

    pj_free(csWGS84);
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

// ----------------------------------------------------------------------
// Convert coordinates from source Cartesian coordinate system to
// destination Cartesian coordinate system.
void
spatialdata::geocoords::Converter::_convert(double** ppCoords,
					    const int numLocs,
					    const CSCart& csDest,
					    const CSCart& csSrc,
					    bool is2D)
{ // convert
  FIREWALL(0 != ppCoords);
  FIREWALL(0 != *ppCoords);

  const int numCoords = is2D ? 2 : 3;
  const int size = numLocs*numCoords;
  const double scale = csSrc.toMeters() / csDest.toMeters();
  for (int i=0; i < size; ++i)
    (*ppCoords)[i] *= scale;
} // convert

// version
// $Id$

// End of file 
