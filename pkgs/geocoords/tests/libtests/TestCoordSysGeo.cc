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

#include "TestCoordSysGeo.h" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.h" // USES CoordSysGeo
#include "spatialdata/geocoords/CoordSysGeo.h" // USES CoordSysGeo
#include <math.h> // USES M_PI

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCoordSysGeo );

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCoordSysGeo::testConstructor(void)
{ // testConstructor
  CoordSysGeo cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test ellipsoid()
void
spatialdata::geocoords::TestCoordSysGeo::testEllipsoid(void)
{ // testEllipsoid
  CoordSysGeo cs;
  const char* ellipsoid = "WGS83";
  cs.ellipsoid(ellipsoid);
  CPPUNIT_ASSERT(0 == strcmp(cs.ellipsoid(), ellipsoid));
} // testEllipsoid

// ----------------------------------------------------------------------
// Test datumHoriz()
void
spatialdata::geocoords::TestCoordSysGeo::testDatumHoriz(void)
{ // testDatumHoriz
  CoordSysGeo cs;
  const char* datumHoriz = "NAD27";
  cs.datumHoriz(datumHoriz);
  CPPUNIT_ASSERT(0 == strcmp(cs.datumHoriz(), datumHoriz));
} // testDatum

// ----------------------------------------------------------------------
// Test datumVert()
void
spatialdata::geocoords::TestCoordSysGeo::testDatumVert(void)
{ // testDatumVert
  CoordSysGeo cs;
  const char* datumVert = "mean sea level";
  cs.datumVert(datumVert);
  CPPUNIT_ASSERT(0 == strcmp(cs.datumVert(), datumVert));
} // testDatumVert

// ----------------------------------------------------------------------
// Test isGeocentric()
void
spatialdata::geocoords::TestCoordSysGeo::testGeocentric(void)
{ // testGeocentric
  CoordSysGeo cs;
  CPPUNIT_ASSERT(!cs.isGeocentric());
  cs.isGeocentric(true);
  CPPUNIT_ASSERT(cs.isGeocentric());
  cs.isGeocentric(false);
  CPPUNIT_ASSERT(!cs.isGeocentric());
} // testGeocentric

// ----------------------------------------------------------------------
// Test elevToMeters()
void
spatialdata::geocoords::TestCoordSysGeo::testElevToMeters(void)
{ // testElevToMeters
  CoordSysGeo cs;
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs.elevToMeters(), tolerance);
  const double elevToMeters = 5.53;
  cs.elevToMeters(elevToMeters);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(elevToMeters, cs.elevToMeters(), tolerance);
} // testElevToMeters

// ----------------------------------------------------------------------
// Test toProjForm()
void
spatialdata::geocoords::TestCoordSysGeo::testToProjForm(void)
{ // testToProjForm
  CoordSysGeo cs;

  const double tolerance = 1.0e-6;

  { // 2D
    const bool is2D = true;
    const int numLocs = 4;
    const int numCoords = 2;
    const double pCoords[] = { 28.0, 23.0,
			       42.0, 34.0,
			       -12.0, 65.7,
			       64.3, -163.0 };
    cs.isGeocentric(true);
    const int size = numLocs * numCoords;
    double* pVals = new double[size];
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.toProjForm(&pVals, numLocs, is2D);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/pCoords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.toProjForm(&pVals, numLocs, is2D);
    const double degToRad = M_PI / 180.0;
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/(pCoords[i]*degToRad),
				   tolerance);
    delete[] pVals; pVals = 0;
  } // 2D

  { // 3D
    const bool is2D = false;
    const int numLocs = 4;
    const int numCoords = 3;
    const double pCoords[] = { 28.0, 23.0, 3.4,
			       42.0, 34.0, 3.5,
			       -12.0, 65.7, 12.6,
			       64.3, -163.0, -1.5 };
    cs.isGeocentric(true);
    const int size = numLocs * numCoords;
    double* pVals = new double[size];
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.toProjForm(&pVals, numLocs, is2D);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/pCoords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.toProjForm(&pVals, numLocs, is2D);
    const double degToRad = M_PI / 180.0;
    for (int i=0; i < size; i += 3) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/(pCoords[i]*degToRad),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i+1]/(pCoords[i+1]*degToRad),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i+2]/pCoords[i+2],
				   tolerance);
    } // for
    delete[] pVals; pVals = 0;
  } // 3D
} // testToProjForm

// ----------------------------------------------------------------------
// Test fromProjForm()
void
spatialdata::geocoords::TestCoordSysGeo::testFromProjForm(void)
{ // testFromProjForm
  CoordSysGeo cs;

  const double tolerance = 1.0e-6;

  { // 2D
    const bool is2D = true;
    const int numLocs = 4;
    const int numCoords = 2;
    const double pCoords[] = { 28.0, 23.0,
			       42.0, 34.0,
			       -12.0, 65.7,
			       64.3, -163.0 };
    cs.isGeocentric(true);
    const int size = numLocs * numCoords;
    double* pVals = new double[size];
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.fromProjForm(&pVals, numLocs, is2D);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/pCoords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.fromProjForm(&pVals, numLocs, is2D);
    const double radToDeg = 180.0 / M_PI;
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/(pCoords[i]*radToDeg),
				   tolerance);
    delete[] pVals; pVals = 0;
  } // 2D

  { // 3D
    const bool is2D = false;
    const int numLocs = 4;
    const int numCoords = 3;
    const double pCoords[] = { 28.0, 23.0, 3.4,
			       42.0, 34.0, 3.5,
			       -12.0, 65.7, 12.6,
			       64.3, -163.0, -1.5 };
    cs.isGeocentric(true);
    const int size = numLocs * numCoords;
    double* pVals = new double[size];
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.fromProjForm(&pVals, numLocs, is2D);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/pCoords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(pVals, pCoords, size*sizeof(double));
    cs.fromProjForm(&pVals, numLocs, is2D);
    const double radToDeg = 180.0 / M_PI;
    for (int i=0; i < size; i += 3) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/(pCoords[i]*radToDeg),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i+1]/(pCoords[i+1]*radToDeg),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i+2]/pCoords[i+2],
				   tolerance);
    } // for
    delete[] pVals; pVals = 0;
  } // 3D
} // testFromProjForm

// version
// $Id$

// End of file 
