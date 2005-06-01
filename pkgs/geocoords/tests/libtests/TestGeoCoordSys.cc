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
  const char* datum = "NAD27";
  const char* units = "km";
  cs.projection(projection);
  cs.ellipsoid(ellipsoid);
  cs.datum(datum);
  cs.units(units);
  cs.initialize();
  GeoCoordSys csB(cs);
  CPPUNIT_ASSERT(0 == strcmp(projection, csB.projection()));
  CPPUNIT_ASSERT(0 == strcmp(ellipsoid, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcmp(datum, csB.datum()));
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
  const char* datum = "NAD83";
  const char* units = "ft";
  GeoCoordSys cs;
  cs.projection(projection);
  cs.ellipsoid(ellipsoid);
  cs.datum(datum);
  cs.units(units);
  cs.initialize();
  GeoCoordSys csB;
  csB = cs;
  CPPUNIT_ASSERT(0 == strcmp(projection, csB.projection()));
  CPPUNIT_ASSERT(0 == strcmp(ellipsoid, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcmp(datum, csB.datum()));
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
// Test datum()
void
spatialdata::TestGeoCoordSys::testDatum(void)
{ // testDatum
  GeoCoordSys cs;
  const char* datum = "NAD27";
  cs.datum(datum);
  CPPUNIT_ASSERT(0 == strcmp(cs.datum(), datum));
} // testDatum

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
  const char* datumA = "ghi";
  const char* unitsA = "jkl";

  const char* projectionB = "mno";
  const char* ellipsoidB = "pqr";
  const char* datumB = "stu";
  const char* unitsB = "vwx";

  GeoCoordSys csA;
  csA.projection(projectionA);
  csA.ellipsoid(ellipsoidA);
  csA.datum(datumA);
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
  csB.datum(datumB);
  CPPUNIT_ASSERT( !(csA == csB) );

  csB = csA;
  csB.units(unitsB);
  CPPUNIT_ASSERT( !(csA == csB) );
} // testEquals

// version
// $Id: TestGeoCoordSys.cc,v 1.2 2005/05/31 23:08:39 baagaard Exp $

// End of file 
