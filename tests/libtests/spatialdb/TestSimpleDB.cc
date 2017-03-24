// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB

#include "data/SimpleDBTestData.hh" // USES SimpleDBTestData

#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include <string.h> // USES strcmp() and memcpy()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDB );

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleDB::testConstructorA(void)
{ // testConstructorA
  SimpleDB db;
} // testConstructorA

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleDB::testConstructorB(void)
{ // testConstructorB
  const char* label = "database A";
  SimpleDB db(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testConstructorB

// ----------------------------------------------------------------------
// Test Label()
void
spatialdata::spatialdb::TestSimpleDB::testLabel(void)
{ // testLabel
  SimpleDB db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test query() using nearest neighbor
void
spatialdata::spatialdb::TestSimpleDB::_testQueryNearest(
					  const SimpleDBTestData& data)
{ // _testQueryNearest
  SimpleDB db;
  _setupDB(&db, data);
  db.queryType(SimpleDB::NEAREST);
  _checkQuery(db, data.names, data.queryNearest, 0,
	      data.numQueries, data.spaceDim, data.numVals);
} // _testQueryNearest

// ----------------------------------------------------------------------
// Test query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleDB::_testQueryLinear(
						  const SimpleDBTestData& data)
{ // _testQueryLinear
  SimpleDB db;
  _setupDB(&db, data);
  db.queryType(SimpleDB::LINEAR);
  _checkQuery(db, data.names, data.queryLinear, data.errFlags,
	      data.numQueries, data.spaceDim, data.numVals);
} // _testQueryLinear

// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDB::_setupDB(SimpleDB* const db,
					       const SimpleDBTestData& data)
{ // _setupDB
  SimpleDBData* dbData = new SimpleDBData;
  dbData->allocate(data.numLocs, data.numVals, data.spaceDim,
		   data.dataDim);
  dbData->data(data.dbData, data.numLocs, data.numVals);
  dbData->coordinates(data.dbCoords, data.numLocs, data.spaceDim);
  dbData->names(const_cast<const char**>(data.names), data.numVals);
  dbData->units(const_cast<const char**>(data.units), data.numVals);

  db->_data = dbData;
  db->_query = new SimpleDBQuery(*db);
  db->_cs = new spatialdata::geocoords::CSCart();
} // _setupDB

// ----------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(SimpleDB& db,
						  char** const names,
						  const double* queryData,
						  const int* flagsE,
						  const int numQueries,
						  const int spaceDim,
						  const int numVals)
{ // _checkQuery
  CPPUNIT_ASSERT(0 != names);
  CPPUNIT_ASSERT(0 != queryData);
  CPPUNIT_ASSERT(0 != numQueries);
  CPPUNIT_ASSERT(0 != spaceDim);
  CPPUNIT_ASSERT(0 != numVals);

  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = names[i];
  db.queryVals(valNames, numVals);
  
  double* vals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int locSize = spaceDim + numVals;
  spatialdata::geocoords::CSCart csCart;
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* coords = &queryData[iQuery*locSize];
    const double* valsE = &queryData[iQuery*locSize+spaceDim];
    const int err = db.query(vals, numVals, coords, spaceDim, &csCart);
    if (0 != flagsE)
      CPPUNIT_ASSERT(err == flagsE[iQuery]);
    else
      CPPUNIT_ASSERT(0 == err);
    for (int iVal=0; iVal < numVals; ++iVal)
      if (valsE[numVals-iVal-1] > tolerance)
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[iVal]/valsE[numVals-iVal-1],
				     tolerance);
      else
	CPPUNIT_ASSERT_DOUBLES_EQUAL(valsE[numVals-iVal-1], vals[iVal],
				     tolerance);
  } // for
  delete[] vals; vals = 0;
} // _checkQuery


// End of file 
