// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "TestSimpleGridDB.hh" // ISA TestSimpleGridDB

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridDB_Cases;

    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleGridDB_Cases {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    // Factories
    static
    TestSimpleGridDB_Data* Line1D(void);

    static
    TestSimpleGridDB_Data* Line2D(void);

    static
    TestSimpleGridDB_Data* Line3D(void);

    static
    TestSimpleGridDB_Data* Area2D(void);

    static
    TestSimpleGridDB_Data* Area3D(void);

    static
    TestSimpleGridDB_Data* Volume3D(void);

}; // class TestSimpleGridDB

// ------------------------------------------------------------------------------------------------
// Static test cases
TEST_CASE("TestSimpleGridDB::testConstructor", "[TestSimpleGridDB]") {
    spatialdata::spatialdb::TestSimpleGridDB::testConstructor();
}
TEST_CASE("TestSimpleGridDB::testAccessors", "[TestSimpleGridDB]") {
    spatialdata::spatialdb::TestSimpleGridDB::testAccessors();
}
TEST_CASE("TestSimpleGridDB::testSearch", "[TestSimpleGridDB]") {
    spatialdata::spatialdb::TestSimpleGridDB::testSearch();
}
TEST_CASE("TestSimpleGridDB::testDataIndex", "[TestSimpleGridDB]") {
    spatialdata::spatialdb::TestSimpleGridDB::testDataIndex();
}

// Data test cases
TEST_CASE("TestSimpleGridDB::testGetNamesDBValues", "[TestSimpleGridDB][Line1D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line1D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleGridDB::testQueryNearest", "[TestSimpleGridDB][Line1D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line1D()).testQueryNearest();
}
TEST_CASE("TestSimpleGridDB::testQueryLinear", "[TestSimpleGridDB][Line1D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line1D()).testQueryLinear();
}
TEST_CASE("TestSimpleGridDB::testRead", "[TestSimpleGridDB][Line1D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line1D()).testRead();
}

TEST_CASE("TestSimpleGridDB::testGetNamesDBValues", "[TestSimpleGridDB][Line2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line2D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleGridDB::testQueryNearest", "[TestSimpleGridDB][Line2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line2D()).testQueryNearest();
}
TEST_CASE("TestSimpleGridDB::testQueryLinear", "[TestSimpleGridDB][Line2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line2D()).testQueryLinear();
}
TEST_CASE("TestSimpleGridDB::testRead", "[TestSimpleGridDB][Line2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line2D()).testRead();
}

TEST_CASE("TestSimpleGridDB::testGetNamesDBValues", "[TestSimpleGridDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleGridDB::testQueryNearest", "[TestSimpleGridDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line3D()).testQueryNearest();
}
TEST_CASE("TestSimpleGridDB::testQueryLinear", "[TestSimpleGridDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line3D()).testQueryLinear();
}
TEST_CASE("TestSimpleGridDB::testRead", "[TestSimpleGridDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Line3D()).testRead();
}

TEST_CASE("TestSimpleGridDB::testGetNamesDBValues", "[TestSimpleGridDB][Area2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area2D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleGridDB::testQueryNearest", "[TestSimpleGridDB][Area2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area2D()).testQueryNearest();
}
TEST_CASE("TestSimpleGridDB::testQueryLinear", "[TestSimpleGridDB][Area2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area2D()).testQueryLinear();
}
TEST_CASE("TestSimpleGridDB::testRead", "[TestSimpleGridDB][Area2D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area2D()).testRead();
}

TEST_CASE("TestSimpleGridDB::testGetNamesDBValues", "[TestSimpleGridDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleGridDB::testQueryNearest", "[TestSimpleGridDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area3D()).testQueryNearest();
}
TEST_CASE("TestSimpleGridDB::testQueryLinear", "[TestSimpleGridDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area3D()).testQueryLinear();
}
TEST_CASE("TestSimpleGridDB::testRead", "[TestSimpleGridDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Area3D()).testRead();
}

TEST_CASE("TestSimpleGridDB::testGetNamesDBValues", "[TestSimpleGridDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Volume3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleGridDB::testQueryNearest", "[TestSimpleGridDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Volume3D()).testQueryNearest();
}
TEST_CASE("TestSimpleGridDB::testQueryLinear", "[TestSimpleGridDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Volume3D()).testQueryLinear();
}
TEST_CASE("TestSimpleGridDB::testRead", "[TestSimpleGridDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleGridDB(spatialdata::spatialdb::TestSimpleGridDB_Cases::Volume3D()).testRead();
}

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data*
spatialdata::spatialdb::TestSimpleGridDB_Cases::Line1D(void) {
    spatialdata::spatialdb::TestSimpleGridDB_Data* data = new TestSimpleGridDB_Data;assert(data);

    data->numX = 3;
    data->spaceDim = 1;
    data->numValues = 2;
    data->dataDim = 1;

    static const double dbX[3] = { -3.0, 1.0, 2.0, };
    data->dbX = dbX;

    static const double dbData[3*2] = {
        1.00000000e-01,  1.10000000e+00, // 0,0,0
        0.00000000e-01,  1.20000000e+00, // 1,0,0
        5.00000000e-01,  1.60000000e+00, // 2,0,0
    };
    data->dbData = dbData;

    static const char* names[2] = { "One", "Two" };
    data->names = names;

    static const char* units[2] = { "m", "m" };
    data->units = units;

    data->numQueries = 5;
    static const double queryNearest[5*(1+2)] = {
        -3.2,  1.00000000e-01,  1.10000000e+00, // (0)
        1.1,  0.00000000e-01,  1.20000000e+00, // (1)
        0.0,  0.00000000e-01,  1.20000000e+00, // (1)
        1.6,  5.00000000e-01,  1.60000000e+00, // (2)
        -2.0,  1.00000000e-01,  1.10000000e+00, // (0)
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(1+2)] = {
        -3.0,  1.00000000e-01,  1.10000000e+00, // (0)
        -1.0,  0.50000000e-01,  1.05000000e+00, // (0.5)
        1.25, 0.12500000e-01,  1.30000000e+00, // (1.25)
        -4.0,  0.0, 0.0, // not found
        3.0,  0.0, 0.0, // not fount
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = { 0, 0, 0, 1, 1, };
    data->errFlags = errFlags;

    data->filename = "data/grid_line1d.spatialdb";

    return data;
} // Line1D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data*
spatialdata::spatialdb::TestSimpleGridDB_Cases::Line2D(void) {
    spatialdata::spatialdb::TestSimpleGridDB_Data* data = new TestSimpleGridDB_Data;assert(data);

    data->numX = 1;
    data->numY = 3;
    data->spaceDim = 2;
    data->numValues = 2;
    data->dataDim = 1;

    static const double dbX[1] = { 2.0, };
    data->dbX = dbX;

    static const double dbY[3] = { -3.0, 1.0, 2.0, };
    data->dbY = dbY;

    static const double dbData[3*2] = {
        1.00000000e-01,  1.10000000e+00, // 0,0,0
        0.00000000e-01,  1.20000000e+00, // 1,0,0
        5.00000000e-01,  1.60000000e+00, // 2,0,0
    };
    data->dbData = dbData;

    static const char* names[2] = { "One", "Two" };
    data->names = names;

    static const char* units[2] = { "m", "m" };
    data->units = units;

    data->numQueries = 5;
    static const double queryNearest[5*(2+2)] = {
        3.8, -3.2,   1.00000000e-01,  1.10000000e+00, // (0)
        1.3,  1.1,   0.00000000e-01,  1.20000000e+00, // (1)
        6.0,  0.0,   0.00000000e-01,  1.20000000e+00, // (1)
        3.4,  1.6,   5.00000000e-01,  1.60000000e+00, // (2)
        3.5, -2.0,   1.00000000e-01,  1.10000000e+00, // (0)
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(2+2)] = {
        3.8, -3.0,   1.00000000e-01,  1.10000000e+00, // (0)
        1.3, -1.0,   0.50000000e-01,  1.05000000e+00, // (0.5)
        6.0,  1.25,  0.12500000e-01,  1.30000000e+00, // (1.25)
        3.4, -4.0,   0.0, 0.0, // not found
        3.5,  3.0,   0.0, 0.0, // not fount
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = { 0, 0, 0, 1, 1, };
    data->errFlags = errFlags;

    data->filename = "data/grid_line2d.spatialdb";

    return data;
} // Line2D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data*
spatialdata::spatialdb::TestSimpleGridDB_Cases::Line3D(void) {
    spatialdata::spatialdb::TestSimpleGridDB_Data* data = new TestSimpleGridDB_Data;assert(data);

    data->numX = 1;
    data->numY = 1;
    data->numZ = 3;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 1;

    static const double dbX[1] = { 2.0, };
    data->dbX = dbX;

    static const double dbY[1] = { 0.6, };
    data->dbY = dbY;

    static const double dbZ[3] = { -3.0, 1.0, 2.0, };
    data->dbZ = dbZ;

    static const double dbData[3*2] = {
        1.00000000e-01,  1.10000000e+00, // 0,0,0
        0.00000000e-01,  1.20000000e+00, // 1,0,0
        5.00000000e-01,  1.60000000e+00, // 2,0,0
    };
    data->dbData = dbData;

    static const char* names[2] = { "One", "Two" };
    data->names = names;

    static const char* units[2] = { "m", "m" };
    data->units = units;

    data->numQueries = 5;
    static const double queryNearest[5*(3+2)] = {
        3.8, 3.8, -3.2,   1.00000000e-01,  1.10000000e+00, // (0)
        1.3, 6.3,  1.1,   0.00000000e-01,  1.20000000e+00, // (1)
        6.0, 5.0,  0.0,   0.00000000e-01,  1.20000000e+00, // (1)
        3.4, 4.4,  1.6,   5.00000000e-01,  1.60000000e+00, // (2)
        3.5, 7.5, -2.0,   1.00000000e-01,  1.10000000e+00, // (0)
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(3+2)] = {
        3.8, 3.8, -3.0,   1.00000000e-01,  1.10000000e+00, // (0)
        1.3, 6.3, -1.0,   0.50000000e-01,  1.05000000e+00, // (0.5)
        6.0, 5.0,  1.25,  0.12500000e-01,  1.30000000e+00, // (1.25)
        3.4, 4.4, -4.0,   0.0, 0.0, // not found
        3.5, 7.5,  3.0,   0.0, 0.0, // not fount
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = { 0, 0, 0, 1, 1, };
    data->errFlags = errFlags;

    data->filename = "data/grid_line3d.spatialdb";

    return data;
} // Line3D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data*
spatialdata::spatialdb::TestSimpleGridDB_Cases::Area2D(void) {
    spatialdata::spatialdb::TestSimpleGridDB_Data* data = new TestSimpleGridDB_Data;assert(data);

    data->numX = 3;
    data->numY = 2;
    data->spaceDim = 2;
    data->numValues = 2;
    data->dataDim = 2;

    static const double dbX[3] = { -3.0, 1.0, 2.0, };
    data->dbX = dbX;

    static const double dbY[2] = { 2.0, 4.0, };
    data->dbY = dbY;

    static const double dbData[3*2*2] = {
        1.00000000e-01,  1.10000000e+00, // 0,0
        0.00000000e-01,  1.20000000e+00, // 1,0
        5.00000000e-01,  1.60000000e+00, // 2,0
        4.00000000e-01,  4.60000000e+00, // 0,1
        9.00000000e-01,  4.70000000e+00, // 1,1
        7.00000000e-01,  4.80000000e+00, // 2,1
    };
    data->dbData = dbData;

    static const char* names[2] = { "One", "Two" };
    data->names = names;

    static const char* units[2] = { "m", "m" };
    data->units = units;

    data->numQueries = 5;
    static const double queryNearest[5*(2+2)] = {
        -3.2,  3.8,  4.00000000e-01,  4.60000000e+00, // (0,1)
        1.1,  1.3,  0.00000000e-01,  1.20000000e+00, // (1,0)
        0.0, -6.0,  0.00000000e-01,  1.20000000e+00, // (1,0)
        1.6,  3.4,  7.00000000e-01,  4.80000000e+00, // (2,1)
        -2.0,  3.5,  4.00000000e-01,  4.60000000e+00, // (0,1)
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(2+2)] = {
        -3.0,  4.0,   4.00000000e-01,  4.60000000e+00, // (0,1)
        -1.0,  2.5,   2.00000000e-01,  2.02500000e+00, // (0.5, 0.25)
        1.25, 3.0,   4.87500000e-01,  3.01250000e+00, // (1.25, 0.5)
        0.0,  4.1,   0.0, 0.0, // not found
        3.0,  2.0,   0.0, 0.0, // not fount
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = { 0, 0, 0, 1, 1, };
    data->errFlags = errFlags;

    data->filename = "data/grid_area2d.spatialdb";

    return data;
} // Area2D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data*
spatialdata::spatialdb::TestSimpleGridDB_Cases::Area3D(void) {
    spatialdata::spatialdb::TestSimpleGridDB_Data* data = new TestSimpleGridDB_Data;assert(data);

    data->numX = 3;
    data->numY = 1;
    data->numZ = 2;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 2;

    static const double dbX[3] = { -3.0, 1.0, 2.0, };
    data->dbX = dbX;

    static const double dbY[1] = { 8.0, };
    data->dbY = dbY;

    static const double dbZ[2] = { 2.0, 4.0, };
    data->dbZ = dbZ;

    static const double dbData[3*1*2*2] = {
        1.00000000e-01,  1.10000000e+00, // 0,0
        0.00000000e-01,  1.20000000e+00, // 1,0
        5.00000000e-01,  1.60000000e+00, // 2,0
        4.00000000e-01,  4.60000000e+00, // 0,1
        9.00000000e-01,  4.70000000e+00, // 1,1
        7.00000000e-01,  4.80000000e+00, // 2,1
    };
    data->dbData = dbData;

    static const char* names[2] = { "One", "Two" };
    data->names = names;

    static const char* units[2] = { "m", "m" };
    data->units = units;

    data->numQueries = 5;
    static const double queryNearest[5*(3+2)] = {
        -3.2,  7.8,  3.8,  4.00000000e-01,  4.60000000e+00, // (0,1)
        1.1,  3.3,  1.3,  0.00000000e-01,  1.20000000e+00, // (1,0)
        0.0, -5.0, -6.0,  0.00000000e-01,  1.20000000e+00, // (1,0)
        1.6,  9.4,  3.4,  7.00000000e-01,  4.80000000e+00, // (2,1)
        -2.0,  2.5,  3.5,  4.00000000e-01,  4.60000000e+00, // (0,1)
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(3+2)] = {
        -3.0,  7.8, 4.0,   4.00000000e-01,  4.60000000e+00, // (0,1)
        -1.0,  3.3, 2.5,   2.00000000e-01,  2.02500000e+00, // (0.5, 0.25)
        1.25, 5.0, 3.0,   4.87500000e-01,  3.01250000e+00, // (1.25, 0.5)
        0.0,  9.4, 4.1,   0.0, 0.0, // not found
        3.0,  2.5, 2.0,   0.0, 0.0, // not found
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = { 0, 0, 0, 1, 1, };
    data->errFlags = errFlags;

    data->filename = "data/grid_area3d.spatialdb";

    return data;
} // Area3D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleGridDB_Data*
spatialdata::spatialdb::TestSimpleGridDB_Cases::Volume3D(void) {
    spatialdata::spatialdb::TestSimpleGridDB_Data* data = new TestSimpleGridDB_Data;assert(data);

    data->numX = 3;
    data->numY = 2;
    data->numZ = 4;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 3;

    static const double dbX[3] = { -3.0, 1.0, 2.0, };
    data->dbX = dbX;

    static const double dbY[2] = { 2.0, 4.0, };
    data->dbY = dbY;

    static const double dbZ[4] = { -0.5, 0.0, 1.0, 4.0, };
    data->dbZ = dbZ;

    static const double dbData[3*2*4*2] = {
        1.00000000e-01,  1.10000000e+00, // 0,0,0
        0.00000000e-01,  1.20000000e+00, // 1,0,0
        5.00000000e-01,  1.60000000e+00, // 2,0,0
        4.00000000e-01,  4.60000000e+00, // 0,1,0
        9.00000000e-01,  4.70000000e+00, // 1,1,0
        7.00000000e-01,  4.80000000e+00, // 2,1,0
        3.00000000e-01,  3.30000000e+00, // 0,0,1
        1.00000000e-01,  3.40000000e+00, // 1,0,1
        3.00000000e-01,  3.30000000e+00, // 2,0,1
        3.00000000e-01,  3.20000000e+00, // 0,1,1
        4.00000000e-01,  3.30000000e+00, // 1,1,1
        4.00000000e-01,  3.40000000e+00, // 2,1,1
        2.00000000e-01,  2.20000000e+00, // 0,0,2
        2.00000000e-01,  2.10000000e+00, // 1,0,2
        8.00000000e-01,  2.80000000e+00, // 2,0,2
        7.00000000e-01,  5.20000000e+00, // 0,1,2
        7.00000000e-01,  5.50000000e+00, // 1,1,2
        3.00000000e-01,  5.70000000e+00, // 2,1,2
        1.00000000e-01,  1.10000000e+00, // 0,0,3
        6.00000000e-01,  1.40000000e+00, // 1,0,3
        3.00000000e-01,  1.50000000e+00, // 2,0,3
        5.00000000e-01,  4.60000000e+00, // 0,1,3
        6.00000000e-01,  4.70000000e+00, // 1,1,3
        4.00000000e-01,  4.50000000e+00, // 2,1,3
    };
    data->dbData = dbData;

    static const char* names[2] = { "One", "Two" };
    data->names = names;

    static const char* units[2] = { "m", "m" };
    data->units = units;

    data->numQueries = 5;
    static const double queryNearest[5*(3+2)] = {
        -3.2,  3.8,  2.0,  7.00000000e-01,  5.20000000e+00, // (0,1,2)
        1.1,  1.3, -0.1,  1.00000000e-01,  3.40000000e+00, // (1,0,1)
        0.0, -6.0,  5.0,  6.00000000e-01,  1.40000000e+00, // (1,0,3)
        1.6,  3.4, -0.6,  7.00000000e-01,  4.80000000e+00, // (2,1,0)
        -2.0,  3.5,  0.9,  7.00000000e-01,  5.20000000e+00, // (0,1,2)
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(3+2)] = {
        -3.0,  4.0,  1.0,   7.00000000e-01,  5.20000000e+00, // (0,1,2)
        -1.0,  2.5,  2.5,   3.62500000e-01,  2.52500000e+00, // (0,5, 0.25, 2.5)
        1.25, 3.0,  0.25,  3.25000000e-01,  3.49062500e+00, // (1.25, 0.5, 1.25)
        0.0,  4.1,  0.0,   0.0, 0.0, // not found
        1.0,  2.0, -0.6,   0.0, 0.0, // not found
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = { 0, 0, 0, 1, 1, };
    data->errFlags = errFlags;

    data->filename = "data/grid_volume3d.spatialdb";

    return data;
} // Volume3D


// End of file
