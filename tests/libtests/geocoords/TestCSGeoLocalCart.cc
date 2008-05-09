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

#include "TestCSGeoLocalCart.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CSGeoLocalCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeoLocalCart
#include "spatialdata/geocoords/CSGeoLocalCart.hh" // USES CSGeoLocalCart

#include <math.h> // USES fabs()
#include <string.h> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCSGeoLocalCart );

// ----------------------------------------------------------------------
#include "data/TestCSGeoLocalCart.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeoLocalCart::testConstructor(void)
{ // testConstructor
  CSGeoLocalCart cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test origin()
void
spatialdata::geocoords::TestCSGeoLocalCart::testOrigin(void)
{ // testOrigin
  CSGeoLocalCart cs;
  
  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLON, cs._originLon, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLAT, cs._originLat, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINELEV, cs._originElev, tolerance);
} // testOrigin

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestCSGeoLocalCart::testInitialize(void)
{ // testInitialize
  CSGeoLocalCart cs;

  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.initialize();

  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINX, cs._originX, tolerance*1e+4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._originY/_ORIGINY, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._originZ/_ORIGINZ, tolerance);  
} // testLocalOrigin

// ----------------------------------------------------------------------
// Test toProjForm()
void
spatialdata::geocoords::TestCSGeoLocalCart::testToProjForm(void)
{ // testToProjForm
  CSGeoLocalCart cs;
 
  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.initialize();

  const int numDims = 3;
  const int size = _NUMLOCS * numDims;
  double* vals = new double[size];
  memcpy(vals, _XYZLOCAL, size*sizeof(double));
  cs.toProjForm(vals, _NUMLOCS, numDims);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/_XYZECEF[i], tolerance);
  delete[] vals; vals = 0;
} // testToProjForm

// ----------------------------------------------------------------------
// Test fromProjForm()
void
spatialdata::geocoords::TestCSGeoLocalCart::testFromProjForm(void)
{ // testFromProjForm
  CSGeoLocalCart cs;

  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.initialize();

  const int numDims = 3;
  const int size = _NUMLOCS * numDims;
  double* vals = new double[size];
  memcpy(vals, _XYZECEF, size*sizeof(double));
  cs.fromProjForm(vals, _NUMLOCS, numDims);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/_XYZLOCAL[i], tolerance);
  delete[] vals; vals = 0;
} // testFromProjForm

// ----------------------------------------------------------------------
// Test radialDir().
void
spatialdata::geocoords::TestCSGeoLocalCart::testRadialDir(void)
{ // testRadialDir
  CSGeoLocalCart cs;

  cs.origin(-122.0, 37.75, 0.0);
  cs.initialize();

  const int numLocs = 3;
  const int numDims = 3;
  const double coords[] = {
    0.0, 0.0, 0.0,
    0.0, 0.0, -20e+3,
    10.0e+3, -25e+3, -5e+3,
  };
  const double dirsE[] = {
    0.0, -0.0032487084, 0.99999472,
    0.0, -0.0032589402, 0.99999469,
    0.0015710173, -0.0071787331, 0.999973,
  };
  
  const int size = numLocs * numDims;
  double* dirs = new double[size];
  cs.radialDir(dirs, coords, numLocs, numDims);

  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    if (fabs(dirsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dirs[i]/dirsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(dirsE[i], dirs[i], tolerance);
  delete[] dirs; dirs = 0;
} // testRadialDir

// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSGeoLocalCart::testPickle(void)
{ // testPickle
  const double toMeters = 4.5;

  CSGeoLocalCart csA;
  csA.ellipsoid(_ELLIPSOID);
  csA.datumHoriz(_DATUMHORIZ);
  csA.datumVert(_DATUMVERT);
  csA.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  csA.toMeters(toMeters);

  std::stringstream s;
  csA.pickle(s);

  CSGeoLocalCart csB;
  csB.unpickle(s);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT(0 == strcasecmp(_ELLIPSOID, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcasecmp(_DATUMHORIZ, csB.datumHoriz()));
  CPPUNIT_ASSERT(0 == strcasecmp(_DATUMVERT, csB.datumVert()));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLON, csB._originLon, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLAT, csB._originLat, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINELEV, csB._originElev, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, csB.toMeters(), tolerance);
} // testPickle


// End of file 
