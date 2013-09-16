// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestGravityField.hh" // Implementation of class methods

#include "spatialdata/spatialdb/GravityField.hh" // USES GravityField

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/CSGeoLocalCart.hh" // USES CSGeoLocalCart

#include <string.h> // USES strcmp()
#include <math.h> // USES sqrt()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestGravityField );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestGravityField::testConstructor(void)
{ // testConstructor
  GravityField db;
} // testConstructor

// ----------------------------------------------------------------------
// Test label().
void
spatialdata::spatialdb::TestGravityField::testLabel(void)
{ // testLabel
  GravityField db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test gravityDir().
void
spatialdata::spatialdb::TestGravityField::testGravityDir(void)
{ // testGravityDir
  GravityField db;

  const double tolerance = 1.0e-06;

  { // Test default
    const double gravityDir[] = { 0.0, 0.0, -1.0 };
    for (int i=0; i < 3; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityDir[i], db._gravityDir[i], 
				   tolerance);
  } // Test default
  
  { // Test user-specified
    const double gravityDir[] = { 1.1, 2.2, 3.3 };
    const double mag = 1.1*sqrt(1 + 4 + 9);
    db.gravityDir(gravityDir[0], gravityDir[1], gravityDir[2]);
    for (int i=0; i < 3; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityDir[i]/mag, db._gravityDir[i], 
				   tolerance);
  } // Test user-specified
} // testGravityDir

// ----------------------------------------------------------------------
// Test acceleration().
void
spatialdata::spatialdb::TestGravityField::testAcceleration(void)
{ // testAcceleration
  GravityField db;

  const double tolerance = 1.0e-06;
  const double gSI = 9.80665;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(gSI, db._acceleration, tolerance);

  const double g = 4.5;
  db.gravAcceleration(g);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(g, db._acceleration, tolerance);
} // testAcceleration

// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestGravityField::testQueryVals(void)
{ // testQueryVals
  GravityField db;

  const int querySize = 2;
  const char* queryNames[] = { "z", "y" };
  const int queryVals[] = { 2, 1 };

  db.queryVals(queryNames, querySize);

  CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
  for (int i=0; i < querySize; ++i)
    CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
} // testQueryVals

// ----------------------------------------------------------------------
// Test query() with 2-D Cartesian coordinates.
void
spatialdata::spatialdb::TestGravityField::testQueryCart2(void)
{ // testQueryCart2
  const int spaceDim = 2;
  const double gacc = 2.0;
  const double gravityDir[] = { -0.6, -0.8, 0.0 };
  const double gravityE[] = { -1.2, -1.6 };
  const int querySize = spaceDim;
  const char* queryNames[] = { "x", "y" };
  
  GravityField db;
  db.gravityDir(gravityDir[0], gravityDir[1], gravityDir[2]);
  db.gravAcceleration(gacc);
  db.open();
  db.queryVals(queryNames, querySize);

  geocoords::CSCart cs;
  cs.setSpaceDim(spaceDim);
  
  double gravity[querySize];
  const double coords[] = { 2.5, 6.3 };
  const int err = db.query(gravity, querySize, coords, spaceDim, &cs);
  CPPUNIT_ASSERT_EQUAL(0, err);
  db.close();

  const double tolerance = 1.0e-06;
  for (int i=0; i < querySize; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityE[i], gravity[i], tolerance);
} // testQueryCart2

// ----------------------------------------------------------------------
// Test query() with 3-D Cartesian coordinates.
void
spatialdata::spatialdb::TestGravityField::testQueryCart3(void)
{ // testQueryCart3
  const int spaceDim = 3;
  const double gacc = 2.0;
  const double gravityDir[] = { 0.3, 0.4, -0.5 };
  const double sqrt2 = sqrt(2.0);
  const double gravityE[] = { 0.6*sqrt2, 0.8*sqrt2, -1.0*sqrt2 };
  
  GravityField db;
  db.gravityDir(gravityDir[0], gravityDir[1], gravityDir[2]);
  db.gravAcceleration(gacc);
  db.open();

  geocoords::CSCart cs;
  cs.setSpaceDim(spaceDim);
  
  double gravity[spaceDim];
  const double coords[] = { 2.5, 6.3, -2.4 };
  const int err = db.query(gravity, spaceDim, coords, spaceDim, &cs);
  CPPUNIT_ASSERT_EQUAL(0, err);
  db.close();

  const double tolerance = 1.0e-06;
  for (int i=0; i < spaceDim; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityE[i], gravity[i], tolerance);
} // testQueryCart3

// ----------------------------------------------------------------------
// Test query() with geographic coordinates.
void
spatialdata::spatialdb::TestGravityField::testQueryGeographic(void)
{ // testQueryGeographic
  const int spaceDim = 3;
  const double gacc = 2.0;
  const double gravityE[] = { 0.0, 0.0, -gacc };
  
  GravityField db;
  db.gravAcceleration(gacc);
  db.open();

  geocoords::CSGeo cs;
  
  double gravity[spaceDim];
  const double coords[] = { 2.5, 6.3, -2.4 };
  const int err = db.query(gravity, spaceDim, coords, spaceDim, &cs);
  CPPUNIT_ASSERT_EQUAL(0, err);
  db.close();

  const double tolerance = 1.0e-06;
  for (int i=0; i < spaceDim; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityE[i], gravity[i], tolerance);
} // testQueryGeographic

// ----------------------------------------------------------------------
// Test query() with projected geographic coordinates.
void
spatialdata::spatialdb::TestGravityField::testQueryGeoProj(void)
{ // testQueryGeoProj
  const int spaceDim = 3;
  const double gacc = 2.0;
  const double gravityE[] = { 0.0, 0.0, -gacc };
  
  GravityField db;
  db.gravAcceleration(gacc);
  db.open();

  geocoords::CSGeoProj cs;
  
  double gravity[spaceDim];
  const double coords[] = { 2.5, 6.3, -2.4 };
  const int err = db.query(gravity, spaceDim, coords, spaceDim, &cs);
  CPPUNIT_ASSERT_EQUAL(0, err);
  db.close();

  const double tolerance = 1.0e-06;
  for (int i=0; i < spaceDim; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityE[i], gravity[i], tolerance);
} // testQueryGeoProj

// ----------------------------------------------------------------------
// Test query() with geocentric coordinates.
void
spatialdata::spatialdb::TestGravityField::testQueryGeocentric(void)
{ // testQueryGeocentric
  const int spaceDim = 3;

  GravityField db;
  db.open();

  geocoords::CSGeo cs;
  cs.isGeocentric(true);
  cs.initialize();

  const double tolerance = 1.0e-06;
  const double gacc = 9.80665;

  const int numLocs = 5;
  const double coords[] = { 
    0.0, 0.0, 6356752.31, // (lon=0.0, lat=90.0)
    6378137.00, 0.0, 0.0, // (lon=0.0, lat=0.0)
    0.0, -6378137.00, 0.0, // (lon=-90.0, lat=0.0)
    -2684785.48, -4296554.90, 3861564.10, // (lon=-122.0, lat=37.5)
    -2680581.35, -4289826.89, 3855476.48, // (lon=-122.0, lat=37.5, elev=-10km)
  };
  const double gravityE[] = {
    0.0, 0.0, -gacc,
    -gacc, 0.0, 0.0,
    0.0, gacc, 0.0,
    4.1330772777176055, 6.6143062683936451, -5.9446622298329901,
    4.1330933324795938, 6.6143319681570834, -5.9446224726661976,
  };
  
  double gravity[spaceDim];
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc, index+=spaceDim) {
    const int err = db.query(gravity, spaceDim, &coords[index], spaceDim, &cs);
    CPPUNIT_ASSERT_EQUAL(0, err);

    for (int i=0; i < spaceDim; ++i)
      if (fabs(gravityE[index+i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, gravity[i]/gravityE[index+i], 
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityE[index+i], gravity[i], tolerance);
  } // for

  db.close();
} // testQueryGeocentric

// ----------------------------------------------------------------------
// Test query() with geocentric coordinates and local origin.
void
spatialdata::spatialdb::TestGravityField::testQueryGeoLocal(void)
{ // testQueryGeoLocal
  const int spaceDim = 3;

  GravityField db;
  db.open();

  geocoords::CSGeoLocalCart cs;
  cs.origin(-122.0, 37.75, 0.0);
  cs.initialize();

  const double gacc = 9.80665;

  const int numLocs = 3;
  const double coords[] = {
    0.0, 0.0, 0.0,
    0.0, 0.0, -20e+3,
    10.0e+3, -25e+3, -5e+3,
  };
  const double gravityE[] = {
    0.0, 0.0032487084*gacc, -0.99999472*gacc,
    0.0, 0.0032589402*gacc, -0.99999469*gacc,
    -0.0015710173*gacc, 0.0071787331*gacc, -0.999973*gacc,
  };
  const double tolerance = 1.0e-06;
  
  double gravity[spaceDim];
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc, index+=spaceDim) {
    const int err = db.query(gravity, spaceDim, &coords[index], spaceDim, &cs);
    CPPUNIT_ASSERT_EQUAL(0, err);

    for (int i=0; i < spaceDim; ++i)
      if (fabs(gravityE[index+i]) > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, gravity[i]/gravityE[index+i], 
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(gravityE[index+i], gravity[i], tolerance);
  } // for

  db.close();
} // testQueryGeoLocal


// End of file 
