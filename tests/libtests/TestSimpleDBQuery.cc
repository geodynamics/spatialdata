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

#include "spatialdata/SpatialDB.h" // USES SimpleDB
#include "spatialdata/SimpleDB.h" // USES SimpleDB

#include "TestSimpleDBQuery.h" // Implementation of class methods

#include "../../lib/SimpleDBQuery.h" // USES SimpleDBQuery
#include "../../lib/SimpleDBTypes.h" // USES SimpleDBTypes

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatial::TestSimpleDBQuery );

// ----------------------------------------------------------------------
// Get static members
#include "data/TestSimpleDBQuery.dat"

// ----------------------------------------------------------------------
/// Setup test subject
void
spatial::TestSimpleDBQuery::setUp(void)
{ // setUp
  SimpleDB::DataStruct* pData = new SimpleDB::DataStruct;

  const int numCoords = 3;
  const int numLocs = NUMLOCS;
  const int numVals = NUMVALS;

  const int dataSize = numLocs*(numCoords+numVals);
  FIREWALL(0 < dataSize);
  pData->Data = new double[dataSize];
  memcpy(pData->Data, DATA, dataSize*sizeof(double));

  pData->ValNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->ValNames[i] = NAMES[i];

  pData->NumLocs = numLocs;
  pData->NumVals = numVals;
  pData->Topology = TOPOLOGY;

  mpDB = new SimpleDB;
  mpDB->mpData = pData;
  mpQuery = new SimpleDBQuery(*mpDB);
} // setUp

// ----------------------------------------------------------------------
/// Cleanup test subject
void
spatial::TestSimpleDBQuery::tearDown(void)
{ // tearDown
  delete mpQuery; mpQuery = 0;
  delete mpDB; mpDB = 0;
} // tearDown

// ----------------------------------------------------------------------
/// Test Constructor()
void
spatial::TestSimpleDBQuery::testConstructor(void)
{ // testConstructor
  SimpleDB db;
  SimpleDBQuery query(db);
} // testConstructor

// ----------------------------------------------------------------------
/// Test DistSquared()
void
spatial::TestSimpleDBQuery::testDistSquared(void)
{ // testDistSquared
  FIREWALL(2 <= NUMPTS);
  const int numCoords = 3;
  const double dist2 = 
    SimpleDBQuery::DistSquared(&COORDS[0], &COORDS[1*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dist2/DIST2, 1.0, tolerance);
} // testDistSquared

// ----------------------------------------------------------------------
/// Test Area()
void
spatial::TestSimpleDBQuery::testArea(void)
{ // testArea
  FIREWALL(3 <= NUMPTS);
  const int numCoords = 3;
  double area = 0;
  double dir[numCoords];
  SimpleDBQuery::Area(&area, dir, &COORDS[0*numCoords], 
		      &COORDS[1*numCoords], &COORDS[2*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(area/AREA, 1.0, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dir[0]/AREADIR[0], 1.0, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dir[1]/AREADIR[1], 1.0, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dir[2]/AREADIR[2], 1.0, tolerance);
} // testArea

// ----------------------------------------------------------------------
/// Test Volume()
void
spatial::TestSimpleDBQuery::testVolume(void)
{ // testVolume
  FIREWALL(4 <= NUMPTS);
  const int numCoords = 3;
  const double volume = 
    SimpleDBQuery::Volume(&COORDS[0*numCoords], &COORDS[1*numCoords], 
			  &COORDS[2*numCoords], &COORDS[3*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(volume/VOLUME, 1.0, tolerance);
} // testVolume

// ----------------------------------------------------------------------
/// Test QueryType()
void
spatial::TestSimpleDBQuery::testQueryType(void)
{ // testQueryType
  FIREWALL(0 != mpQuery);

  { // test A
    const SimpleDB::QueryEnum queryType = SimpleDB::NEAREST;
    mpQuery->QueryType(queryType);
    CPPUNIT_ASSERT(mpQuery->mQueryType == queryType);
  } // test A

  { // test B
    const SimpleDB::QueryEnum queryType = SimpleDB::LINEAR;
    mpQuery->QueryType(queryType);
    CPPUNIT_ASSERT(queryType == mpQuery->mQueryType);
  } // test B
} // testQueryType

// ----------------------------------------------------------------------
/// Test QueryVals()
void
spatial::TestSimpleDBQuery::testQueryVals(void)
{ // testQueryVals
  FIREWALL(0 != mpQuery);

  { // test A
    const char* names[] = { "one" };
    const int numNames = 1;
    const int vals[] = {0};
    mpQuery->QueryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == mpQuery->mQuerySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == mpQuery->mQueryVals[i]);
  } // test A

  { // test B
    const char* names[] = { "two" };
    const int numNames = 1;
    const int vals[] = {1};
    mpQuery->QueryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == mpQuery->mQuerySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == mpQuery->mQueryVals[i]);
  } // test B

  { // test C
    const char* names[] = { "two", "one" };
    const int numNames = 2;
    const int vals[] = {1, 0};
    mpQuery->QueryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == mpQuery->mQuerySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == mpQuery->mQueryVals[i]);
  } // test C
} // testQueryVals

// version
// $Id: TestSimpleDBQuery.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
