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

/** @file tests/libtests/spatialdb/TestSimpleGridDB.hh
 *
 * @brief C++ TestSimpleGridDB object
 *
 * C++ unit testing for SimpleGridDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testsimplegriddb_hh)
#define spatialdata_spatialdb_testsimplegriddb_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/spatialdbfwd.hh"

namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridDB;
        class TestSimpleGridDB_Data;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleGridDB : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSimpleGridDB);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testSearch);
    CPPUNIT_TEST(testDataIndex);
    CPPUNIT_TEST(testGetNamesDBValues);
    CPPUNIT_TEST(testQueryNearest);
    CPPUNIT_TEST(testQueryLinear);
    CPPUNIT_TEST(testRead);

    CPPUNIT_TEST_SUITE_END_ABSTRACT();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Setup testing data.
    void setUp(void);

    /// Tear down testing data.
    void tearDown(void);

    /// Test constructor.
    void testConstructor(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test _search()
    void testSearch(void);

    /// Test _dataIndex()
    void testDataIndex(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test query() using nearest neighbor.
    void testQueryNearest(void);

    /// Test query() using linear interpolation.
    void testQueryLinear(void);

    /// Test read().
    void testRead(void);

    // PRIVATE METHODS ////////////////////////////////////////////////////
private:

    /** Populate database with data.
     *
     * @param db Database
     * @param data Data for database
     */
    void _setupDB(SimpleGridDB* const db);

    /** Test query method by doing query and checking values returned.
     *
     * @param db Database to query
     * @param names Names of values in database
     * @param queryData Query locations and expected values
     * @param flagsE Array of expected return values
     * @param numQueries Number of queries
     * @param spaceDim Number of coordinates per location
     * @param numVals Number of values in database
     */
    void _checkQuery(SimpleGridDB& db,
                     const char** const names,
                     const double* queryData,
                     const int* flagsE,
                     const size_t numQueries,
                     const size_t spaceDim,
                     const size_t numVals);

protected:

    // PROTECTED MEMBERS //////////////////////////////////////////////////

    TestSimpleGridDB_Data* _data; ///< Test data.

}; // class TestSimpleGridDB

class spatialdata::spatialdb::TestSimpleGridDB_Data {
    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Constructor
    TestSimpleGridDB_Data(void);

    /// Destructor
    ~TestSimpleGridDB_Data(void);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    /// @name Database information
    //@{
    size_t numX; ///< Number of locations in x dimension.
    size_t numY; ///< Number of locations in y dimension.
    size_t numZ; ///< Number of locations in z dimension.
    size_t spaceDim; ///< Spatial dimension for coordinates of locations
    size_t numValues; ///< Number of values per location in database
    size_t dataDim; ///< Spatial dimension of data in database
    const double* dbX; ///< Coordinates along x dimension.
    const double* dbY; ///< Coordinates along x dimension.
    const double* dbZ; ///< Coordinates along x dimension.
    const double* dbData; ///< Database data
    const char** names; ///< Names of values in database
    const char** units; ///< Units of values in database
    //@}

    /// @name Query information
    //@{
    size_t numQueries; ///< Number of queries
    const double* queryNearest; ///< Data for nearest neighbor queries
    const double* queryLinear; ///< Data for linear interpolation queries
    const int* errFlags; ///< Expected return values for queries
    //@}

    /// @io I/O information
    //@{
    const char* filename; ///< Filename of matching spatial database.
    //@}

};

#endif // spatialdata_spatialdb_testsimplegriddb_hh

// End of file
