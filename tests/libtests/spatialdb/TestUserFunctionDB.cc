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
#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include <string.h> // USES strcmp() and memcpy()

// ----------------------------------------------------------------------
// Setup testing data.
void
spatialdata::spatialdb::TestUserFunctionDB::setUp(void) {
    _db = new UserFunctionDB(); CPPUNIT_ASSERT(_db);
    _data = NULL;
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
void
spatialdata::spatialdb::TestUserFunctionDB::tearDown(void) {
    delete _db; _db = NULL;
    delete _data; _data = NULL;
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
    CPPUNIT_ASSERT_EQUAL(label, std::string(_db->label()));
} // testLabel

// ----------------------------------------------------------------------
// Test coordsys()
void
spatialdata::spatialdb::TestUserFunctionDB::testCoordsys(void) {
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(2);

    _db->coordsys(cs);
  
    CPPUNIT_ASSERT_EQUAL(cs.spaceDim(), _db->_cs->spaceDim());
} // testCoordsys

// ----------------------------------------------------------------------
// Test addValue()
void
spatialdata::spatialdb::TestUserFunctionDB::testAddValue(void) {
    _initializeDB();

    // Verify functions have been added
    const int numVals = _data->numVals;
    for (int i=0; i < numVals; ++i) {
	CPPUNIT_ASSERT_EQUAL(_data->functions[i].fn, _db->_functions[_data->values[i]].fn);
	CPPUNIT_ASSERT_EQUAL(_data->functions[i].units, _db->_functions[_data->values[i]].units);
    } // for
  
} // testCoordsys


// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestUserFunctionDB::testOpenClose(void) {
  _initializeDB();
  CPPUNIT_ASSERT(_data);
  
  // Test open() and close() with valid data.
  _db->open();
  // Verify scales
    const int numVals = _data->numVals;
    const double tolerance = 1.0e-6;
    for (int i=0; i < numVals; ++i) {
	CPPUNIT_ASSERT_DOUBLES_EQUAL(_data->functions[i].scale, _db->_functions[_data->values[i]].scale, tolerance);
    } // for
  _db->close();
  CPPUNIT_ASSERT(!_db->_queryFunctions);

  // Verify open() fails with spatial dimension mismatch.
  const int spaceDim = _data->cs->spaceDim();
  const int spaceDimBad = (spaceDim == 3) ? 2 : 3;
  _db->_cs->setSpaceDim(spaceDimBad);
  CPPUNIT_ASSERT_THROW(_db->open(), std::runtime_error);
  _db->_cs->setSpaceDim(spaceDim); // Reset space dimension.
  
  // Verify open() fails with bad units.
  _db->_functions[_data->values[0]].units = "dfkjasdf";
  CPPUNIT_ASSERT_THROW(_db->open(), std::runtime_error);

} // testOpenClose


// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestUserFunctionDB::testQueryVals(void) {
  CPPUNIT_ASSERT(_data);

  _initializeDB();
  _db->open();

  // Call queryVals().
  const int numVals = _data->numVals - 1;
  const char** names = (numVals > 0) ? new const char*[numVals] : NULL;
  for (int i=0; i < numVals; ++i) {
      names[i] = _data->values[numVals-1-i];
  } // for
  _db->queryVals(names, numVals);
  delete[] names; names = NULL;

  // Check result.
  for (int i=0; i < numVals; ++i) {
      const int j = numVals - 1 - i;
      CPPUNIT_ASSERT_EQUAL(_data->functions[j].fn, _db->_queryFunctions[i]->fn);
      CPPUNIT_ASSERT_EQUAL(_data->functions[j].units, _db->_queryFunctions[i]->units);
      CPPUNIT_ASSERT_EQUAL(_data->functions[j].scale, _db->_queryFunctions[i]->scale);
  } // for

  // Attempt to create query with no values.
  CPPUNIT_ASSERT_THROW(_db->queryVals(NULL, 0), std::runtime_error);
  
  // Attempt to create query with value not in database (verify failure).
  const char* badname = "lkdfjglkdfjgljsdf";
  CPPUNIT_ASSERT_THROW(_db->queryVals(&badname, 1), std::runtime_error);

  _db->close();
} // testQueryVals

#include <math.h>
// ----------------------------------------------------------------------
// Test query()
void
spatialdata::spatialdb::TestUserFunctionDB::testQuery(void) {
    CPPUNIT_ASSERT(_data);

    CPPUNIT_ASSERT(_data->cs);
    const int spaceDim = _data->cs->spaceDim();
    const int numVals = _data->numVals;
    const int numQueries = _data->numQueryPoints;
    double* values = (numVals > 0) ? new double[numVals] : NULL;
    
    _initializeDB();
    _db->open();

    // Call queryVals().
    const char** names = (numVals > 0) ? new const char*[numVals] : NULL;
    for (int i=0; i < numVals; ++i) {
	names[i] = _data->values[i];
    } // for
    _db->queryVals(names, numVals);
    delete[] names; names = NULL;

    // Call query() and check result.
    const double tolerance = 1.0e-6;
    for (int iQuery=0; iQuery < numQueries; ++iQuery) {	
	const int flag = _db->query(values, numVals, &_data->queryXYZ[iQuery*spaceDim], spaceDim, _data->cs);
	CPPUNIT_ASSERT_EQUAL(0, flag);
	
	for (int iVal=0; iVal < numVals; ++iVal) {
	    const double valueE = _data->queryValues[iQuery*numVals+iVal]*_data->functions[iVal].scale;
	    CPPUNIT_ASSERT_DOUBLES_EQUAL(valueE, values[iVal], tolerance);
	} // for
    } // for
    delete[] values; values = NULL;

    _db->close();
    
} // testQuery


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestUserFunctionDB::_initializeDB(void) {
    CPPUNIT_ASSERT(_db);
    CPPUNIT_ASSERT(_data);
    CPPUNIT_ASSERT(_data->numVals > 0);

    CPPUNIT_ASSERT(_data->cs);
    _db->coordsys(*_data->cs);
    
    const int numVals = _data->numVals;
    CPPUNIT_ASSERT(_data->values);
    for (int iVal=0; iVal < numVals; ++iVal) {
	_db->addValue(_data->values[iVal], _data->functions[iVal].fn, _data->functions[iVal].units.c_str());
    } // for
} // _initializeDB

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::TestUserFunctionDB_Data::TestUserFunctionDB_Data(void) :
    numVals(0),
    values(NULL),
    functions(NULL),
    cs(NULL),
    queryXYZ(NULL),
    queryValues(NULL),
    numQueryPoints(0)
{}

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::TestUserFunctionDB_Data::~TestUserFunctionDB_Data(void)
{
    delete cs; cs = NULL;
}




// End of file 
