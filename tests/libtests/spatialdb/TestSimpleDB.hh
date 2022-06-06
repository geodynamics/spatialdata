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

/** @file tests/libtests/spatialdb/TestSimpleDB.hh
 *
 * @brief C++ TestSimpleDB object
 *
 * C++ unit testing for SimpleDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testsimpledb_hh)
#define spatialdata_spatialdb_testsimpledb_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/spatialdbfwd.hh"

namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDB;
        class TestSimpleDB_Data;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleDB : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestSimpleDB);

    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testGetNamesDBValues);
    CPPUNIT_TEST(testQueryNearest);
    CPPUNIT_TEST(testQueryLinear);

    CPPUNIT_TEST_SUITE_END_ABSTRACT();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Initialize test subject.
    void setUp(void);

    /// Deallocate test data;
    void tearDown(void);

    /// Test constructors.
    void testConstructors(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test queryNearest()
    void testQueryNearest(void);

    /// Test queryLinear()
    void testQueryLinear(void);

protected:

    // PROTECTED METHODS //////////////////////////////////////////////////

    /// Populate database with data.
    void _initializeDB(void);

protected:

    // PROTECTED MEMBERS //////////////////////////////////////////////////

    SimpleDB* _db; ///< Test subject
    TestSimpleDB_Data* _data; ///< Data for tests.

    // PRIVATE METHODS ////////////////////////////////////////////////////
private:

    /** Test query method by doing query and checking values returned.
     *
     * @param queryData Query locations and expected values
     * @param flagsE Array of expected return values
     */
    void _checkQuery(const double* queryData,
                     const int* flagsE);

}; // class TestSimpleDB

class spatialdata::spatialdb::TestSimpleDB_Data {
    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Constructor
    TestSimpleDB_Data(void);

    /// Destructor
    ~TestSimpleDB_Data(void);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    size_t numLocs;
    size_t spaceDim;
    size_t numValues;
    size_t dataDim;
    size_t numQueries;

    const double* dbCoordinates;
    const double* dbValues;
    const char** names;
    const char** units;

    const double* queryNearest;
    const double* queryLinear;
    const int* errFlags;

};

#endif // spatialdata_spatialdb_testsimpledb_hh

// End of file
