// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "TestUserFunctionDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/UserFunctionDB.hh" // USES UserFunctionDB
#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()
#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::TestUserFunctionDB::TestUserFunctionDB(TestUserFunctionDB_Data* data,
                                                               UserFunctionDB* db) :
    _db(db),
    _data(data) {
    assert(_data);
    assert(_db);

    _db->setCoordSys(*_data->cs);
} // setUp


// ----------------------------------------------------------------------
// Tear down testing data.
spatialdata::spatialdb::TestUserFunctionDB::~TestUserFunctionDB(void) {
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
spatialdata::spatialdb::TestUserFunctionDB::testDescription(void) {
    UserFunctionDB db;

    const std::string& description = "database 2";
    db.setDescription(description.c_str());
    CHECK(description == std::string(db.getDescription()));
} // testDescription


// ----------------------------------------------------------------------
// Test coordsys()
void
spatialdata::spatialdb::TestUserFunctionDB::testCoordsys(void) {
    UserFunctionDB db;

    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(2);
    db.setCoordSys(cs);
    CHECK(cs.getSpaceDim() == db._cs->getSpaceDim());
} // testCoordsys


// ----------------------------------------------------------------------
// Test addValue()
void
spatialdata::spatialdb::TestUserFunctionDB::testAddValue(void) {
    const int numValues = _data->numValues;
    for (int i = 0; i < numValues; ++i) {
        const std::string& name = _data->values[i].name;
        assert(_db->_functions[name].fn);
        CHECK(_data->values[i].units == _db->_functions[name].units);
    } // for
} // testAddValue


// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestUserFunctionDB::testOpenClose(void) {
    assert(_data);
    assert(_db);

    // Test open() and close() with valid data.
    _db->open();
    // Verify scales
    const size_t numValues = _data->numValues;
    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < numValues; ++i) {
        const std::string& name = _data->values[i].name;
        CHECK_THAT(_db->_functions[name].scale, Catch::Matchers::WithinAbs(_data->values[i].scale, tolerance));
    } // for

    REQUIRE(numValues == _db->_querySize);

    _db->close();
    assert(!_db->_queryFunctions);

    // Verify open() fails with spatial dimension mismatch.
    const int spaceDim = _data->cs->getSpaceDim();
    const int spaceDimBad = (spaceDim == 3) ? 2 : 3;
    _db->_cs->setSpaceDim(spaceDimBad);
    CHECK_THROWS_AS(_db->open(), std::runtime_error);
    _db->_cs->setSpaceDim(spaceDim); // Reset space dimension.

    // Verify open() fails with bad units.
    _db->_functions[_data->values[0].name].units = "abcd";
    CHECK_THROWS_AS(_db->open(), std::runtime_error);

} // testOpenClose


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestUserFunctionDB::testGetNamesDBValues(void) {
    assert(_data);
    assert(_db);

    const char** valueNames = NULL;
    size_t numValues = 0;
    _db->getNamesDBValues(&valueNames, &numValues);
    REQUIRE(_data->numValues == numValues);

    for (size_t i = 0; i < numValues; ++i) {
        bool found = false;
        for (size_t iE = 0; iE < numValues; ++iE) {
            if (_data->values[iE].name == std::string(valueNames[i])) {
                found = true;
                break;
            } // if
        } // for
        if (!found) {
            FAIL("Could not find value '" << valueNames[i] << "' in UserFunctionDB test data.");
        } // if
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ----------------------------------------------------------------------
// Test setQueryValues().
void
spatialdata::spatialdb::TestUserFunctionDB::testQueryVals(void) {
    assert(_data);
    assert(_db);

    _db->open();

    // Call setQueryValues().
    const int numValues = _data->numValues - 1;
    const char** names = (numValues > 0) ? new const char*[numValues] : NULL;
    for (int i = 0; i < numValues; ++i) {
        names[i] = _data->values[numValues-1-i].name.c_str();
    } // for
    _db->setQueryValues(names, numValues);
    delete[] names;names = NULL;

    // Check result.
    for (int i = 0; i < numValues; ++i) {
        const int j = numValues - 1 - i;
        assert(_db->_queryFunctions[j]->fn);
        CHECK(_data->values[j].units == _db->_queryFunctions[i]->units);
        CHECK(_data->values[j].scale == _db->_queryFunctions[i]->scale);
    } // for

    // Attempt to create query with no values.
    CHECK_THROWS_AS(_db->setQueryValues(NULL, 0), std::invalid_argument);

    // Attempt to create query with value not in database (verify failure).
    const char* badname = "lkdfjglkdfjgljsdf";
    CHECK_THROWS_AS(_db->setQueryValues(&badname, 1), std::out_of_range);

    _db->close();
} // testQueryVals


// ----------------------------------------------------------------------
// Test query()
void
spatialdata::spatialdb::TestUserFunctionDB::testQuery(void) {
    assert(_data);

    assert(_data->cs);
    const int spaceDim = _data->cs->getSpaceDim();
    const size_t numValues = _data->numValues;
    const size_t numQueries = _data->numQueryPoints;
    double* values = (numValues > 0) ? new double[numValues] : NULL;

    _db->open();

    // Call setQueryValues().
    const char** names = (numValues > 0) ? new const char*[numValues] : NULL;
    for (size_t i = 0; i < numValues; ++i) {
        names[i] = _data->values[i].name.c_str();
    } // for
    _db->setQueryValues(names, numValues);
    delete[] names;names = NULL;

    // Call query() and check result.
    const double tolerance = 1.0e-6;
    for (size_t iQuery = 0; iQuery < numQueries; ++iQuery) {
        const int flag = _db->query(values, numValues, &_data->queryXYZ[iQuery*spaceDim], spaceDim, _data->cs);
        CHECK(0 == flag);

        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            const double valueE = _data->queryValues[iQuery*numValues+iVal]*_data->values[iVal].scale;
            CHECK_THAT(values[iVal], Catch::Matchers::WithinAbs(valueE, tolerance));
        } // for
    } // for
    delete[] values;values = NULL;

    _db->close();

} // testQuery


// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::TestUserFunctionDB_Data::TestUserFunctionDB_Data(void) :
    numValues(0),
    values(NULL),
    cs(NULL),
    queryXYZ(NULL),
    queryValues(NULL),
    numQueryPoints(0) {}


// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::TestUserFunctionDB_Data::~TestUserFunctionDB_Data(void) {
    delete cs;cs = NULL;
}


// End of file
