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

#include "TestGeoCoordSys.h" // Implementation of class methods

#include "spatialdata/geocoords/GeoCoordSys.h" // USES GeoCoordSys

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::TestGeoCoordSys );

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::TestGeoCoordSys::testConstructor(void)
{ // testConstructor
  GeoCoordSys cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test copy constructor
void
spatialdata::TestGeoCoordSys::testCopyConstructor(void)
{ // testCopyConstructor
  GeoCoordSys cs;
  const char* projection = "tmerc";
  const char* ellipsoid = "clrk66";
  const char* datumHoriz = "NAD27";
  const char* datumVert = "MSL";
  const char* units = "km";
  cs.projection(projection);
  cs.ellipsoid(ellipsoid);
  cs.datumHoriz(datumHoriz);
  cs.datumVert(datumVert);
  cs.units(units);
  cs.initialize();
  GeoCoordSys csB(cs);
  CPPUNIT_ASSERT(0 == strcmp(projection, csB.projection()));
  CPPUNIT_ASSERT(0 == strcmp(ellipsoid, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcmp(datumHoriz, csB.datumHoriz()));
  CPPUNIT_ASSERT(0 == strcmp(datumVert, csB.datumVert()));
  CPPUNIT_ASSERT(0 == strcmp(units, csB.units()));
  CPPUNIT_ASSERT(0 != cs.coordsys());
} // testCopyConstructor

// ----------------------------------------------------------------------
// Test operator=
void
spatialdata::TestGeoCoordSys::testAssign(void)
{ // testAssign
  const char* projection = "sinu";
  const char* ellipsoid = "GRS80";
  const char* datumHoriz = "NAD83";
  const char* datumVert = "MSL";
  const char* units = "ft";
  GeoCoordSys cs;
  cs.projection(projection);
  cs.ellipsoid(ellipsoid);
  cs.datumHoriz(datumHoriz);
  cs.datumVert(datumVert);
  cs.units(units);
  cs.initialize();
  GeoCoordSys csB;
  csB = cs;
  CPPUNIT_ASSERT(0 == strcmp(projection, csB.projection()));
  CPPUNIT_ASSERT(0 == strcmp(ellipsoid, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcmp(datumHoriz, csB.datumHoriz()));
  CPPUNIT_ASSERT(0 == strcmp(datumVert, csB.datumVert()));
  CPPUNIT_ASSERT(0 == strcmp(units, csB.units()));
  CPPUNIT_ASSERT(0 != csB.coordsys());
} // testAssign

// ----------------------------------------------------------------------
// Test projection()
void
spatialdata::TestGeoCoordSys::testProjection(void)
{ // testProjection
  GeoCoordSys cs;
  const char* projection = "utm";
  cs.projection(projection);
  CPPUNIT_ASSERT(0 == strcmp(cs.projection(), projection));
} // testProjection

// ----------------------------------------------------------------------
// Test ellipsoid()
void
spatialdata::TestGeoCoordSys::testEllipsoid(void)
{ // testEllipsoid
  GeoCoordSys cs;
  const char* ellipsoid = "WGS83";
  cs.ellipsoid(ellipsoid);
  CPPUNIT_ASSERT(0 == strcmp(cs.ellipsoid(), ellipsoid));
} // testEllipsoid

// ----------------------------------------------------------------------
// Test datumHoriz()
void
spatialdata::TestGeoCoordSys::testDatumHoriz(void)
{ // testDatumHoriz
  GeoCoordSys cs;
  const char* datumHoriz = "NAD27";
  cs.datumHoriz(datumHoriz);
  CPPUNIT_ASSERT(0 == strcmp(cs.datumHoriz(), datumHoriz));
} // testDatum

// ----------------------------------------------------------------------
// Test datumVert()
void
spatialdata::TestGeoCoordSys::testDatumVert(void)
{ // testDatumVert
  GeoCoordSys cs;
  const char* datumVert = "NAD27";
  cs.datumVert(datumVert);
  CPPUNIT_ASSERT(0 == strcmp(cs.datumVert(), datumVert));
} // testDatumVert

// ----------------------------------------------------------------------
// Test units()
void
spatialdata::TestGeoCoordSys::testUnits(void)
{ // testUnits
  GeoCoordSys cs;
  const char* units = "km";
  cs.units(units);
  CPPUNIT_ASSERT(0 == strcmp(cs.units(), units));
} // testUnits

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::TestGeoCoordSys::testInitialize(void)
{ // testInitialize
  GeoCoordSys cs;
  cs.initialize();
} // testInitialize

// ----------------------------------------------------------------------
// Test coordsys()
void
spatialdata::TestGeoCoordSys::testCoordSys(void)
{ // testCoordSys
  GeoCoordSys cs;
  cs.initialize();
  const projPJ proj = cs.coordsys();
  CPPUNIT_ASSERT(0 != proj);
} // testCoordSys

// ----------------------------------------------------------------------
// Test operator==
void
spatialdata::TestGeoCoordSys::testEquals(void)
{ // testEquals
  const char* projectionA = "abc";
  const char* ellipsoidA = "def";
  const char* datumHorizA = "ghi";
  const char* datumVertA = "mno";
  const char* unitsA = "jkl";

  const char* projectionB = "mno";
  const char* ellipsoidB = "pqr";
  const char* datumHorizB = "stu";
  const char* datumVertB = "aac";
  const char* unitsB = "vwx";

  GeoCoordSys csA;
  csA.projection(projectionA);
  csA.ellipsoid(ellipsoidA);
  csA.datumHoriz(datumHorizA);
  csA.datumVert(datumVertA);
  csA.units(unitsA);

  GeoCoordSys csB(csA);

  CPPUNIT_ASSERT(csA == csB);

  csB = csA;
  csB.projection(projectionB);
  CPPUNIT_ASSERT( !(csA == csB) );

  csB = csA;
  csB.ellipsoid(ellipsoidB);
  CPPUNIT_ASSERT( !(csA == csB) );

  csB = csA;
  csB.datumHoriz(datumHorizB);
  CPPUNIT_ASSERT( !(csA == csB) );

  csB = csA;
  csB.datumVert(datumVertB);
  CPPUNIT_ASSERT( !(csA == csB) );

  csB = csA;
  csB.units(unitsB);
  CPPUNIT_ASSERT( !(csA == csB) );
} // testEquals

// version
// $Id: TestGeoCoordSys.cc,v 1.3 2005/07/02 00:21:13 baagaard Exp $

// End of file 
