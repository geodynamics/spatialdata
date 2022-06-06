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

#include <portinfo>

#include "TestSimpleGridDB.hh" // ISA TestSimpleGridDB

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridDB_Line1D;
        class TestSimpleGridDB_Line2D;
        class TestSimpleGridDB_Line3D;
        class TestSimpleGridDB_Area2D;
        class TestSimpleGridDB_Area3D;
        class TestSimpleGridDB_Volume3D;
    } // spatialdb
} // spatialdata

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Line1D : public TestSimpleGridDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleGridDB_Line1D, TestSimpleGridDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleGridDB::setUp();
        CPPUNIT_ASSERT(_data);

        _data->numX = 3;
        _data->spaceDim = 1;
        _data->numValues = 2;
        _data->dataDim = 1;

        static const double dbX[3] = { -3.0, 1.0, 2.0, };
        _data->dbX = dbX;

        static const double dbData[3*2] = {
            1.00000000e-01,  1.10000000e+00, // 0,0,0
            0.00000000e-01,  1.20000000e+00, // 1,0,0
            5.00000000e-01,  1.60000000e+00, // 2,0,0
        };
        _data->dbData = dbData;

        static const char* names[2] = { "One", "Two" };
        _data->names = names;

        static const char* units[2] = { "m", "m" };
        _data->units = units;

        _data->numQueries = 5;
        static const double queryNearest[5*(1+2)] = {
            -3.2,  1.00000000e-01,  1.10000000e+00, // (0)
            1.1,  0.00000000e-01,  1.20000000e+00, // (1)
            0.0,  0.00000000e-01,  1.20000000e+00, // (1)
            1.6,  5.00000000e-01,  1.60000000e+00, // (2)
            -2.0,  1.00000000e-01,  1.10000000e+00, // (0)
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(1+2)] = {
            -3.0,  1.00000000e-01,  1.10000000e+00, // (0)
            -1.0,  0.50000000e-01,  1.05000000e+00, // (0.5)
            1.25, 0.12500000e-01,  1.30000000e+00, // (1.25)
            -4.0,  0.0, 0.0, // not found
            3.0,  0.0, 0.0, // not fount
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = { 0, 0, 0, 1, 1, };
        _data->errFlags = errFlags;

        _data->filename = "data/grid_line1d.spatialdb";
    } // setUp

}; // TestSimpleGriDB_Line1D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridDB_Line1D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Line2D : public TestSimpleGridDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleGridDB_Line2D, TestSimpleGridDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleGridDB::setUp();
        CPPUNIT_ASSERT(_data);

        _data->numX = 1;
        _data->numY = 3;
        _data->spaceDim = 2;
        _data->numValues = 2;
        _data->dataDim = 1;

        static const double dbX[1] = { 2.0, };
        _data->dbX = dbX;

        static const double dbY[3] = { -3.0, 1.0, 2.0, };
        _data->dbY = dbY;

        static const double dbData[3*2] = {
            1.00000000e-01,  1.10000000e+00, // 0,0,0
            0.00000000e-01,  1.20000000e+00, // 1,0,0
            5.00000000e-01,  1.60000000e+00, // 2,0,0
        };
        _data->dbData = dbData;

        static const char* names[2] = { "One", "Two" };
        _data->names = names;

        static const char* units[2] = { "m", "m" };
        _data->units = units;

        _data->numQueries = 5;
        static const double queryNearest[5*(2+2)] = {
            3.8, -3.2,   1.00000000e-01,  1.10000000e+00, // (0)
            1.3,  1.1,   0.00000000e-01,  1.20000000e+00, // (1)
            6.0,  0.0,   0.00000000e-01,  1.20000000e+00, // (1)
            3.4,  1.6,   5.00000000e-01,  1.60000000e+00, // (2)
            3.5, -2.0,   1.00000000e-01,  1.10000000e+00, // (0)
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(2+2)] = {
            3.8, -3.0,   1.00000000e-01,  1.10000000e+00, // (0)
            1.3, -1.0,   0.50000000e-01,  1.05000000e+00, // (0.5)
            6.0,  1.25,  0.12500000e-01,  1.30000000e+00, // (1.25)
            3.4, -4.0,   0.0, 0.0, // not found
            3.5,  3.0,   0.0, 0.0, // not fount
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = { 0, 0, 0, 1, 1, };
        _data->errFlags = errFlags;

        _data->filename = "data/grid_line2d.spatialdb";
    } // setUp

}; // TestSimpleGriDB_Line2D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridDB_Line2D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Line3D : public TestSimpleGridDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleGridDB_Line3D, TestSimpleGridDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleGridDB::setUp();
        CPPUNIT_ASSERT(_data);

        _data->numX = 1;
        _data->numY = 1;
        _data->numZ = 3;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 1;

        static const double dbX[1] = { 2.0, };
        _data->dbX = dbX;

        static const double dbY[1] = { 0.6, };
        _data->dbY = dbY;

        static const double dbZ[3] = { -3.0, 1.0, 2.0, };
        _data->dbZ = dbZ;

        static const double dbData[3*2] = {
            1.00000000e-01,  1.10000000e+00, // 0,0,0
            0.00000000e-01,  1.20000000e+00, // 1,0,0
            5.00000000e-01,  1.60000000e+00, // 2,0,0
        };
        _data->dbData = dbData;

        static const char* names[2] = { "One", "Two" };
        _data->names = names;

        static const char* units[2] = { "m", "m" };
        _data->units = units;

        _data->numQueries = 5;
        static const double queryNearest[5*(3+2)] = {
            3.8, 3.8, -3.2,   1.00000000e-01,  1.10000000e+00, // (0)
            1.3, 6.3,  1.1,   0.00000000e-01,  1.20000000e+00, // (1)
            6.0, 5.0,  0.0,   0.00000000e-01,  1.20000000e+00, // (1)
            3.4, 4.4,  1.6,   5.00000000e-01,  1.60000000e+00, // (2)
            3.5, 7.5, -2.0,   1.00000000e-01,  1.10000000e+00, // (0)
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(3+2)] = {
            3.8, 3.8, -3.0,   1.00000000e-01,  1.10000000e+00, // (0)
            1.3, 6.3, -1.0,   0.50000000e-01,  1.05000000e+00, // (0.5)
            6.0, 5.0,  1.25,  0.12500000e-01,  1.30000000e+00, // (1.25)
            3.4, 4.4, -4.0,   0.0, 0.0, // not found
            3.5, 7.5,  3.0,   0.0, 0.0, // not fount
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = { 0, 0, 0, 1, 1, };
        _data->errFlags = errFlags;

        _data->filename = "data/grid_line3d.spatialdb";
    } // setUp

}; // TestSimpleGriDB_Line3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridDB_Line3D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Area2D : public TestSimpleGridDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleGridDB_Area2D, TestSimpleGridDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleGridDB::setUp();
        CPPUNIT_ASSERT(_data);

        _data->numX = 3;
        _data->numY = 2;
        _data->spaceDim = 2;
        _data->numValues = 2;
        _data->dataDim = 2;

        static const double dbX[3] = { -3.0, 1.0, 2.0, };
        _data->dbX = dbX;

        static const double dbY[2] = { 2.0, 4.0, };
        _data->dbY = dbY;

        static const double dbData[3*2*2] = {
            1.00000000e-01,  1.10000000e+00, // 0,0
            0.00000000e-01,  1.20000000e+00, // 1,0
            5.00000000e-01,  1.60000000e+00, // 2,0
            4.00000000e-01,  4.60000000e+00, // 0,1
            9.00000000e-01,  4.70000000e+00, // 1,1
            7.00000000e-01,  4.80000000e+00, // 2,1
        };
        _data->dbData = dbData;

        static const char* names[2] = { "One", "Two" };
        _data->names = names;

        static const char* units[2] = { "m", "m" };
        _data->units = units;

        _data->numQueries = 5;
        static const double queryNearest[5*(2+2)] = {
            -3.2,  3.8,  4.00000000e-01,  4.60000000e+00, // (0,1)
            1.1,  1.3,  0.00000000e-01,  1.20000000e+00, // (1,0)
            0.0, -6.0,  0.00000000e-01,  1.20000000e+00, // (1,0)
            1.6,  3.4,  7.00000000e-01,  4.80000000e+00, // (2,1)
            -2.0,  3.5,  4.00000000e-01,  4.60000000e+00, // (0,1)
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(2+2)] = {
            -3.0,  4.0,   4.00000000e-01,  4.60000000e+00, // (0,1)
            -1.0,  2.5,   2.00000000e-01,  2.02500000e+00, // (0.5, 0.25)
            1.25, 3.0,   4.87500000e-01,  3.01250000e+00, // (1.25, 0.5)
            0.0,  4.1,   0.0, 0.0, // not found
            3.0,  2.0,   0.0, 0.0, // not fount
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = { 0, 0, 0, 1, 1, };
        _data->errFlags = errFlags;

        _data->filename = "data/grid_area2d.spatialdb";
    } // setUp

}; // TestSimpleGriDB_Area2D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridDB_Area2D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Area3D : public TestSimpleGridDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleGridDB_Area3D, TestSimpleGridDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleGridDB::setUp();
        CPPUNIT_ASSERT(_data);

        _data->numX = 3;
        _data->numY = 1;
        _data->numZ = 2;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 2;

        static const double dbX[3] = { -3.0, 1.0, 2.0, };
        _data->dbX = dbX;

        static const double dbY[1] = { 8.0, };
        _data->dbY = dbY;

        static const double dbZ[2] = { 2.0, 4.0, };
        _data->dbZ = dbZ;

        static const double dbData[3*1*2*2] = {
            1.00000000e-01,  1.10000000e+00, // 0,0
            0.00000000e-01,  1.20000000e+00, // 1,0
            5.00000000e-01,  1.60000000e+00, // 2,0
            4.00000000e-01,  4.60000000e+00, // 0,1
            9.00000000e-01,  4.70000000e+00, // 1,1
            7.00000000e-01,  4.80000000e+00, // 2,1
        };
        _data->dbData = dbData;

        static const char* names[2] = { "One", "Two" };
        _data->names = names;

        static const char* units[2] = { "m", "m" };
        _data->units = units;

        _data->numQueries = 5;
        static const double queryNearest[5*(3+2)] = {
            -3.2,  7.8,  3.8,  4.00000000e-01,  4.60000000e+00, // (0,1)
            1.1,  3.3,  1.3,  0.00000000e-01,  1.20000000e+00, // (1,0)
            0.0, -5.0, -6.0,  0.00000000e-01,  1.20000000e+00, // (1,0)
            1.6,  9.4,  3.4,  7.00000000e-01,  4.80000000e+00, // (2,1)
            -2.0,  2.5,  3.5,  4.00000000e-01,  4.60000000e+00, // (0,1)
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(3+2)] = {
            -3.0,  7.8, 4.0,   4.00000000e-01,  4.60000000e+00, // (0,1)
            -1.0,  3.3, 2.5,   2.00000000e-01,  2.02500000e+00, // (0.5, 0.25)
            1.25, 5.0, 3.0,   4.87500000e-01,  3.01250000e+00, // (1.25, 0.5)
            0.0,  9.4, 4.1,   0.0, 0.0, // not found
            3.0,  2.5, 2.0,   0.0, 0.0, // not found
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = { 0, 0, 0, 1, 1, };
        _data->errFlags = errFlags;

        _data->filename = "data/grid_area3d.spatialdb";
    } // setUp

}; // TestSimpleGriDB_Area3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridDB_Area3D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleGridDB_Volume3D : public TestSimpleGridDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleGridDB_Volume3D, TestSimpleGridDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleGridDB::setUp();
        CPPUNIT_ASSERT(_data);

        _data->numX = 3;
        _data->numY = 2;
        _data->numZ = 4;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 3;

        static const double dbX[3] = { -3.0, 1.0, 2.0, };
        _data->dbX = dbX;

        static const double dbY[2] = { 2.0, 4.0, };
        _data->dbY = dbY;

        static const double dbZ[4] = { -0.5, 0.0, 1.0, 4.0, };
        _data->dbZ = dbZ;

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
        _data->dbData = dbData;

        static const char* names[2] = { "One", "Two" };
        _data->names = names;

        static const char* units[2] = { "m", "m" };
        _data->units = units;

        _data->numQueries = 5;
        static const double queryNearest[5*(3+2)] = {
            -3.2,  3.8,  2.0,  7.00000000e-01,  5.20000000e+00, // (0,1,2)
            1.1,  1.3, -0.1,  1.00000000e-01,  3.40000000e+00, // (1,0,1)
            0.0, -6.0,  5.0,  6.00000000e-01,  1.40000000e+00, // (1,0,3)
            1.6,  3.4, -0.6,  7.00000000e-01,  4.80000000e+00, // (2,1,0)
            -2.0,  3.5,  0.9,  7.00000000e-01,  5.20000000e+00, // (0,1,2)
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(3+2)] = {
            -3.0,  4.0,  1.0,   7.00000000e-01,  5.20000000e+00, // (0,1,2)
            -1.0,  2.5,  2.5,   3.62500000e-01,  2.52500000e+00, // (0,5, 0.25, 2.5)
            1.25, 3.0,  0.25,  3.25000000e-01,  3.49062500e+00, // (1.25, 0.5, 1.25)
            0.0,  4.1,  0.0,   0.0, 0.0, // not found
            1.0,  2.0, -0.6,   0.0, 0.0, // not found
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = { 0, 0, 0, 1, 1, };
        _data->errFlags = errFlags;

        _data->filename = "data/grid_volume3d.spatialdb";
    } // setUp

}; // TestSimpleGriDB_Volume3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridDB_Volume3D);

// End of file
