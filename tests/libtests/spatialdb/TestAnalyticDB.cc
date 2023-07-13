// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "spatialdata/spatialdb/AnalyticDB.hh" // Test subject

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestAnalyticDB;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestAnalyticDB {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test constructors
    static
    void testConstructors(void);

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test setData()
    static
    void testSetData(void);

    /// Test getNamesDBValues().
    static
    void testGetNamesDBValues(void);

    /// Test setQueryValues()
    static
    void testQueryVals(void);

    /// Test query()
    static
    void testQuery(void);

    /// Test query() WGS84 -> UTM.
    static
    void testQueryUTM(void);

}; // class TestAnalyticDB

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestAnalyticDB::testConstructors", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testConstructors();
}
TEST_CASE("TestAnalyticDB::testAccessors", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testAccessors();
}
TEST_CASE("TestAnalyticDB::testSetData", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testSetData();
}
TEST_CASE("TestAnalyticDB::testGetNamesDBValues", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testGetNamesDBValues();
}
TEST_CASE("TestAnalyticDB::testQueryVals", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testQueryVals();
}
TEST_CASE("TestAnalyticDB::testQuery", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testQuery();
}
TEST_CASE("TestAnalyticDB::testQueryUTM", "[TestAnalyticDB]") {
    spatialdata::spatialdb::TestAnalyticDB::testQueryUTM();
}

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestAnalyticDB::testConstructors(void) {
    AnalyticDB db;

    const std::string description("database A");
    AnalyticDB dbL(description.c_str());
    CHECK(description == std::string(dbL.getDescription()));
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors().
void
spatialdata::spatialdb::TestAnalyticDB::testAccessors(void) {
    const std::string description("database 2");

    AnalyticDB db;
    db.setDescription(description.c_str());
    CHECK(description == std::string(db.getDescription()));
} // testAccessors


// ----------------------------------------------------------------------
// Test setData().
void
spatialdata::spatialdb::TestAnalyticDB::testSetData(void) {
    AnalyticDB db;

    const size_t numValuesE = 3;
    const char* names[numValuesE] = { "one", "two", "three" };
    const char* units[numValuesE] = { "m", "km", "cm" };
    const char* expressions[numValuesE] = { "x^2 + y^2", "x/z", "x + y + z" };

    db.setData(names, units, expressions, numValuesE);

    REQUIRE(numValuesE == db._numValues);
    for (size_t i = 0; i < numValuesE; ++i) {
        CHECK(std::string(names[i]) == db._names[i]);
    } // for

    for (size_t i = 0; i < numValuesE; ++i) {
        CHECK(std::string(expressions[i]) == db._expressions[i]);
    } // for

    CHECK(numValuesE == db._querySize);
} // testSetData


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestAnalyticDB::testGetNamesDBValues(void) {
    const size_t numValuesE = 3;
    const char* names[numValuesE] = { "one", "two", "three" };
    const char* units[numValuesE] = { "none", "none", "none" };
    const char* expressions[numValuesE] = { "x^2 + y^2", "x/z", "x + y + z" };

    AnalyticDB db;
    db.setData(names, units, expressions, numValuesE);

    const char** valueNames = NULL;
    size_t numValues = 0;
    db.getNamesDBValues(&valueNames, &numValues);
    REQUIRE(numValuesE == numValues);

    for (size_t i = 0; i < numValuesE; ++i) {
        CHECK(std::string(names[i]) == std::string(valueNames[i]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetNamesDBValues


// ----------------------------------------------------------------------
// Test setQueryValues().
void
spatialdata::spatialdb::TestAnalyticDB::testQueryVals(void) {
    AnalyticDB db;

    const size_t numValuesE = 3;
    const char* names[numValuesE] = { "one", "two", "three" };
    const char* units[numValuesE] = { "none", "none", "none" };
    const char* expressions[numValuesE] = { "x^2 + y^2", "x/z", "x + y + z" };

    const size_t querySize = 2;
    const char* queryNames[querySize] = { "three", "two" };
    const size_t queryVals[querySize] = { 2, 1 };

    db.setData(names, units, expressions, numValuesE);
    db.setQueryValues(queryNames, querySize);

    REQUIRE(querySize == db._querySize);
    for (size_t i = 0; i < querySize; ++i) {
        CHECK(queryVals[i] == db._queryValues[i]);
    } // for
} // testQueryVals


// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestAnalyticDB::testQuery(void) {
    AnalyticDB db;

    const size_t spaceDim = 3;
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(spaceDim);
    const double coords[spaceDim] = { 1.1, 2.3, 5.6 };

    const size_t numValues = 3;
    const char* names[numValues] = { "one", "two", "three" };
    const char* units[numValues] = { "none", "km", "cm" };
    const char* expressions[numValues] = { "x^2 + y^2", "x/z", "x + y + z" };
    const double scales[numValues] = { 1.0, 1000.0, 0.01 };
    const double values[numValues] = {
        coords[0]*coords[0],
        coords[0]/coords[2],
        coords[0]+coords[1]+coords[2],
    };

    const size_t querySize = 2;
    const char* queryNames[querySize] = { "three", "two" };
    const size_t queryVals[querySize] = { 2, 1 };

    db.setData(names, units, expressions, numValues);
    db.setQueryValues(queryNames, querySize);

    double data[querySize];
    db.query(data, querySize, coords, spaceDim, &cs);

    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < querySize; ++i) {
        const size_t index = queryVals[i];
        const double valE = scales[index] * values[index];
        const double toleranceV = fabs(valE) > 0.0 ? fabs(valE) * tolerance : tolerance;
        CHECK_THAT(data[i], Catch::Matchers::WithinAbs(valE, toleranceV));
    } // for
} // testQuery


// ----------------------------------------------------------------------
// Test query() with WGS84 -> UTM.
void
spatialdata::spatialdb::TestAnalyticDB::testQueryUTM(void) {
    AnalyticDB db;
    const size_t spaceDim = 3;

    spatialdata::geocoords::CSGeo csWGS84;
    csWGS84.setString("EPSG:4326");
    csWGS84.setSpaceDim(spaceDim);
    const double coordsLL[spaceDim] = { 37.50, -122.30, 5.6 };

    spatialdata::geocoords::CSGeo csUTM;
    csUTM.setString("EPSG:32610");
    csUTM.setSpaceDim(spaceDim);
    const double coordsUTM[spaceDim] = { 561873.454241, 4150571.437855, 5.6 };

    const size_t numValues = 3;
    const char* names[numValues] = { "one", "two", "three" };
    const char* units[numValues] = { "none", "km", "cm" };
    const char* expressions[numValues] = { "x^2 + y^2", "x/z", "x + y + z" };
    const double scales[numValues] = { 1.0, 1000.0, 0.01 };
    const double values[numValues] = {
        coordsUTM[0]*coordsUTM[0],
        coordsUTM[0]/coordsUTM[2],
        coordsUTM[0]+coordsUTM[1]+coordsUTM[2],
    };

    const size_t querySize = 2;
    const char* queryNames[querySize] = { "three", "two" };
    const size_t queryVals[querySize] = { 2, 1 };

    db.setCoordSys(csUTM);
    db.setData(names, units, expressions, numValues);
    db.setQueryValues(queryNames, querySize);

    double data[querySize];
    db.query(data, querySize, coordsLL, spaceDim, &csWGS84);

    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < querySize; ++i) {
        const size_t index = queryVals[i];
        const double valE = scales[index] * values[index];
        const double toleranceV = fabs(valE) > 0.0 ? fabs(valE) * tolerance : tolerance;
        CHECK_THAT(data[i], Catch::Matchers::WithinAbs(valE, toleranceV));
    } // for
} // testQueryUTM


// End of file
