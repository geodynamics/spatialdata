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

#include "TestCoordSysLocal.h" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.h" // USES CoordSysLocal
#include "spatialdata/geocoords/CoordSysLocal.h" // USES CoordSysLocal

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCoordSysLocal );

// ----------------------------------------------------------------------
#include "data/TestCoordSysLocal.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCoordSysLocal::testConstructor(void)
{ // testConstructor
  CoordSysLocal cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test ellipsoid()
void
spatialdata::geocoords::TestCoordSysLocal::testLocalOrigin(void)
{ // testLocalOrigin
  CoordSysLocal cs;
  
  cs.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV,
		 _ELLIPSOID, _DATUMHORIZ, _DATUMVERT);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLON, cs._originLon, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLAT, cs._originLat, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINELEV, cs._originElev, tolerance);
  CPPUNIT_ASSERT(0 == strcmp(_ELLIPSOID, cs._ellipsoid.c_str()));
  CPPUNIT_ASSERT(0 == strcmp(_DATUMHORIZ, cs._datumHoriz.c_str()));
  CPPUNIT_ASSERT(0 == strcmp(_DATUMVERT, cs.datumVert()));

  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINX, cs._originX, tolerance*1e+4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._originY/_ORIGINY, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._originZ/_ORIGINZ, tolerance);  
} // testLocalOrigin

// ----------------------------------------------------------------------
// Test xyzToMeters()
void
spatialdata::geocoords::TestCoordSysLocal::testXYZToMeters(void)
{ // testXYZToMeters
  CoordSysLocal cs;
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._xyzToMeters, tolerance);
  const double xyzToMeters = 5.53;
  cs.xyzToMeters(xyzToMeters);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(xyzToMeters, cs._xyzToMeters, tolerance);
} // testXYZToMeters

// ----------------------------------------------------------------------
// Test toProjForm()
void
spatialdata::geocoords::TestCoordSysLocal::testToProjForm(void)
{ // testToProjForm
  CoordSysLocal cs;

  cs.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV,
		 _ELLIPSOID, _DATUMHORIZ, _DATUMVERT);
  const int numCoords = 3;
  const int size = _NUMLOCS * numCoords;
  double* pVals = new double[size];
  memcpy(pVals, _XYZLOCAL, size*sizeof(double));
  cs.toProjForm(&pVals, _NUMLOCS);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/_XYZECEF[i], tolerance);
  delete[] pVals; pVals = 0;
} // testToProjForm

// ----------------------------------------------------------------------
// Test fromProjForm()
void
spatialdata::geocoords::TestCoordSysLocal::testFromProjForm(void)
{ // testFromProjForm
  CoordSysLocal cs;

  cs.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV,
		 _ELLIPSOID, _DATUMHORIZ, _DATUMVERT);
  const int numCoords = 3;
  const int size = _NUMLOCS * numCoords;
  double* pVals = new double[size];
  memcpy(pVals, _XYZECEF, size*sizeof(double));
  cs.fromProjForm(&pVals, _NUMLOCS);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/_XYZLOCAL[i], tolerance);
  delete[] pVals; pVals = 0;
} // testFromProjForm

// version
// $Id$

// End of file 
