// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "TestSimpleDBQuery.hh" // ISA TestSimpleDBQuery

#include "catch2/catch_test_macros.hpp"

#include <cassert>

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDBQuery_3D;
    } // spatialdb
} // spatialdata

// ------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDBQuery_3D {
public:

    // Factory methods
    static
    TestSimpleDBQuery_Data* createData(void);

}; // TestSimpleDBQuery_3D

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSimpleDBQuery::testConstructor", "[TestSimpleDBQuery][3D]") {
    spatialdata::spatialdb::TestSimpleDBQuery(spatialdata::spatialdb::TestSimpleDBQuery_3D::createData()).testConstructor();
}
TEST_CASE("TestSimpleDBQuery::testAccessors", "[TestSimpleDBQuery][3D]") {
    spatialdata::spatialdb::TestSimpleDBQuery(spatialdata::spatialdb::TestSimpleDBQuery_3D::createData()).testAccessors();
}
TEST_CASE("TestSimpleDBQuery::testQueryVals", "[TestSimpleDBQuery][3D]") {
    spatialdata::spatialdb::TestSimpleDBQuery(spatialdata::spatialdb::TestSimpleDBQuery_3D::createData()).testQueryVals();
}
TEST_CASE("TestSimpleDBQuery::testDistSquared", "[TestSimpleDBQuery][3D]") {
    spatialdata::spatialdb::TestSimpleDBQuery(spatialdata::spatialdb::TestSimpleDBQuery_3D::createData()).testDistSquared();
}
TEST_CASE("TestSimpleDBQuery::testArea", "[TestSimpleDBQuery][3D]") {
    spatialdata::spatialdb::TestSimpleDBQuery(spatialdata::spatialdb::TestSimpleDBQuery_3D::createData()).testArea();
}
TEST_CASE("TestSimpleDBQuery::testVolume", "[TestSimpleDBQuery][3D]") {
    spatialdata::spatialdb::TestSimpleDBQuery(spatialdata::spatialdb::TestSimpleDBQuery_3D::createData()).testVolume();
}

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleDBQuery_Data*
spatialdata::spatialdb::TestSimpleDBQuery_3D::createData(void) {
    spatialdata::spatialdb::TestSimpleDBQuery_Data* data = new TestSimpleDBQuery_Data;assert(data);

    data->numLocs = 5;
    data->spaceDim = 3;
    data->numValues = 3;
    data->dataDim = 3;
    data->numPoints = 4;

    data->dist2 = 9.86850000e+00;
    data->area = 7.28666752e+00;
    data->volume = 2.95458000e+00;

    static const double dbCoordinates[5*3] = {
        0.00000000e+00,  0.00000000e+00,  0.00000000e+00,
        1.00000000e+00,  1.00000000e-01,  3.00000000e-01,
        2.00000000e+00,  2.00000000e-01,  2.00000000e-01,
        3.00000000e+00,  3.00000000e-01,  1.00000000e-01,
        4.00000000e+00,  4.00000000e-01,  9.00000000e-01,
    };
    data->dbCoordinates = dbCoordinates;

    static const double dbValues[5*3] = {
        1.1,  5.5,  3.4,
        2.2,  6.6,  4.5,
        3.3,  7.7,  5.6,
        4.4,  8.8,  6.7,
        4.5,  9.9,  7.8,
    };
    data->dbValues = dbValues;

    static const char* names[3] = {
        "one",
        "two",
        "three",
    };
    data->names = names;

    static const char* units[3] = {
        "m",
        "s",
        "m/s",
    };
    data->units = units;

    static const double coordinates[4*3] = {
        2.95000000e+00,  4.48000000e+00,  3.44000000e+00,
        5.80000000e+00,  5.32000000e+00,  4.46000000e+00,
        7.97000000e+00,  1.06200000e+01,  7.00000000e+00,
        8.38000000e+00,  1.30100000e+01,  9.34000000e+00,
    };
    data->coordinates = coordinates;

    static const double areaDir[3] = {
        -2.24547092e-01, -3.44848999e-01,  9.11404285e-01,
    };
    data->areaDir = areaDir;

    return data;
} // TestSimpleDBQuery_3D


// End of file
