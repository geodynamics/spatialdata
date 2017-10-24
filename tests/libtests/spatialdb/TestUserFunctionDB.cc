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

#include "TestUserFunctionDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/UserFunctionDB.hh" // USES UserFunctionDB
#include "spatialdata/spatialdb/SimpleGridAscii.hh" // USES SimpleGridAscii

#include "data/UserFunctionDBTestData.hh" // USES UserFunctionDBTestData

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include <string.h> // USES strcmp() and memcpy()

// ----------------------------------------------------------------------
// Setup testing data.
void
spatialdata::spatialdb::TestUserFunctionDB::setUp(void) {
    _db = new UserFunctionDB(); CPPUNIT_ASSERT(_db);
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
void
spatialdata::spatialdb::TestUserFunctionDB::tearDown(void) {
    delete _db; _db = NULL;
} // tearDown

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestUserFunctionDB::testConstructor(void) {
  UserFunctionDB db;
} // testConstructor

// ----------------------------------------------------------------------
// Test label()
void
spatialdata::spatialdb::TestUserFunctionDB::testLabel(void) {
    const std::string& label = "database 2";
    _db->label(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(_db->.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test coordsys()
void
spatialdata::spatialdb::TestUserFunctionDB::testCoordsys(void) {
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(2);

    _db->coordsys(&cs);
  
    CPPUNIT_ASSERT_EQUAL(cs.spaceDim(), _db->_cs->spaceDim());
} // testCoordsys

// ----------------------------------------------------------------------
// Test addValue()
void
spatialdata::spatialdb::TestUserFunctionDB::testAddValue(void) {
    _initializeDB();
  
    CPPUNIT_ASSERT_MESSAGE(":TODO: @brad Implement test.", false);
  
} // testCoordsys


// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestUserFunctionDB::testOpenClose(void) {
  _initializeDB();
  CPPUNIT_ASSERT(_data);
  
  // Test open() and close() with valid data.
  _db->open();
  CPPUNIT_ASSERT_MESSAGE(":TODO: @brad Implement test.", false);
  // Verify scales
  _db->close();


  // Verify open() fails with spatial dimension mismatch.
  const int spaceDim = _data->cs->spaceDim();
  const int spaceDimBad = (spaceDim == 3) : 2 ? 3;
  _db->cs->setSpaceDim(spaceDimBad);
  CPPUNIT_ASSERT_THROW(std::runtime_error, _db->open());
  _db->cs->setSpaceDim(spaceDim); // Reset space dimension.
  
  // Verify open() fails with bad units.
  _db._functions[_db->values[0]].units = "dfkjasdf";
  CPPUNIT_ASSERT_THROW(std::runtime_error, _db->open());

} // testOpenClose


// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestUserFunctionDB::testOpenCloseBadUnits(void) {
  _initializeDB();

  
} // testOpenCloseBadUnits


// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestUserFunctionDB::testQueryVals(void) {
  _initializeDB();

  // Query values in in reverse order

  // Attempt to create query with value not in database (verify failure).
  
  CPPUNIT_ASSERT_MESSAGE(":TODO: @brad Implement test.", false);
  
} // testQueryVals


// ----------------------------------------------------------------------
// Test query()
void
spatialdata::spatialdb::TestUserFunctionDB::testQuery(void) {
    // Attempt query() before setting up database.
    int flag = _db->query(&values, coords, dim);
    CPPUNIT_ASSERT(!flag);

    _initializeDB();
    CPPUNIT_ASSERT_MESSAGE(":TODO: @brad Implement test.", false);
  
} // testQuery


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestUserFunctionDB::_initializeDB(void) {
    CPPUNIT_ASSERT(_db);
    CPPUNIT_ASSERT(_data);
    CPPUNIT_ASSERT(_data->numVals > 0);
    
    _db->coordsys(_data->cs);
    
    const int numVals = _data->numVals;
    CPPUNIT_ASSERT(_data->values);
    for (int iVal=0; iVal < numVals; ++iVal) {
	_db->addValue(_data->values[iVal], _data->functions[iVal].fn, _data->functions[iVal].units);
    } // for
} // _initializeDB

// ----------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestUserFunctionDB::_checkQuery(UserFunctionDB& db,
						       char** const names,
						       const double* queryData,
						       const int* flagsE,
						       const int numQueries,
						       const int spaceDim,
						       const int numVals)
{ // _checkQuery
  CPPUNIT_ASSERT(names);
  CPPUNIT_ASSERT(queryData);
  CPPUNIT_ASSERT(numQueries);
  CPPUNIT_ASSERT(spaceDim);
  CPPUNIT_ASSERT(numVals);

  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = names[i];
  db.queryVals(valNames, numVals);
  
  double* vals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int locSize = spaceDim + numVals;
  spatialdata::geocoords::CSCart csCart;
  csCart.setSpaceDim(spaceDim);
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* coords = &queryData[iQuery*locSize];
    const double* valsE = &queryData[iQuery*locSize+spaceDim];
    const int err = db.query(vals, numVals, coords, spaceDim, &csCart);
    if (0 != flagsE)
      CPPUNIT_ASSERT(err == flagsE[iQuery]);
    else {
      CPPUNIT_ASSERT(0 == err);
      for (int iVal=0; iVal < numVals; ++iVal) {
	if (valsE[numVals-iVal-1] > tolerance) {
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[iVal]/valsE[numVals-iVal-1],
				       tolerance);
	} else {
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(valsE[numVals-iVal-1], vals[iVal],
				       tolerance);
	} // if/else
      } // for
    } // if/else
  } // for
  delete[] vals; vals = 0;
} // _checkQuery


// End of file 
