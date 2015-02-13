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

#include "TestProjector.hh" // Implementation of class methods

#include "spatialdata/geocoords/Projector.hh" // USES Projector

#include "spatialdata/geocoords/CoordSys.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include <valarray> // USES std::valarray
#include <string.h> // USES strcmp()
#include <strings.h> // USES strcasecmp()
#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestProjector );

// ----------------------------------------------------------------------
#include "data/TestProjector.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestProjector::testConstructor(void)
{ // testConstructor
  Projector proj;
} // testConstructor

// ----------------------------------------------------------------------
// Test copy constructor
void
spatialdata::geocoords::TestProjector::testCopy(void)
{ // testCopy
  Projector proj;
  proj.projection(_PROJECTION);
  proj.units(_UNITS);
  proj.projOptions(_PROJOPTIONS);

  Projector projB(proj);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT(0 == strcmp(projB.projection(), _PROJECTION));
  CPPUNIT_ASSERT(0 == strcmp(proj.units(), _UNITS));
  CPPUNIT_ASSERT(0 == strcmp(proj.projOptions(), _PROJOPTIONS));
} // testCopy

// ----------------------------------------------------------------------
// Test projection()
void
spatialdata::geocoords::TestProjector::testProjection(void)
{ // testProjection
  Projector proj;
  proj.projection(_PROJECTION);
  CPPUNIT_ASSERT(0 == strcmp(proj.projection(), _PROJECTION));
} // testProjection

// ----------------------------------------------------------------------
// Test units()
void
spatialdata::geocoords::TestProjector::testUnits(void)
{ // testUnits
  Projector proj;
  proj.units(_UNITS);
  CPPUNIT_ASSERT(0 == strcmp(proj.units(), _UNITS));
} // testUnits

// ----------------------------------------------------------------------
// Test projOptions()
void
spatialdata::geocoords::TestProjector::testProjOptions(void)
{ // testProjOptions
  Projector proj;
  proj.units(_PROJOPTIONS);
  CPPUNIT_ASSERT(0 == strcmp(proj.units(), _PROJOPTIONS));
} // testProjOptions

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestProjector::testInitialize(void)
{ // testInitialize
  Projector proj;
  CSGeo cs;
  proj.initialize(cs);
} // testIniailize

// ----------------------------------------------------------------------
// Test project()
void
spatialdata::geocoords::TestProjector::testProject(void)
{ // testProject
  Projector proj;
  proj.projection(_PROJECTION);
  proj.units(_UNITS);
  proj.projOptions(_PROJOPTIONS);

  CSGeo cs;
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.initialize();
  proj.initialize(cs);

  const int numLocs = _NUMLOCS;
  const int numDims = 2;
  const int size = numDims * numLocs;
  std::valarray<double> coords(size);
  memcpy(&coords[0], _LONLAT, size*sizeof(double));

  proj.project(&coords[0], numLocs, numDims);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(coords[i]/_XY[i], 1.0, tolerance);
} // testProject

// ----------------------------------------------------------------------
// Test invproject()
void
spatialdata::geocoords::TestProjector::testInvproject(void)
{ // testInvproject
  Projector proj;
  proj.projection(_PROJECTION);
  proj.units(_UNITS);
  proj.projOptions(_PROJOPTIONS);

  CSGeo cs;
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.initialize();
  proj.initialize(cs);

  const int numLocs = _NUMLOCS;
  const int numDims = 2;
  const int size = numDims * numLocs;
  std::valarray<double> coords(size);
  memcpy(&coords[0], _XY, size*sizeof(double));

  proj.invproject(&coords[0], numLocs, numDims);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(coords[i]/_LONLAT[i], 1.0, tolerance);
} // testInvproject

// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestProjector::testPickle(void)
{ // testPickle
  Projector projA;
  projA.projection(_PROJECTION);
  projA.units(_UNITS);
  projA.projOptions(_PROJOPTIONS);

  std::stringstream s;
  projA.pickle(s);
  
  Projector projB;
  projB.unpickle(s);
  CPPUNIT_ASSERT(0 == strcasecmp(_PROJECTION, projB.projection()));
  CPPUNIT_ASSERT(0 == strcasecmp(_UNITS, projB.units()));
  CPPUNIT_ASSERT(0 == strcasecmp(_PROJOPTIONS, projB.projOptions()));
} // testPickle


// End of file 
