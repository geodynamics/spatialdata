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

/** @file tests/libtests/spatialdb/TestUserFunctionDB.hh
 *
 * @brief C++ TestUserFunctionDB object
 *
 * C++ unit testing for UserFunctionDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testuserfunctiondb_hh)
#define spatialdata_spatialdb_testuserfunctiondb_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/UserFunctionDB.hh" // HASA UserFunctionDB::UserData

/// Namespace for spatial package
namespace spatialdata {
    namespace spatialdb {
        class TestUserFunctionDB;
        class TestUserFunctionDB_Data;
    } // spatialdb
} // spatialdata

/// C++ unit testing for UserFunctionDB
class spatialdata::spatialdb::TestUserFunctionDB : public CppUnit::TestFixture { // class TestUserFunctionDB
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestUserFunctionDB);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testDescription);
    CPPUNIT_TEST(testAddValue);
    CPPUNIT_TEST(testCoordsys);
    CPPUNIT_TEST(testOpenClose);
    CPPUNIT_TEST(testGetNamesDBValues);
    CPPUNIT_TEST(testQueryVals);
    CPPUNIT_TEST(testQuery);

    CPPUNIT_TEST_SUITE_END_ABSTRACT();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Setup testing data.
    void setUp(void);

    /// Tear down testing data.
    void tearDown(void);

    /// Test constructor
    void testConstructor(void);

    /// Test label()
    void testDescription(void);

    /// Test addValue()
    void testAddValue(void);

    /// Test coordsys()
    void testCoordsys(void);

    /// Test open() and close()
    void testOpenClose(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test setQueryValues().
    void testQueryVals(void);

    /// Test query().
    void testQuery(void);

    // PRIVATE METHODS ////////////////////////////////////////////////////
private:

    /** Populate database with data.
     *
     * @param db Database
     * @param data Data for database
     */
    void _initializeDB(void);

    virtual
    void _addValues(void) = 0;

protected:

    // PROTECTED MEMBERS //////////////////////////////////////////////////

    UserFunctionDB* _db; ///< Test subject.
    TestUserFunctionDB_Data* _data; ///< Test data.

}; // class TestUserFunctionDB

class spatialdata::spatialdb::TestUserFunctionDB_Data {
    // PUBLIC STRUCTS ///////////////////////////////////////////////////////
public:

    /// Structure for holding user data
    struct UserData {
        std::string name; ///< Name of value.
        std::string units; ///< Units for value of user function.
        double scale; ///< Scale to convert to SI units.
    }; // UserData

    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Constructor
    TestUserFunctionDB_Data(void);

    /// Destructor
    ~TestUserFunctionDB_Data(void);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    size_t numValues; ///< Number of values in spatial database.
    const UserData* values; ///< Names of values in spatial database.
    spatialdata::geocoords::CoordSys* cs; ///< Coordinate system.

    const double* queryXYZ; ///< Coordinate sof points in test queries.
    const double* queryValues; ///< Expected values in test queries.
    int numQueryPoints; ///< Number of points in test queries.

}; // TestUserFunctionDB_Data

#endif // spatialdata_spatialdb_testuserfunctiondb_hh

// End of file
