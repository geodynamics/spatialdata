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

#include "TestSimpleDB.hh" // ISA TestSimpleDB

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDB_Point3D;
        class TestSimpleDB_Line3D;
        class TestSimpleDB_Area3D;
        class TestSimpleDB_Volume3D;
    } // spatialdb
} // spatialdata

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDB_Point3D : public TestSimpleDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleDB_Point3D, TestSimpleDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleDB::setUp();
        _data = new TestSimpleDB_Data;CPPUNIT_ASSERT(_data);

        _data->numLocs = 1;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 0;
        _data->numQueries = 3;

        static const double dbCoordinates[3] = {
            1.00000000e-01,  2.00000000e-01,  3.00000000e-01,
        };
        _data->dbCoordinates = dbCoordinates;

        static const double dbValues[2] = {
            6.30000000e+00,  7.40000000e+00,
        };
        _data->dbValues = dbValues;

        static const char* names[] = {
            "One",
            "Two",
        };
        _data->names = names;

        static const char* units[] = {
            "m",
            "m/s",
        };
        _data->units = units;

        static const double queryNearest[3*(3+2)] = {
            4.50000000e+00,  2.30000000e+00,  4.00000000e+00,  6.30000000e+00,  7.40000000e+00,
            3.20000000e+00,  7.40000000e+00,  5.80000000e+00,  6.30000000e+00,  7.40000000e+00,
            4.00000000e+00,  9.80000000e+00,  5.70000000e+00,  6.30000000e+00,  7.40000000e+00,
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[3*(3+2)] = {
            2.90000000e+00,  3.40000000e+00,  8.70000000e+00,  6.30000000e+00,  7.40000000e+00,
            2.20000000e+00,  9.00000000e+00,  8.50000000e+00,  6.30000000e+00,  7.40000000e+00,
            2.00000000e-01,  5.80000000e+00,  6.60000000e+00,  6.30000000e+00,  7.40000000e+00,
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[3] = {
            0, 0, 0,};
        _data->errFlags = errFlags;
    } // setUp

}; // TestSimpleGriDB_Point3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleDB_Point3D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDB_Line3D : public TestSimpleDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleDB_Line3D, TestSimpleDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleDB::setUp();
        _data = new TestSimpleDB_Data;CPPUNIT_ASSERT(_data);

        _data->numLocs = 5;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 1;
        _data->numQueries = 4;

        static const double dbCoordinates[5*3] = {
            3.40000000e+00,  9.50000000e+00,  8.70000000e+00,
            5.70000000e+00,  9.90000000e+00,  1.85000000e+01,
            6.85000000e+00,  1.01000000e+01,  2.34000000e+01,
            8.00000000e+00,  1.03000000e+01,  2.83000000e+01,
            1.49000000e+01,  1.15000000e+01,  5.77000000e+01,
        };
        _data->dbCoordinates = dbCoordinates;

        static const double dbValues[5*2] = {
            1.00000000e-01,  1.10000000e+00,
            3.00000000e-01,  3.30000000e+00,
            2.00000000e-01,  2.20000000e+00,
            1.00000000e-01,  1.10000000e+00,
            -4.00000000e-01, -4.40000000e+00,
        };
        _data->dbValues = dbValues;

        static const char* names[] = {
            "One",
            "Two",
        };
        _data->names = names;

        static const char* units[] = {
            "m",
            "m/s",
        };
        _data->units = units;

        static const double queryNearest[4*(3+2)] = {
            5.70000000e+00,  9.90000000e+00,  1.85000000e+01,  3.00000000e-01,  3.30000000e+00,
            1.26000000e+01,  1.11000000e+01,  4.79000000e+01, -4.00000000e-01, -4.40000000e+00,
            1.72000000e+01,  1.19000000e+01,  6.75000000e+01, -4.00000000e-01, -4.40000000e+00,
            6.16000000e+00,  9.98000000e+00,  2.04600000e+01,  3.00000000e-01,  3.30000000e+00,
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[4*(3+2)] = {
            5.70000000e+00,  9.90000000e+00,  1.85000000e+01,  3.00000000e-01,  3.30000000e+00,
            1.26000000e+01,  1.11000000e+01,  4.79000000e+01, -2.33333333e-01, -2.56666667e+00,
            1.72000000e+01,  1.19000000e+01,  6.75000000e+01,  0.00000000e+00,  0.00000000e+00,
            6.16000000e+00,  9.98000000e+00,  2.04600000e+01,  2.60000000e-01,  2.86000000e+00,
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[4] = {
            0, 0, 1, 0,};
        _data->errFlags = errFlags;
    } // setUp

}; // TestSimpleGriDB_Line3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleDB_Line3D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDB_Area3D : public TestSimpleDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleDB_Area3D, TestSimpleDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleDB::setUp();
        _data = new TestSimpleDB_Data;CPPUNIT_ASSERT(_data);

        _data->numLocs = 6;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 2;
        _data->numQueries = 4;

        static const double dbCoordinates[6*3] = {
            3.40000000e+00,  9.50000000e+00,  8.70000000e+00,
            4.29442719e+00,  9.50000000e+00,  9.14721360e+00,
            6.97770876e+00,  9.50000000e+00,  1.04888544e+01,
            7.63236243e+00,  1.21186147e+01,  9.17954704e+00,
            3.83643578e+00,  1.12457431e+01,  7.82712844e+00,
            4.05465367e+00,  1.21186147e+01,  7.39069266e+00,
        };
        _data->dbCoordinates = dbCoordinates;

        static const double dbValues[6*2] = {
            1.00000000e-01,  1.10000000e+00,
            3.00000000e-01,  3.30000000e+00,
            2.00000000e-01,  2.20000000e+00,
            1.00000000e-01,  1.10000000e+00,
            -4.00000000e-01, -4.40000000e+00,
            -3.00000000e-01, -3.20000000e+00,
        };
        _data->dbValues = dbValues;

        static const char* names[] = {
            "One",
            "Two",
        };
        _data->names = names;

        static const char* units[] = {
            "m",
            "m/s",
        };
        _data->units = units;

        static const double queryNearest[4*(3+2)] = {
            6.30149946e+00,  1.03728716e+01,  9.60520501e+00,  2.00000000e-01,  2.20000000e+00,
            3.78727022e+00,  1.01546537e+01,  8.48447656e+00,  1.00000000e-01,  1.10000000e+00,
            6.95615313e+00,  1.29914862e+01,  8.29589766e+00,  1.00000000e-01,  1.10000000e+00,
            4.89452639e+00,  1.19003968e+01,  7.94701520e+00, -3.00000000e-01, -3.20000000e+00,
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[4*(3+2)] = {
            6.30149946e+00,  1.03728716e+01,  9.60520501e+00,  2.00000000e-01,  2.20000000e+00,
            3.78727022e+00,  1.01546537e+01,  8.48447656e+00, -3.75000000e-02, -4.12500000e-01,
            6.95615313e+00,  1.29914862e+01,  8.29589766e+00,  0.00000000e+00,  0.00000000e+00,
            4.89452639e+00,  1.19003968e+01,  7.94701520e+00, -2.25000000e-01, -2.42500000e+00,
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[4] = {
            0, 0, 1, 0,};
        _data->errFlags = errFlags;
    } // setUp

}; // TestSimpleGriDB_Area3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleDB_Area3D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestSimpleDB_Volume3D : public TestSimpleDB {
    CPPUNIT_TEST_SUB_SUITE(TestSimpleDB_Volume3D, TestSimpleDB);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestSimpleDB::setUp();
        _data = new TestSimpleDB_Data;CPPUNIT_ASSERT(_data);

        _data->numLocs = 8;
        _data->spaceDim = 3;
        _data->numValues = 2;
        _data->dataDim = 3;
        _data->numQueries = 5;

        static const double dbCoordinates[8*3] = {
            4.46656933e+00,  8.13917840e+00,  8.80292932e+00,
            2.67771495e+00,  8.13917840e+00,  7.90850213e+00,
            4.90300511e+00,  9.88492152e+00,  7.93005776e+00,
            3.11415073e+00,  9.88492152e+00,  7.03563057e+00,
            3.68584927e+00,  9.11507848e+00,  1.03643694e+01,
            1.89699489e+00,  9.11507848e+00,  9.46994224e+00,
            4.12228505e+00,  1.08608216e+01,  9.49149787e+00,
            2.33343067e+00,  1.08608216e+01,  8.59707068e+00,
        };
        _data->dbCoordinates = dbCoordinates;

        static const double dbValues[8*2] = {
            1.00000000e-01,  1.10000000e+00,
            3.00000000e-01,  3.30000000e+00,
            2.00000000e-01,  2.20000000e+00,
            1.00000000e-01,  1.10000000e+00,
            4.00000000e-01,  4.60000000e+00,
            3.00000000e-01,  3.20000000e+00,
            7.00000000e-01,  5.20000000e+00,
            5.00000000e-01,  4.60000000e+00,
        };
        _data->dbValues = dbValues;

        static const char* names[] = {
            "One",
            "Two",
        };
        _data->names = names;

        static const char* units[] = {
            "m",
            "m/s",
        };
        _data->units = units;

        static const double queryNearest[5*(3+2)] = {
            4.38173419e+00,  8.36254772e+00,  8.74899281e+00,  1.00000000e-01,  1.10000000e+00,
            2.35495601e+00,  1.00264422e+01,  9.00123360e+00,  5.00000000e-01,  4.60000000e+00,
            3.91112675e+00,  1.07838373e+01,  9.69020768e+00,  7.00000000e-01,  5.20000000e+00,
            3.87701461e+00,  1.04910673e+01,  9.08761157e+00,  7.00000000e-01,  5.20000000e+00,
            3.01795532e+00,  8.84019490e+00,  8.79326896e+00,  3.00000000e-01,  3.30000000e+00,
        };
        _data->queryNearest = queryNearest;

        static const double queryLinear[5*(3+2)] = {
            4.38173419e+00,  8.36254772e+00,  8.74899281e+00,  1.35000000e-01,  1.49500000e+00,
            2.35495601e+00,  1.00264422e+01,  9.00123360e+00,  4.10000000e-01,  3.85500000e+00,
            3.91112675e+00,  1.07838373e+01,  9.69020768e+00,  0.00000000e+00,  0.00000000e+00,
            3.87701461e+00,  1.04910673e+01,  9.08761157e+00,  5.30000000e-01,  4.42000000e+00,
            3.01795532e+00,  8.84019490e+00,  8.79326896e+00,  2.00000000e-01,  2.15500000e+00,
        };
        _data->queryLinear = queryLinear;

        static const int errFlags[5] = {
            0, 0, 1, 0, 0, };
        _data->errFlags = errFlags;
    } // setUp

}; // TestSimpleGriDB_Volume3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleDB_Volume3D);

// End of file
