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

#include "spatialdata/geocoords/CoordSys.h" // USES CoordSysGeo
#include "spatialdata/geocoords/CoordSysGeo.h" // USES CoordSysGeo

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestProjector );

// ----------------------------------------------------------------------
#include "data/TestProjector.dat"

// ----------------------------------------------------------------------
// Test projection()
void
spatialdata::geocoords::TestProjector::testProjection(void)
{ // testProjection
  CoordSysGeo cs;
  Projector proj(cs);
  proj.projection(_PROJECTION);
  CPPUNIT_ASSERT(0 == strcmp(proj.projection(), _PROJECTION));
} // testProjection

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestProjector::testConstructor(void)
{ // testConstructor
  CoordSysGeo cs;
  Projector proj(cs);
} // testConstructor

// ----------------------------------------------------------------------
// Test falseEasting()
void
spatialdata::geocoords::TestProjector::testFalseEasting(void)
{ // testFalseEasting
  CoordSysGeo cs;
  Projector proj(cs);
  proj.falseEasting(_FALSEEASTING);
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, proj.falseEasting()/_FALSEEASTING,
			       tolerance);
} // testEasting

// ----------------------------------------------------------------------
// Test falseNorthing()
void
spatialdata::geocoords::TestProjector::testFalseNorthing(void)
{ // testFalseNorthing
  CoordSysGeo cs;
  Projector proj(cs);
  proj.falseNorthing(_FALSENORTHING);
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, proj.falseNorthing()/_FALSENORTHING,
			       tolerance);
} // testNorthing

// ----------------------------------------------------------------------
// Test scaleFactor()
void
spatialdata::geocoords::TestProjector::testScaleFactor(void)
{ // testScaleFactor
  CoordSysGeo cs;
  Projector proj(cs);
  proj.scaleFactor(_SCALEFACTOR);
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, proj.scaleFactor()/_SCALEFACTOR,
			       tolerance);
} // testProjection

// ----------------------------------------------------------------------
// Test units()
void
spatialdata::geocoords::TestProjector::testUnits(void)
{ // testUnits
  CoordSysGeo cs;
  Projector proj(cs);
  proj.units(_UNITS);
  CPPUNIT_ASSERT(0 == strcmp(proj.units(), _UNITS));
} // testUnits

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestProjector::testInitialize(void)
{ // testInitialize
  CoordSysGeo cs;
  Projector proj(cs);
  proj.initialize();
} // testIniailize

// ----------------------------------------------------------------------
// Test project()
void
spatialdata::geocoords::TestProjector::testProject(void)
{ // testProject
  CoordSysGeo cs;
  Projector proj(cs);
  proj.projection(_PROJECTION);
  proj.falseEasting(_FALSEEASTING);
  proj.falseNorthing(_FALSENORTHING);
  proj.scaleFactor(_SCALEFACTOR);
  proj.units(_UNITS);
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
spatialdata::geocoords::TestProjector::testInvproject(void)
{ // testInvproject
  CoordSysGeo cs;
  Projector proj(cs);
  proj.projection(_PROJECTION);
  proj.falseEasting(_FALSEEASTING);
  proj.falseNorthing(_FALSENORTHING);
  proj.scaleFactor(_SCALEFACTOR);
  proj.units(_UNITS);
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
