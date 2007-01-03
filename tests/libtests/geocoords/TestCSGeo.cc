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

#include "TestCSGeo.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include <math.h> // USES M_PI

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCSGeo );

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeo::testConstructor(void)
{ // testConstructor
  CSGeo cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test ellipsoid()
void
spatialdata::geocoords::TestCSGeo::testEllipsoid(void)
{ // testEllipsoid
  CSGeo cs;
  const char* ellipsoid = "WGS83";
  cs.ellipsoid(ellipsoid);
  CPPUNIT_ASSERT(0 == strcmp(cs.ellipsoid(), ellipsoid));
} // testEllipsoid

// ----------------------------------------------------------------------
// Test datumHoriz()
void
spatialdata::geocoords::TestCSGeo::testDatumHoriz(void)
{ // testDatumHoriz
  CSGeo cs;
  const char* datumHoriz = "NAD27";
  cs.datumHoriz(datumHoriz);
  CPPUNIT_ASSERT(0 == strcmp(cs.datumHoriz(), datumHoriz));
} // testDatum

// ----------------------------------------------------------------------
// Test datumVert()
void
spatialdata::geocoords::TestCSGeo::testDatumVert(void)
{ // testDatumVert
  CSGeo cs;
  const char* datumVert = "mean sea level";
  cs.datumVert(datumVert);
  CPPUNIT_ASSERT(0 == strcmp(cs.datumVert(), datumVert));
} // testDatumVert

// ----------------------------------------------------------------------
// Test isGeocentric()
void
spatialdata::geocoords::TestCSGeo::testGeocentric(void)
{ // testGeocentric
  CSGeo cs;
  CPPUNIT_ASSERT(!cs.isGeocentric());
  cs.isGeocentric(true);
  CPPUNIT_ASSERT(cs.isGeocentric());
  cs.isGeocentric(false);
  CPPUNIT_ASSERT(!cs.isGeocentric());
} // testGeocentric

// ----------------------------------------------------------------------
// Test toMeters()
void
spatialdata::geocoords::TestCSGeo::testToMeters(void)
{ // testToMeters
  CSGeo cs;
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs.toMeters(), tolerance);
  const double toMeters = 5.53;
  cs.toMeters(toMeters);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, cs.toMeters(), tolerance);
} // testToMeters

// ----------------------------------------------------------------------
// Test spaceDim()
void
spatialdata::geocoords::TestCSGeo::testSpaceDim(void)
{ // testSpaceDim
  CSGeo cs;
  CPPUNIT_ASSERT_EQUAL(3, cs.spaceDim());
  const int spaceDim = 2;
  cs.setSpaceDim(spaceDim);
  CPPUNIT_ASSERT_EQUAL(spaceDim, cs.spaceDim());
} // testSpaceDim

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestCSGeo::testInitialize(void)
{ // testInitialize
  CSGeo cs;
  cs.initialize();
  CPPUNIT_ASSERT(0 != cs._pCS);
} // testInitialize

// ----------------------------------------------------------------------
// Test toProjForm()
void
spatialdata::geocoords::TestCSGeo::testToProjForm(void)
{ // testToProjForm
  CSGeo cs;

  const double tolerance = 1.0e-6;

  { // 2D
    const int numLocs = 4;
    const int numDims = 2;
    const double coords[] = { 28.0, 23.0,
			      42.0, 34.0,
			      -12.0, 65.7,
			      64.3, -163.0 };
    cs.isGeocentric(true);
    cs.setSpaceDim(numDims);
    const int size = numLocs * numDims;
    double* vals = new double[size];
    memcpy(vals, coords, size*sizeof(double));
    cs.toProjForm(vals, numLocs, numDims);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/coords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(vals, coords, size*sizeof(double));
    cs.toProjForm(vals, numLocs, numDims);
    const double degToRad = M_PI / 180.0;
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/(coords[i]*degToRad),
				   tolerance);
    delete[] vals; vals = 0;
  } // 2D

  { // 3D
    const int numLocs = 4;
    const int numDims = 3;
    const double coords[] = { 28.0, 23.0, 3.4,
			      42.0, 34.0, 3.5,
			      -12.0, 65.7, 12.6,
			      64.3, -163.0, -1.5 };
    cs.isGeocentric(true);
    cs.setSpaceDim(numDims);
    const int size = numLocs * numDims;
    double* vals = new double[size];
    memcpy(vals, coords, size*sizeof(double));
    cs.toProjForm(vals, numLocs, numDims);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/coords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(vals, coords, size*sizeof(double));
    cs.toProjForm(vals, numLocs, numDims);
    const double degToRad = M_PI / 180.0;
    for (int i=0; i < size; i += 3) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/(coords[i]*degToRad),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i+1]/(coords[i+1]*degToRad),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i+2]/coords[i+2],
				   tolerance);
    } // for
    delete[] vals; vals = 0;
  } // 3D
} // testToProjForm

// ----------------------------------------------------------------------
// Test fromProjForm()
void
spatialdata::geocoords::TestCSGeo::testFromProjForm(void)
{ // testFromProjForm
  CSGeo cs;

  const double tolerance = 1.0e-6;

  { // 2D
    const int numLocs = 4;
    const int numDims = 2;
    const double coords[] = { 28.0, 23.0,
			       42.0, 34.0,
			       -12.0, 65.7,
			       64.3, -163.0 };
    cs.isGeocentric(true);
    cs.setSpaceDim(numDims);
    const int size = numLocs * numDims;
    double* vals = new double[size];
    memcpy(vals, coords, size*sizeof(double));
    cs.fromProjForm(vals, numLocs, numDims);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/coords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(vals, coords, size*sizeof(double));
    cs.fromProjForm(vals, numLocs, numDims);
    const double radToDeg = 180.0 / M_PI;
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/(coords[i]*radToDeg),
				   tolerance);
    delete[] vals; vals = 0;
  } // 2D

  { // 3D
    const int numLocs = 4;
    const int numDims = 3;
    const double coords[] = { 28.0, 23.0, 3.4,
			       42.0, 34.0, 3.5,
			       -12.0, 65.7, 12.6,
			       64.3, -163.0, -1.5 };
    cs.isGeocentric(true);
    cs.setSpaceDim(numDims);
    const int size = numLocs * numDims;
    double* vals = new double[size];
    memcpy(vals, coords, size*sizeof(double));
    cs.fromProjForm(vals, numLocs, numDims);
    for (int i=0; i < size; ++i)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/coords[i], tolerance);

    cs.isGeocentric(false);
    memcpy(vals, coords, size*sizeof(double));
    cs.fromProjForm(vals, numLocs, numDims);
    const double radToDeg = 180.0 / M_PI;
    for (int i=0; i < size; i += 3) {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/(coords[i]*radToDeg),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i+1]/(coords[i+1]*radToDeg),
				   tolerance);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i+2]/coords[i+2],
				   tolerance);
    } // for
    delete[] vals; vals = 0;
  } // 3D
} // testFromProjForm

// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSGeo::testPickle(void)
{ // testPickle
  const char* ellipsoid = "clrk66";
  const char* datumHoriz = "NAD27";
  const char* datumVert = "mean sea level";
  const bool isGeocentric = true;
  const double toMeters = 7.3;
  const int spaceDim = 2;

  CSGeo csA;
  csA.ellipsoid(ellipsoid);
  csA.datumHoriz(datumHoriz);
  csA.datumVert(datumVert);
  csA.isGeocentric(isGeocentric);
  csA.toMeters(toMeters);
  csA.setSpaceDim(spaceDim);

  std::stringstream s;
  csA.pickle(s);

  CSGeo csB;
  csB.unpickle(s);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT(0 == strcasecmp(ellipsoid, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcasecmp(datumHoriz, csB.datumHoriz()));
  CPPUNIT_ASSERT(0 == strcasecmp(datumVert, csB.datumVert()));
  CPPUNIT_ASSERT(isGeocentric == csB.isGeocentric());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, csB.toMeters(), tolerance);
  CPPUNIT_ASSERT_EQUAL(spaceDim, csB.spaceDim());
} // testPickle


// End of file 
