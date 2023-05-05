// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/CompositeDB.hh" // USES CompositeDB

#include "spatialdata/spatialdb/UniformDB.hh" // USES UniformDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

/// Namespace for spatial package
namespace spatialdata {
    namespace spatialdb {
        class TestCompositeDB;
        class CompositeDB; // USES CompositeDB
    } // spatialdb
} // spatialdata

/// C++ unit testing for CompositeDB
class spatialdata::spatialdb::TestCompositeDB : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestCompositeDB);

    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testGetNamesDBValues);
    CPPUNIT_TEST(testQueryValsAB);
    CPPUNIT_TEST(testQueryValsA);
    CPPUNIT_TEST(testQueryValsB);
    CPPUNIT_TEST(testQueryAB);
    CPPUNIT_TEST(testQueryA);
    CPPUNIT_TEST(testQueryB);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Setup.
    void setUp(void);

    /// Test constructors
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
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestCompositeDB);

// --------------------------
void
spatialdata::spatialdb::TestCompositeDB::setUp(void) {
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

    const std::string label("database A");
    CompositeDB db2(label.c_str());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in db label.", label, std::string(db2.getDescription()));
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestCompositeDB::testAccessors(void) {
    const std::string label("database 2");

    CompositeDB db;
    db.setDescription(label.c_str());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in label.", label, std::string(db.getDescription()));

    // Set database A
    const size_t numNamesA = 2;
    const char* namesA[2] = { "three", "one" };
    db.setDBA(&_dbA, namesA, numNamesA);

    CPPUNIT_ASSERT_MESSAGE("Mismatch in dbA.", db._dbA);
    CPPUNIT_ASSERT_MESSAGE("Mismatch in infoA", db._infoA);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query buffer.", !db._infoA->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query indicates.", !db._infoA->query_indices);
    CPPUNIT_ASSERT_MESSAGE("Expected 0 query size.", !db._infoA->query_size);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numNamesA, db._infoA->num_names);
    for (size_t i = 0; i < numNamesA; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names for dbA.", std::string(namesA[i]), db._infoA->names_values[i]);
    } // for

    CPPUNIT_ASSERT_MESSAGE("Expected NULL dbB.", !db._dbB);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL infoB", !db._infoB);

    // Set database B
    const size_t numNamesB = 1;
    const char* namesB[1] = { "five" };
    db.setDBB(&_dbB, namesB, numNamesB);

    CPPUNIT_ASSERT_MESSAGE("Mismatch in dbB.", db._dbB);
    CPPUNIT_ASSERT_MESSAGE("Mismatch in infoB", db._infoB);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query buffer.", !db._infoB->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query indicates.", !db._infoB->query_indices);
    CPPUNIT_ASSERT_MESSAGE("Expected 0 query size.", !db._infoB->query_size);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numNamesB, db._infoB->num_names);
    for (size_t i = 0; i < numNamesB; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names for dbB.", std::string(namesB[i]), db._infoB->names_values[i]);
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
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValuesA + numValuesB, numValues);

    size_t iAB = 0;
    for (size_t iA = 0; iA < numValuesA; ++iA, ++iAB) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names of values in db A.",
                                     std::string(namesA[iA]), std::string(valueNames[iAB]));
    } // for
    for (size_t iB = 0; iB < numValuesB; ++iB, ++iAB) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names of values in db B.",
                                     std::string(namesB[iB]), std::string(valueNames[iAB]));
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
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbA.", db._dbA);
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoA.", db._infoA);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbA.", qsizeA, db._infoA->query_size);
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query buffer for dbA.", db._infoA->query_buffer);
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query indices for dbA.", db._infoA->query_indices);
        for (size_t i = 0; i < qsizeA; ++i) {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices for dbA.", qindicesA[i], db._infoA->query_indices[i]);
        } // for

        const size_t qsizeB = 1;
        const size_t qindicesB[1] = { 2 };
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbB.", db._dbB);
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoB.", db._infoB);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbB.", qsizeB, db._infoB->query_size);
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query buffer for dbB.", db._infoB->query_buffer);
        CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query indices for dbB.", db._infoB->query_indices);
        for (size_t i = 0; i < qsizeB; ++i) {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices for dbB.", qindicesB[i], db._infoB->query_indices[i]);
        } // for
    } // check defaults

    db.setQueryValues(queryVals, querySize);
    db.close();

    const size_t qsizeA = 2;
    const size_t qindicesA[2] = { 0, 2 };
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbA.", db._dbA);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoA.", db._infoA);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbA.", qsizeA, db._infoA->query_size);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query buffer for dbA.", db._infoA->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query indices for dbA.", db._infoA->query_indices);
    for (size_t i = 0; i < qsizeA; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices for dbA.", qindicesA[i], db._infoA->query_indices[i]);
    } // for

    const size_t qsizeB = 1;
    const size_t qindicesB[1] = { 1 };
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbB.", db._dbB);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoB.", db._infoB);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbB.", qsizeB, db._infoB->query_size);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query buffer for dbB.", db._infoB->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query indices for dbB.", db._infoB->query_indices);
    for (size_t i = 0; i < qsizeB; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices for dbB.", qindicesB[i], db._infoB->query_indices[i]);
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
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbA.", db._dbA);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoA.", db._infoA);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbA.", qsizeA, db._infoA->query_size);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query buffer for dbA.", db._infoA->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query indices for dbA.", db._infoA->query_indices);
    for (size_t i = 0; i < qsizeA; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices for dbA.", qindicesA[i], db._infoA->query_indices[i]);
    } // for

    const size_t qsizeB = 0;
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbB.", db._dbB);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoB.", db._infoB);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbB.", qsizeB, db._infoB->query_size);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query buffer for dbB.", !db._infoB->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query indices for dbB.", !db._infoB->query_indices);
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
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbA.", db._dbA);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoA.", db._infoA);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbA.", qsizeA, db._infoA->query_size);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query buffer for dbA.", !db._infoA->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected NULL query indices for dbA.", !db._infoA->query_indices);

    const size_t qsizeB = 1;
    const size_t qindicesB[1] = { 0 };
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL dbB.", db._dbB);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL infoB.", db._infoB);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size for dbB.", qsizeB, db._infoB->query_size);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query buffer for dbB.", db._infoB->query_buffer);
    CPPUNIT_ASSERT_MESSAGE("Expected non-NULL query indices for dbB.", db._infoB->query_indices);
    for (size_t i = 0; i < qsizeB; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices for dbB.", qindicesB[i], db._infoB->query_indices[i]);
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

    for (size_t i = 0; i < querySize; ++i) {
        CPPUNIT_ASSERT_EQUAL(valsE[i], data[i]);
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

    for (size_t i = 0; i < querySize; ++i) {
        CPPUNIT_ASSERT_EQUAL(valsE[i], data[i]);
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

    for (size_t i = 0; i < querySize; ++i) {
        CPPUNIT_ASSERT_EQUAL(valsE[i], data[i]);
    } // for
} // testQueryB


// End of file
