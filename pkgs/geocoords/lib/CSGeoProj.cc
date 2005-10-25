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
#include "CSGeoProj.h" // implementation of class methods

#include "Projector.h" // USES Projector

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

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
  
  FIREWALL(0 != _pProjector);
  _pProjector->initialize(*this);
} // initialize

// ----------------------------------------------------------------------
// Convert coordinates to PROJ4 useable form.
void
spatialdata::geocoords::CSGeoProj::toProjForm(double** ppCoords,
					      const int numLocs,
					      bool is2D) const
{ // toProjForm
  FIREWALL(0 != _pProjector);

  const int numCoords = (is2D) ? 2 : 3;
  const int size = numCoords * numLocs;
  for (int i=0; i < size; i += numCoords) {
    double lon = 0;
    double lat = 0;
    _pProjector->invproject(&lon, &lat, (*ppCoords)[i  ], (*ppCoords)[i+1]);
    (*ppCoords)[i  ] = lon;
    (*ppCoords)[i+1] = lat;
  } // for

  CSGeo::toProjForm(ppCoords, numLocs, is2D);
} // toProjForm
  
// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CSGeoProj::fromProjForm(double** ppCoords,
						const int numLocs,
						bool is2D) const
{ // fromProjForm
  FIREWALL(0 != _pProjector);

  CSGeo::fromProjForm(ppCoords, numLocs, is2D);

  const int numCoords = (is2D) ? 2 : 3;
  const int size = numCoords * numLocs;
  for (int i=0; i < size; i += numCoords) {
    double x = 0;
    double y = 0;
    _pProjector->project(&x, &y, (*ppCoords)[i  ], (*ppCoords)[i+1]);
    (*ppCoords)[i  ] = x;
    (*ppCoords)[i+1] = y;
  } // for
} // fromProjForm
  
// version
// $Id$

// version
// $Id$

// End of file 
