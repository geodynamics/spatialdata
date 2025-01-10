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

#include "spatialdata/spatialdb/spatialdbfwd.hh" // USES SimpleDB, SimpleDBQuery

#include <cstddef> // USES size_t

/// Namespace for spatial package
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDBQuery;
        class TestSimpleDBQuery_Data;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDBQuery {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestSimpleDBQuery(TestSimpleDBQuery_Data* data);

    /// Destructor.
    ~TestSimpleDBQuery(void);

    /// Test constructor
    void testConstructor(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test setQueryValues()
    void testQueryVals(void);

    /// Test distSquared()
    void testDistSquared(void);

    /// Test area().
    void testArea(void);

    /// Test volume().
    void testVolume(void);

    // PROTECTED MEMBERS //////////////////////////////////////////////////////////////////////////
protected:

    /// Populdate database with values.
    void _initializeDB(void);

    // PROTECTED MEMBERS //////////////////////////////////////////////////////////////////////////
protected:

    SimpleDB* _db; ///< Database for test subject.
    SimpleDBQuery* _query; ///< Test subject.
    TestSimpleDBQuery_Data* _data; ///< Test data.

}; // class TestSimpleDBQuery

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDBQuery_Data {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor
    TestSimpleDBQuery_Data(void);

    /// Destructor
    ~TestSimpleDBQuery_Data(void);

    // PUBLIC MEMBERS /////////////////////////////////////////////////////////////////////////////
public:

    /// @name Database information
    //@{
    size_t numLocs; ///< Number of locations in database.
    size_t spaceDim; ///< Spatial dimension for coordinates of locations.
    size_t numValues; ///< Number of values per location in database.
    size_t dataDim; ///< Spatial dimension of data in database.
    const double* dbCoordinates; ///< Database locations.
    const double* dbValues; ///< Database values at locations.
    const char** names; ///< Names of values in database.
    const char** units; ///< Units of values in database.
    //@}

    /// @name Query information
    //@{
    size_t numPoints; ///< Number of points for locations
    const double* coordinates; ///< Coordinates of query locations
    double dist2; ///< Expected value for distance squared
    double area; ///< Expected value for area
    const double* areaDir; ///< Expected value for area direction
    double volume; ///< Expected value for volume
    //@}

}; // TestSimpleDBQuery_Data

// End of file
