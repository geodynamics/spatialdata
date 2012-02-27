// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleDBQuery.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery
#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData

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
  SimpleDBData* pData = new SimpleDBData;
  pData->allocate(data.numLocs, data.numVals, data.spaceDim,
		  data.dataDim);
  pData->data(data.dbData, data.numLocs, data.numVals);
  pData->coordinates(data.dbCoords, data.numLocs, data.spaceDim);
  pData->names(const_cast<const char**>(data.names), data.numVals);
  pData->units(const_cast<const char**>(data.units), data.numVals);

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
