// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file tests/libtests/spatialdb/TestUserFunctionDB.hh
 *
 * @brief C++ TestUserFunctionDB object
 *
 * C++ unit testing for UserFunctionDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testuserfunctiondb_hh)
#define spatialdata_spatialdb_testuserfunctiondb_hh

#include "spatialdata/spatialdb/UserFunctionDB.hh" // Test subject

/// Namespace for spatial package
namespace spatialdata {
    namespace spatialdb {
        class TestUserFunctionDB;
        class TestUserFunctionDB_Data;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestUserFunctionDB {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestUserFunctionDB(TestUserFunctionDB_Data* data,
                       UserFunctionDB* db);

    /// Destructor.
    ~TestUserFunctionDB(void);

    /// Test constructor
    static
    void testConstructor(void);

    /// Test setDescription()
    static
    void testDescription(void);

    /// Test coordsys()
    static
    void testCoordsys(void);

    /// Test addValue()
    void testAddValue(void);

    /// Test open() and close()
    void testOpenClose(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test setQueryValues().
    void testQueryVals(void);

    /// Test query().
    void testQuery(void);

protected:

    // PROTECTED MEMBERS //////////////////////////////////////////////////

    UserFunctionDB* _db; ///< Test subject.
    TestUserFunctionDB_Data* _data; ///< Test data.

}; // class TestUserFunctionDB

// ------------------------------------------------------------------------------------------------
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
