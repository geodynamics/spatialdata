// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "spatialdata/spatialdb/spatialdbfwd.hh"

#include <cstddef> // USES size_t

namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDB;
        class TestSimpleDB_Data;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDB {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestSimpleDB(TestSimpleDB_Data* data);

    /// Destructor.
    ~TestSimpleDB(void);

    /// Test constructors.
    static
    void testConstructors(void);

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test queryNearest()
    void testQueryNearest(void);

    /// Test queryLinear()
    void testQueryLinear(void);

protected:

    // PROTECTED METHODS //////////////////////////////////////////////////////////////////////////

    /// Populate database with data.
    void _initializeDB(void);

protected:

    // PROTECTED MEMBERS //////////////////////////////////////////////////////////////////////////

    SimpleDB* _db; ///< Test subject
    TestSimpleDB_Data* _data; ///< Data for tests.

    // PRIVATE METHODS ////////////////////////////////////////////////////////////////////////////
private:

    /** Test query method by doing query and checking values returned.
     *
     * @param queryData Query locations and expected values
     * @param flagsE Array of expected return values
     */
    void _checkQuery(const double* queryData,
                     const int* flagsE);

}; // class TestSimpleDB

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDB_Data {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor
    TestSimpleDB_Data(void);

    /// Destructor
    ~TestSimpleDB_Data(void);

    // PUBLIC MEMBERS ////////////////////////////////////////////////////////////////////////////
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

// End of file
