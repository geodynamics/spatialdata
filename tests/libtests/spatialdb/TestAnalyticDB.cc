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

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/AnalyticDB.hh" // USES AnalyticDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestAnalyticDB;
        class AnalyticDB; // USES AnalyticDB
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestAnalyticDB : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestAnalyticDB);

    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testSetData);
    CPPUNIT_TEST(testGetNamesDBValues);
    CPPUNIT_TEST(testQueryVals);
    CPPUNIT_TEST(testQuery);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test constructors
    void testConstructors(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test setData()
    void testSetData(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test setQueryValues()
    void testQueryVals(void);

    /// Test query()
    void testQuery(void);

}; // class TestAnalyticDB
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestAnalyticDB);

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestAnalyticDB::testConstructors(void) {
    AnalyticDB db;

    const std::string label("database A");
    AnalyticDB dbL(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(dbL.getDescription()));
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors().
void
spatialdata::spatialdb::TestAnalyticDB::testAccessors(void) {
    const std::string label("database 2");

    AnalyticDB db;
    db.setDescription(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(db.getDescription()));
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

    CPPUNIT_ASSERT_EQUAL(numValuesE, db._numValues);
    for (size_t i = 0; i < numValuesE; ++i) {
        CPPUNIT_ASSERT_EQUAL(std::string(names[i]), db._names[i]);
    } // for

    for (size_t i = 0; i < numValuesE; ++i) {
        CPPUNIT_ASSERT_EQUAL(std::string(expressions[i]), db._expressions[i]);
    } // for

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default query size.", numValuesE, db._querySize);
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
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValuesE, numValues);

    for (size_t i = 0; i < numValuesE; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names of values.",
                                     std::string(names[i]), std::string(valueNames[i]));
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

    CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
    for (size_t i = 0; i < querySize; ++i) {
        CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryValues[i]);
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
    const char* units[numValues] = { "none", "none", "none" };
    const char* expressions[numValues] = { "x^2 + y^2", "x/z", "x + y + z" };
    const double values[numValues] = { coords[0]*coords[0], coords[0]/coords[2], coords[0]+coords[1]+coords[2] };

    const size_t querySize = 2;
    const char* queryNames[querySize] = { "three", "two" };
    const size_t queryVals[querySize] = { 2, 1 };

    db.setData(names, units, expressions, numValues);
    db.setQueryValues(queryNames, querySize);
    double data[querySize];

    db.query(data, querySize, coords, spaceDim, &cs);

    for (size_t i = 0; i < querySize; ++i) {
        const double valE = values[queryVals[i]];
        CPPUNIT_ASSERT_EQUAL(valE, data[i]);
    } // for
} // testQuery


// End of file
