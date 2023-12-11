// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/spatialdb/CompositeDB.hh" // USES CompositeDB

#include "spatialdata/spatialdb/UniformDB.hh" // USES UniformDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestCompositeDB;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestCompositeDB {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestCompositeDB(void);

    /// Test constructors
    static
    void testConstructors(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test setQueryValues() with values in dbA and dbB.
    void testQueryValsAB(void);

    /// Test setQueryValues() with values in dbA
    void testQueryValsA(void);

    /// Test setQueryValues() with values in dbB.
    void testQueryValsB(void);

    /// Test query() with values in both dbA and dbB.
    void testQueryAB(void);

    /// Test query() with values in dbA.
    void testQueryA(void);

    /// Test query() with values in dbB.
    void testQueryB(void);

private:

    UniformDB _dbA; ///< Spatial database A.
    UniformDB _dbB; ///< Spatial databsae B.

}; // class TestCompositeDB
// ------------------------------------------------------------------------------------------------
TEST_CASE("TestCompositeDB::testConstructors", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB::testConstructors();
}

TEST_CASE("TestCompositeDB::testAccessors", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testAccessors();
}
TEST_CASE("TestCompositeDB::testGetNamesDBValues", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testGetNamesDBValues();
}
TEST_CASE("TestCompositeDB::testQueryValsAB", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testQueryValsAB();
}
TEST_CASE("TestCompositeDB::testQueryValsA", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testQueryValsA();
}
TEST_CASE("TestCompositeDB::testQueryValsB", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testQueryValsB();
}
TEST_CASE("TestCompositeDB::testQueryAB", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testQueryAB();
}
TEST_CASE("TestCompositeDB::testQueryA", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testQueryA();
}
TEST_CASE("TestCompositeDB::testQueryB", "[TestCompositeDB]") {
    spatialdata::spatialdb::TestCompositeDB().testQueryB();
}

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestCompositeDB::TestCompositeDB(void) {
    { // initialize db A
        const size_t numValues = 3;
        const char* names[3] = { "one", "two", "three" };
        const char* units[3] = { "none", "none", "none" };
        const double values[3] = { 1.1, 2.2, 3.3 };
        _dbA.setData(names, units, values, numValues);
    } // initialize db A

    { // initialize db B
        const size_t numValues = 2;
        const char* names[2] = { "four", "five" };
        const char* units[2] = { "none", "none" };
        const double values[2] = { 4.4, 5.5 };
        _dbB.setData(names, units, values, numValues);
    } // initialize db B

} // setUp


// ----------------------------------------------------------------------
// Test constructors.
void
spatialdata::spatialdb::TestCompositeDB::testConstructors(void) {
    CompositeDB db;

    const std::string description("database A");
    CompositeDB db2(description.c_str());
    CHECK(description == std::string(db2.getDescription()));
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestCompositeDB::testAccessors(void) {
    const std::string label("database 2");

    CompositeDB db;
    db.setDescription(label.c_str());
    CHECK(label == std::string(db.getDescription()));

    // Set database A
    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    CHECK(db._dbA);
    CHECK(db._infoA);
    CHECK(!db._infoA->query_buffer);
    CHECK(!db._infoA->query_indices);
    CHECK(!db._infoA->query_size);
    REQUIRE(numNamesA == db._infoA->num_names);
    for (size_t i = 0; i < numNamesA; ++i) {
        CHECK(std::string(namesA[i]) == db._infoA->names_values[i]);
    } // for

    CHECK(!db._dbB);
    CHECK(!db._infoB);

    // Set database B
    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    CHECK(db._dbB);
    CHECK(db._infoB);
    CHECK(!db._infoB->query_buffer);
    CHECK(!db._infoB->query_indices);
    CHECK(!db._infoB->query_size);
    REQUIRE(numNamesB == db._infoB->num_names);
    for (size_t i = 0; i < numNamesB; ++i) {
        CHECK(std::string(namesB[i]) == db._infoB->names_values[i]);
    } // for
} // testAccessors


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestCompositeDB::testGetNamesDBValues(void) {
    CompositeDB db;

    const size_t numValuesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numValuesA);

    const size_t numValuesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numValuesB);

    const char** valueNames = NULL;
    size_t numValues = 0;
    db.getNamesDBValues(&valueNames, &numValues);
    REQUIRE(numValuesA + numValuesB == numValues);

    size_t iAB = 0;
    for (size_t iA = 0; iA < numValuesA; ++iA, ++iAB) {
        CHECK(std::string(namesA[iA]) == std::string(valueNames[iAB]));
    } // for
    for (size_t iB = 0; iB < numValuesB; ++iB, ++iAB) {
        CHECK(std::string(namesB[iB]) == std::string(valueNames[iAB]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ----------------------------------------------------------------------
// Test setQueryValues() with values in dbA and dbB.
void
spatialdata::spatialdb::TestCompositeDB::testQueryValsAB(void) {
    CompositeDB db;

    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    const size_t querySize = 3;
    const char* queryVals[3] = { "one", "five", "three" };

    db.open();

    { // Check defaults (all values in A and then all values in B).
        const size_t qsizeA = 2;
        const size_t qindicesA[qsizeA] = { 0, 1 };
        CHECK(db._dbA);
        CHECK(db._infoA);
        CHECK(db._infoA->query_buffer);
        CHECK(db._infoA->query_indices);
        REQUIRE(qsizeA == db._infoA->query_size);
        for (size_t i = 0; i < qsizeA; ++i) {
            CHECK(qindicesA[i] == db._infoA->query_indices[i]);
        } // for

        const size_t qsizeB = 1;
        const size_t qindicesB[1] = { 2 };
        CHECK(db._dbB);
        CHECK(db._infoB);
        CHECK(db._infoB->query_buffer);
        CHECK(db._infoB->query_indices);
        REQUIRE(qsizeB == db._infoB->query_size);
        for (size_t i = 0; i < qsizeB; ++i) {
            CHECK(qindicesB[i] == db._infoB->query_indices[i]);
        } // for
    } // check defaults

    db.setQueryValues(queryVals, querySize);
    db.close();

    const size_t qsizeA = 2;
    const size_t qindicesA[2] = { 0, 2 };
    CHECK(db._dbA);
    CHECK(db._infoA);
    CHECK(db._infoA->query_buffer);
    CHECK(db._infoA->query_indices);
    REQUIRE(qsizeA == db._infoA->query_size);
    for (size_t i = 0; i < qsizeA; ++i) {
        CHECK(qindicesA[i] == db._infoA->query_indices[i]);
    } // for

    const size_t qsizeB = 1;
    const size_t qindicesB[1] = { 1 };
    CHECK(db._dbB);
    CHECK(db._infoB);
    CHECK(db._infoB->query_buffer);
    CHECK(db._infoB->query_indices);
    REQUIRE(qsizeB == db._infoB->query_size);
    for (size_t i = 0; i < qsizeB; ++i) {
        CHECK(qindicesB[i] == db._infoB->query_indices[i]);
    } // for
} // testQueryValsAB


// ----------------------------------------------------------------------
// Test setQueryValues() with values in dbA.
void
spatialdata::spatialdb::TestCompositeDB::testQueryValsA(void) {
    CompositeDB db;

    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    const size_t querySize = 2;
    const char* queryVals[2] = { "one", "three" };

    db.open();
    db.setQueryValues(queryVals, querySize);
    db.close();

    const size_t qsizeA = 2;
    const size_t qindicesA[2] = { 0, 1 };
    CHECK(db._dbA);
    CHECK(db._infoA);
    CHECK(db._infoA->query_buffer);
    CHECK(db._infoA->query_indices);
    REQUIRE(qsizeA == db._infoA->query_size);
    for (size_t i = 0; i < qsizeA; ++i) {
        CHECK(qindicesA[i] == db._infoA->query_indices[i]);
    } // for

    const size_t qsizeB = 0;
    CHECK(db._dbB);
    CHECK(db._infoB);
    CHECK(!db._infoB->query_buffer);
    CHECK(!db._infoB->query_indices);
    CHECK(qsizeB == db._infoB->query_size);
} // testQueryValsA


// ----------------------------------------------------------------------
// Test setQueryValues() with values in dbB.
void
spatialdata::spatialdb::TestCompositeDB::testQueryValsB(void) {
    CompositeDB db;

    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    const size_t querySize = 1;
    const char* queryVals[1] = { "five" };

    db.open();
    db.setQueryValues(queryVals, querySize);
    db.close();

    const size_t qsizeA = 0;
    CHECK(db._dbA);
    CHECK(db._infoA);
    CHECK(!db._infoA->query_buffer);
    CHECK(!db._infoA->query_indices);
    REQUIRE(qsizeA == db._infoA->query_size);

    const size_t qsizeB = 1;
    const size_t qindicesB[1] = { 0 };
    CHECK(db._dbB);
    CHECK(db._infoB);
    CHECK(db._infoB->query_buffer);
    CHECK(db._infoB->query_indices);
    REQUIRE(qsizeB == db._infoB->query_size);
    for (size_t i = 0; i < qsizeB; ++i) {
        CHECK(qindicesB[i] == db._infoB->query_indices[i]);
    } // for
} // testQueryValsB


// ----------------------------------------------------------------------
// Test query() with values in both dbA and dbB.
void
spatialdata::spatialdb::TestCompositeDB::testQueryAB(void) {
    CompositeDB db;

    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    const size_t querySize = 2;
    const char* queryVals[2] = { "five", "one" };

    const size_t spaceDim = 2;
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(spaceDim);
    const double coords[2] = { 2.3, 5.6 };
    double data[querySize];
    const double valsE[2] = { 5.5, 1.1 };

    db.open();
    db.setQueryValues(queryVals, querySize);
    db.query(data, querySize, coords, spaceDim, &cs);
    db.close();

    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < querySize; ++i) {
        const double toleranceV = fabs(valsE[i]) > 0.0 ? tolerance*valsE[i] : tolerance;
        CHECK_THAT(data[i], Catch::Matchers::WithinAbs(valsE[i], toleranceV));
    } // for
} // testQueryAB


// ----------------------------------------------------------------------
// Test query() with values in dbA.
void
spatialdata::spatialdb::TestCompositeDB::testQueryA(void) { // testQueryA
    CompositeDB db;

    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    const size_t querySize = 1;
    const char* queryVals[1] = { "three" };

    const size_t spaceDim = 2;
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(spaceDim);
    const double coords[2] = { 2.3, 5.6 };
    double data[querySize];
    const double valsE[1] = { 3.3 };

    db.open();
    db.setQueryValues(queryVals, querySize);
    db.query(data, querySize, coords, spaceDim, &cs);
    db.close();

    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < querySize; ++i) {
        const double toleranceV = fabs(valsE[i]) > 0.0 ? tolerance*valsE[i] : tolerance;
        CHECK_THAT(data[i], Catch::Matchers::WithinAbs(valsE[i], toleranceV));
    } // for
} // testQueryA


// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestCompositeDB::testQueryB(void) {
    CompositeDB db;

    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    const size_t querySize = 1;
    const char* queryVals[1] = { "five", };

    const size_t spaceDim = 2;
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(spaceDim);
    const double coords[2] = { 2.3, 5.6 };
    double data[querySize];
    const double valsE[1] = { 5.5 };

    db.open();
    db.setQueryValues(queryVals, querySize);
    db.query(data, querySize, coords, spaceDim, &cs);
    db.close();

    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < querySize; ++i) {
        const double toleranceV = fabs(valsE[i]) > 0.0 ? tolerance*valsE[i] : tolerance;
        CHECK_THAT(data[i], Catch::Matchers::WithinAbs(valsE[i], toleranceV));
    } // for
} // testQueryB


// End of file
