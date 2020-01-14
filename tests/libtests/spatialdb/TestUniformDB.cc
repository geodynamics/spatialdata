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

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/UniformDB.hh" // USES UniformDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestUniformDB;
        class UniformDB; // USES UniformDB
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestUniformDB : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestUniformDB);

    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testSetData);
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

    /// Test queryVals()
    void testQueryVals(void);

    /// Test query()
    void testQuery(void);

}; // class TestUniformDB
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestUniformDB);

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestUniformDB::testConstructors(void) {
    UniformDB db;

    const std::string label("database A");
    UniformDB dbL(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(dbL.label()));
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors().
void
spatialdata::spatialdb::TestUniformDB::testAccessors(void) {
    const std::string label("database 2");

    UniformDB db;
    db.label(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(db.label()));
} // testAccessors


// ----------------------------------------------------------------------
// Test setData().
void
spatialdata::spatialdb::TestUniformDB::testSetData(void) {
    UniformDB db;

    const int numValues = 3;
    const char* names[numValues] = { "one", "two", "three" };
    const char* units[numValues] = { "m", "km", "cm" };
    const double values[numValues] = { 1.1, 2.2, 3.3 };
    const double valuesE[numValues] = { 1.1, 2.2e+3, 3.3e-2 };

    db.setData(names, units, values, numValues);

    CPPUNIT_ASSERT_EQUAL(numValues, db._numValues);
    for (int i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL(std::string(names[i]), db._names[i]);
    } // for

    for (int i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL(valuesE[i], db._values[i]);
    } // for
} // testSetData


// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestUniformDB::testQueryVals(void) {
    UniformDB db;

    const int numValues = 3;
    const char* names[numValues] = { "one", "two", "three" };
    const char* units[numValues] = { "none", "none", "none" };
    const double values[numValues] = { 1.1, 2.2, 3.3 };

    const int querySize = 2;
    const char* queryNames[querySize] = { "three", "two" };
    const int queryVals[querySize] = { 2, 1 };

    db.setData(names, units, values, numValues);
    db.queryVals(queryNames, querySize);

    CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
    for (int i = 0; i < querySize; ++i) {
        CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
    }
} // testQueryVals


// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestUniformDB::testQuery(void) {
    UniformDB db;

    const int numValues = 3;
    const char* names[numValues] = { "one", "two", "three" };
    const char* units[numValues] = { "none", "none", "none" };
    const double values[numValues] = { 1.1, 2.2, 3.3 };

    const int querySize = 2;
    const char* queryNames[querySize] = { "three", "two" };
    const int queryVals[querySize] = { 2, 1 };

    db.setData(names, units, values, numValues);
    db.queryVals(queryNames, querySize);

    const int spaceDim = 2;
    spatialdata::geocoords::CSCart cs;
    cs.setSpaceDim(spaceDim);
    const double coords[spaceDim] = { 2.3, 5.6 };
    double data[querySize];

    db.query(data, querySize, coords, spaceDim, &cs);

    for (int i = 0; i < querySize; ++i) {
        const double valE = values[queryVals[i]];
        CPPUNIT_ASSERT_EQUAL(valE, data[i]);
    } // for
} // testQuery


// End of file
