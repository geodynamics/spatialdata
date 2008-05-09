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

#include "TestSimpleDBQuery.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleDBTypes.hh" // USES SimpleDBTypes

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include "data/SimpleDBQueryData.hh"

#include <string.h> // USES memcpy()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBQuery );

// ----------------------------------------------------------------------
// Test Constructor()
void
spatialdata::spatialdb::TestSimpleDBQuery::testConstructor(void)
{ // testConstructor
  SimpleDB db;
  SimpleDBQuery query(db);
} // testConstructor

// ----------------------------------------------------------------------
// Test QueryType()
void
spatialdata::spatialdb::TestSimpleDBQuery::testQueryType(void)
{ // testQueryType
  SimpleDB db;
  SimpleDBQuery query(db);

  { // test A
    const SimpleDB::QueryEnum queryType = SimpleDB::NEAREST;
    query.queryType(queryType);
    CPPUNIT_ASSERT(queryType == query._queryType);
  } // test A

  { // test B
    const SimpleDB::QueryEnum queryType = SimpleDB::LINEAR;
    query.queryType(queryType);
    CPPUNIT_ASSERT(queryType == query._queryType);
  } // test B
} // testQueryType

// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDBQuery::_setupDB(SimpleDB* const db,
						    const SimpleDBQueryData& data)
{ // _setupDB
  SimpleDB::DataStruct* pData = new SimpleDB::DataStruct;

  const int numCoords = data.spaceDim;
  const int numLocs = data.numLocs;
  const int numVals = data.numVals;

  const int dataSize = numLocs*(numCoords+numVals);
  CPPUNIT_ASSERT(0 < dataSize);
  pData->data = new double[dataSize];
  memcpy(pData->data, data.dbData, dataSize*sizeof(double));

  pData->valNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valNames[i] = data.names[i];

  pData->valUnits = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valUnits[i] = data.units[i];

  pData->numLocs = numLocs;
  pData->numVals = numVals;
  pData->dataDim = data.dataDim;

  db->_data = pData;
  db->_query = new SimpleDBQuery(*db);
  db->_cs = new spatialdata::geocoords::CSCart();
} // _setupDB

// ----------------------------------------------------------------------
// Test queryVals()
void
spatialdata::spatialdb::TestSimpleDBQuery::_testQueryVals(const SimpleDBQueryData& data)
{ // _testQueryVals
  SimpleDB db;
  _setupDB(&db, data);
  CPPUNIT_ASSERT(0 != db._query);

  { // test A
    const char* names[] = { "one" };
    const int numNames = 1;
    const int vals[] = {0};
    db._query->queryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == db._query->_querySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == db._query->_queryVals[i]);
  } // test A

  { // test B
    const char* names[] = { "two" };
    const int numNames = 1;
    const int vals[] = {1};
    db._query->queryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == db._query->_querySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == db._query->_queryVals[i]);
  } // test B

  { // test C
    const char* names[] = { "two", "one" };
    const int numNames = 2;
    const int vals[] = {1, 0};
    db._query->queryVals(names, numNames);
    CPPUNIT_ASSERT(numNames == db._query->_querySize);
    for (int i=0; i < numNames; ++i)
      CPPUNIT_ASSERT(vals[i] == db._query->_queryVals[i]);
  } // test C
} // _testQueryVals

#include <iostream>
// ----------------------------------------------------------------------
// Test distSquared()
void
spatialdata::spatialdb::TestSimpleDBQuery::_testDistSquared(const SimpleDBQueryData& data)
{ // _testDistSquared
  CPPUNIT_ASSERT(2 <= data.numPts);
  const int numCoords = data.spaceDim;
  const double dist2 = 
    SimpleDBQuery::_distSquared(&data.coords[0], &data.coords[1*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dist2/data.dist2, tolerance);
} // _testDistSquared

// ----------------------------------------------------------------------
// Test area()
void
spatialdata::spatialdb::TestSimpleDBQuery::_testArea(const SimpleDBQueryData& data)
{ // _testArea
  CPPUNIT_ASSERT(3 <= data.numPts);
  const int numCoords = data.spaceDim;
  double area = 0;
  double dir[numCoords];
  SimpleDBQuery::_area(&area, dir, &data.coords[0*numCoords], 
		       &data.coords[1*numCoords], &data.coords[2*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, area/data.area, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dir[0]/data.areaDir[0], 1.0, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dir[1]/data.areaDir[1], 1.0, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(dir[2]/data.areaDir[2], 1.0, tolerance);
} // _testArea

// ----------------------------------------------------------------------
// Test volume()
void
spatialdata::spatialdb::TestSimpleDBQuery::_testVolume(const SimpleDBQueryData& data)
{ // _testVolume
  CPPUNIT_ASSERT(4 <= data.numPts);
  const int numCoords = data.spaceDim;
  const double volume = 
    SimpleDBQuery::_volume(&data.coords[0*numCoords], 
			   &data.coords[1*numCoords], 
			   &data.coords[2*numCoords], 
			   &data.coords[3*numCoords]);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, volume/data.volume, tolerance);
} // _testVolume


// End of file 
