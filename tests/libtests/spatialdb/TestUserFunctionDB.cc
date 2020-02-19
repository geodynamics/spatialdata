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

#include <stdexcept> // USES std::runtime_error
#include <string.h> // USES strcmp() and memcpy()

// ----------------------------------------------------------------------
// Setup testing data.
void
spatialdata::spatialdb::TestUserFunctionDB::setUp(void) {
    _db = new UserFunctionDB();CPPUNIT_ASSERT(_db);
    _data = NULL;
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
void
spatialdata::spatialdb::TestUserFunctionDB::tearDown(void) {
    delete _db;_db = NULL;
    delete _data;_data = NULL;
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
    _db->setLabel(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(_db->getLabel()));
} // testLabel


// ----------------------------------------------------------------------
// Test coordsys()
void
spatialdata::spatialdb::TestUserFunctionDB::testCoordsys(void) {
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(2);

    _db->setCoordSys(cs);

    CPPUNIT_ASSERT_EQUAL(cs.getSpaceDim(), _db->_cs->getSpaceDim());
} // testCoordsys


// ----------------------------------------------------------------------
// Test addValue()
void
spatialdata::spatialdb::TestUserFunctionDB::testAddValue(void) {
    _initializeDB();

    // Verify functions have been added
    const int numVals = _data->numVals;
    for (int i = 0; i < numVals; ++i) {
        const std::string& name = _data->values[i].name;
        CPPUNIT_ASSERT(_db->_functions[name].fn);
        CPPUNIT_ASSERT_EQUAL(_data->values[i].units, _db->_functions[name].units);
    } // for

} // testAddValue


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
    for (int i = 0; i < numVals; ++i) {
        const std::string& name = _data->values[i].name;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(_data->values[i].scale, _db->_functions[name].scale, tolerance);
    } // for
    _db->close();
    CPPUNIT_ASSERT(!_db->_queryFunctions);

    // Verify open() fails with spatial dimension mismatch.
    const int spaceDim = _data->cs->getSpaceDim();
    const int spaceDimBad = (spaceDim == 3) ? 2 : 3;
    _db->_cs->setSpaceDim(spaceDimBad);
    CPPUNIT_ASSERT_THROW(_db->open(), std::runtime_error);
    _db->_cs->setSpaceDim(spaceDim); // Reset space dimension.

    // Verify open() fails with bad units.
    _db->_functions[_data->values[0].name].units = "abcd";
    CPPUNIT_ASSERT_THROW(_db->open(), std::runtime_error);

} // testOpenClose


// ----------------------------------------------------------------------
// Test setQueryValues().
void
spatialdata::spatialdb::TestUserFunctionDB::testQueryVals(void) {
    CPPUNIT_ASSERT(_data);

    _initializeDB();
    _db->open();

    // Call setQueryValues().
    const int numVals = _data->numVals - 1;
    const char** names = (numVals > 0) ? new const char*[numVals] : NULL;
    for (int i = 0; i < numVals; ++i) {
        names[i] = _data->values[numVals-1-i].name.c_str();
    } // for
    _db->setQueryValues(names, numVals);
    delete[] names;names = NULL;

    // Check result.
    for (int i = 0; i < numVals; ++i) {
        const int j = numVals - 1 - i;
        CPPUNIT_ASSERT(_db->_queryFunctions[j]->fn);
        CPPUNIT_ASSERT_EQUAL(_data->values[j].units, _db->_queryFunctions[i]->units);
        CPPUNIT_ASSERT_EQUAL(_data->values[j].scale, _db->_queryFunctions[i]->scale);
    } // for

    // Attempt to create query with no values.
    CPPUNIT_ASSERT_THROW(_db->setQueryValues(NULL, 0), std::runtime_error);

    // Attempt to create query with value not in database (verify failure).
    const char* badname = "lkdfjglkdfjgljsdf";
    CPPUNIT_ASSERT_THROW(_db->setQueryValues(&badname, 1), std::runtime_error);

    _db->close();
} // testQueryVals


// ----------------------------------------------------------------------
// Test query()
void
spatialdata::spatialdb::TestUserFunctionDB::testQuery(void) {
    CPPUNIT_ASSERT(_data);

    CPPUNIT_ASSERT(_data->cs);
    const int spaceDim = _data->cs->getSpaceDim();
    const size_t numVals = _data->numVals;
    const size_t numQueries = _data->numQueryPoints;
    double* values = (numVals > 0) ? new double[numVals] : NULL;

    _initializeDB();
    _db->open();

    // Call setQueryValues().
    const char** names = (numVals > 0) ? new const char*[numVals] : NULL;
    for (size_t i = 0; i < numVals; ++i) {
        names[i] = _data->values[i].name.c_str();
    } // for
    _db->setQueryValues(names, numVals);
    delete[] names;names = NULL;

    // Call query() and check result.
    const double tolerance = 1.0e-6;
    for (size_t iQuery = 0; iQuery < numQueries; ++iQuery) {
        const int flag = _db->query(values, numVals, &_data->queryXYZ[iQuery*spaceDim], spaceDim, _data->cs);
        CPPUNIT_ASSERT_EQUAL(0, flag);

        for (size_t iVal = 0; iVal < numVals; ++iVal) {
            const double valueE = _data->queryValues[iQuery*numVals+iVal]*_data->values[iVal].scale;
            CPPUNIT_ASSERT_DOUBLES_EQUAL(valueE, values[iVal], tolerance);
        } // for
    } // for
    delete[] values;values = NULL;

    _db->close();

} // testQuery


// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestUserFunctionDB::_initializeDB(void) {
    CPPUNIT_ASSERT(_db);
    CPPUNIT_ASSERT(_data);

    CPPUNIT_ASSERT(_data->cs);
    _db->setCoordSys(*_data->cs);

    _addValues();
} // _initializeDB


// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::TestUserFunctionDB_Data::TestUserFunctionDB_Data(void) :
    numVals(0),
    values(NULL),
    cs(NULL),
    queryXYZ(NULL),
    queryValues(NULL),
    numQueryPoints(0)
{}


// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::TestUserFunctionDB_Data::~TestUserFunctionDB_Data(void) {
    delete cs;cs = NULL;
}


// End of file
