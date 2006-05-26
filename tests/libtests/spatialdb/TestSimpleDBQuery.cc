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

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB

#include "TestSimpleDBQuery.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleDBTypes.hh" // USES SimpleDBTypes

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBQuery );

// ----------------------------------------------------------------------
// Get static members
#include "data/TestSimpleDBQuery.dat"

// ----------------------------------------------------------------------
/// Setup test subject
void
spatialdata::spatialdb::TestSimpleDBQuery::setUp(void)
{ // setUp
  SimpleDB::DataStruct* pData = new SimpleDB::DataStruct;

  const int numCoords = 3;
  const int numLocs = NUMLOCS;
  const int numVals = NUMVALS;

  const int dataSize = numLocs*(numCoords+numVals);
  CPPUNIT_ASSERT(0 < dataSize);
  pData->data = new double[dataSize];
  memcpy(pData->data, DATA, dataSize*sizeof(double));

  pData->valNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valNames[i] = NAMES[i];

  pData->valUnits = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valUnits[i] = UNITS[i];

  pData->numLocs = numLocs;
  pData->numVals = numVals;
  pData->topology = TOPOLOGY;

  _pDB = new SimpleDB;
  _pDB->_pData = pData;
  _pQuery = new SimpleDBQuery(*_pDB);
} // setUp

// ----------------------------------------------------------------------
/// Cleanup test subject
void
spatialdata::spatialdb::TestSimpleDBQuery::tearDown(void)
{ // tearDown
  delete _pQuery; _pQuery = 0;
  delete _pDB; _pDB = 0;
} // tearDown

// ----------------------------------------------------------------------
/// Test Constructor()
void
spatialdata::spatialdb::TestSimpleDBQuery::testConstructor(void)
{ // testConstructor
  SimpleDB db;
  SimpleDBQuery query(db);
} // testConstructor

// ----------------------------------------------------------------------
/// Test DistSquared()
void
spatialdata::spatialdb::TestSimpleDBQuery::testDistSquared(void)
{ // testDistSquared
  CPPUNIT_ASSERT(2 <= NUMPTS);
  const int numCoords = 3;
  const double dist2 = 
    SimpleDBQuery::_distSquared(&COORDS[0], &COORDS[1*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dist2/DIST2, 1.0, tolerance);
} // testDistSquared

// ----------------------------------------------------------------------
/// Test Area()
void
spatialdata::spatialdb::TestSimpleDBQuery::testArea(void)
{ // testArea
  CPPUNIT_ASSERT(3 <= NUMPTS);
  const int numCoords = 3;
  double area = 0;
  double dir[numCoords];
  SimpleDBQuery::_area(&area, dir, &COORDS[0*numCoords], 
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
spatialdata::spatialdb::TestSimpleDBQuery::testVolume(void)
{ // testVolume
  CPPUNIT_ASSERT(4 <= NUMPTS);
  const int numCoords = 3;
  const double volume = 
    SimpleDBQuery::_volume(&COORDS[0*numCoords], &COORDS[1*numCoords], 
			   &COORDS[2*numCoords], &COORDS[3*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(volume/VOLUME, 1.0, tolerance);
} // testVolume

// ----------------------------------------------------------------------
/// Test QueryType()
void
spatialdata::spatialdb::TestSimpleDBQuery::testQueryType(void)
{ // testQueryType
  CPPUNIT_ASSERT(0 != _pQuery);

  { // test A
    const SimpleDB::QueryEnum queryType = SimpleDB::NEAREST;
    _pQuery->queryType(queryType);
    CPPUNIT_ASSERT(_pQuery->_queryType == queryType);
  } // test A

  { // test B
    const SimpleDB::QueryEnum queryType = SimpleDB::LINEAR;
    _pQuery->queryType(queryType);
    CPPUNIT_ASSERT(queryType == _pQuery->_queryType);
  } // test B
} // testQueryType

// ----------------------------------------------------------------------
/// Test QueryVals()
void
spatialdata::spatialdb::TestSimpleDBQuery::testQueryVals(void)
{ // testQueryVals
  CPPUNIT_ASSERT(0 != _pQuery);

  { // test A
    const char* names[] = { "one" };
    const int numNames = 1;
    const int vals[] = {0};
    _pQuery->queryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == _pQuery->_querySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == _pQuery->_queryVals[i]);
  } // test A

  { // test B
    const char* names[] = { "two" };
    const int numNames = 1;
    const int vals[] = {1};
    _pQuery->queryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == _pQuery->_querySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == _pQuery->_queryVals[i]);
  } // test B

  { // test C
    const char* names[] = { "two", "one" };
    const int numNames = 2;
    const int vals[] = {1, 0};
    _pQuery->queryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == _pQuery->_querySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == _pQuery->_queryVals[i]);
  } // test C
} // testQueryVals

// version
// $Id$

// End of file 
