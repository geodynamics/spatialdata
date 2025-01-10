// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "spatialdata/spatialdb/spatialdbfwd.hh"

#include <cstddef> // USES size_t
#include <cassert>

namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridDB;
        class TestSimpleGridDB_Data;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestSimpleGridDB(TestSimpleGridDB_Data* data);

    /// Destructor.
    ~TestSimpleGridDB(void);

    /// Test constructor.
    static
    void testConstructor(void);

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test _search()
    static
    void testSearch(void);

    /// Test _dataIndex()
    static
    void testDataIndex(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test query() using nearest neighbor.
    void testQueryNearest(void);

    /// Test query() using linear interpolation.
    void testQueryLinear(void);

    /// Test read().
    void testRead(void);

    // PRIVATE METHODS ////////////////////////////////////////////////////////////////////////////
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

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////////////////////////////

    TestSimpleGridDB_Data* _data; ///< Test data.

}; // class TestSimpleGridDB

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Data {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
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

// End of file
