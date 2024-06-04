// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "spatialdata/geocoords/geocoordsfwd.hh" // USES CoordSys

#include <cstddef> // HASA size_t

namespace spatialdata {
    namespace spatialdb {
        class TestGravityField;
        class TestGravityField_Data;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor.
    TestGravityField(TestGravityField_Data* data);

    /// Destructor.
    ~TestGravityField(void);

    /// Test constructor
    static
    void testConstructor(void);

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test getNamesDBValues().
    static
    void testGetNamesDBValues(void);

    /// Test setQueryValues()
    static
    void testQueryVals(void);

    /// Test query().
    void testQuery(void);

    // PROTECTED METHODS //////////////////////////////////////////////////////////////////////////
protected:

    TestGravityField_Data* _data; ///< Test data.

}; // class TestGravityField

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField_Data {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor
    TestGravityField_Data(void);

    /// Destructor
    ~TestGravityField_Data(void);

    // PUBLIC MEMBERS /////////////////////////////////////////////////////////////////////////////
public:

    spatialdata::geocoords::CoordSys* cs; ///< Coordinate system.
    double gravityAcc; ///< Gravitational acceleration.
    const double* gravityDir; ///< Direction of gravitational acceleration.

    size_t querySize; ///< Number of values in query (1, 2, or 3).
    const char* queryNames[3]; ///< Names of values in query.

    size_t numPoints; ///< Number of query points.
    const double* coordinates; ///< Coordinates of query point.
    const double* gravity; ///< Expected values for query.

}; // TestGravityField_Data

// End of file
