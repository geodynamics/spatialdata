// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestProjector.h" // Implementation of class methods

#include "spatialdata/geocoords/Projector.h" // USES Projector

#include "journal/debug.h" // USES journal::debug_t

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::TestProjector );

// ----------------------------------------------------------------------
#include "data/TestProjector.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::TestProjector::testConstructor(void)
{ // testConstructor
  Projector proj;
} // testConstructor

// ----------------------------------------------------------------------
// Test projection()
void
spatialdata::TestProjector::testProjection(void)
{ // testProjection
  Projector proj;
  const char* projection = "aea";
  proj.projection(projection);
  CPPUNIT_ASSERT(0 == strcmp(proj.projection(), projection));
} // testProjection

// ----------------------------------------------------------------------
// Test ellipsoid()
void
spatialdata::TestProjector::testEllipsoid(void)
{ // testEllipsoid
  Projector proj;
  const char* ellipsoid = "WGS84";
  proj.ellipsoid(ellipsoid);
  CPPUNIT_ASSERT(0 == strcmp(proj.ellipsoid(), ellipsoid));
} // testEllipsoid

// ----------------------------------------------------------------------
// Test datum()
void
spatialdata::TestProjector::testDatum(void)
{ // testDatum
  Projector proj;
  const char* datum = "NAD27";
  proj.datum(datum);
  CPPUNIT_ASSERT(0 == strcmp(proj.datum(), datum));
} // testDatum

// ----------------------------------------------------------------------
// Test units()
void
spatialdata::TestProjector::testUnits(void)
{ // testUnits
  Projector proj;
  const char* units = "km";
  proj.units(units);
  CPPUNIT_ASSERT(0 == strcmp(proj.units(), units));
} // testUnits

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::TestProjector::testInitialize(void)
{ // testInitialize
  Projector proj;
  proj.initialize();
} // testIniailize

// ----------------------------------------------------------------------
// Test project()
void
spatialdata::TestProjector::testProject(void)
{ // testProject
  Projector proj;
  proj.initialize();
  const int numLocs = _NUMLOCS;
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    double x = 0;
    double y = 0;
    const double* pLonLat = &_LONLAT[2*iLoc];
    proj.project(&x, &y, pLonLat[0], pLonLat[1]);
    const double* pXY = &_XY[2*iLoc];
    const double tolerance = 1.0e-6;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(x/pXY[0], 1.0, tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(y/pXY[1], 1.0, tolerance);
  } // for
} // testProject

// ----------------------------------------------------------------------
// Test invproject()
void
spatialdata::TestProjector::testInvproject(void)
{ // testInvproject
  Projector proj;
  proj.initialize();
  const int numLocs = _NUMLOCS;
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    double lon = 0;
    double lat = 0;
    const double* pXY = &_XY[2*iLoc];
    proj.invproject(&lon, &lat, pXY[0], pXY[1]);
    const double* pLonLat = &_LONLAT[2*iLoc];
    const double tolerance = 1.0e-6;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(lon/pLonLat[0], 1.0, tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(lat/pLonLat[1], 1.0, tolerance);
  } // for
} // testInvproject

// version
// $Id: TestProjector.cc,v 1.1 2005/05/25 17:29:42 baagaard Exp $

// End of file 
