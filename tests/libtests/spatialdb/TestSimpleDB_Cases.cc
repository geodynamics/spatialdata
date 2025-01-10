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

#include "TestSimpleDB.hh" // ISA TestSimpleDB

#include "catch2/catch_test_macros.hpp"

#include <cassert>

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDB_Cases;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleDB_Cases {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    // Factories
    static
    TestSimpleDB_Data* Point3D(void);

    static
    TestSimpleDB_Data* Line3D(void);

    static
    TestSimpleDB_Data* Area3D(void);

    static
    TestSimpleDB_Data* Volume3D(void);

}; // class TestSimpleDB

// ------------------------------------------------------------------------------------------------
// Static test cases
TEST_CASE("TestSimpleDB::testConstructors", "[TestSimpleDB]") {
    spatialdata::spatialdb::TestSimpleDB::testConstructors();
}
TEST_CASE("TestSimpleDB::testAccessors", "[TestSimpleDB]") {
    spatialdata::spatialdb::TestSimpleDB::testAccessors();
}

// Data test cases
TEST_CASE("TestSimpleDB::testGetNamesDBValues", "[TestSimpleDB][Point3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Point3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleDB::testQueryNearest", "[TestSimpleDB][Point3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Point3D()).testQueryNearest();
}
TEST_CASE("TestSimpleDB::testQueryLinear", "[TestSimpleDB][Point3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Point3D()).testQueryLinear();
}

TEST_CASE("TestSimpleDB::testGetNamesDBValues", "[TestSimpleDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Line3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleDB::testQueryNearest", "[TestSimpleDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Line3D()).testQueryNearest();
}
TEST_CASE("TestSimpleDB::testQueryLinear", "[TestSimpleDB][Line3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Line3D()).testQueryLinear();
}

TEST_CASE("TestSimpleDB::testGetNamesDBValues", "[TestSimpleDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Area3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleDB::testQueryNearest", "[TestSimpleDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Area3D()).testQueryNearest();
}
TEST_CASE("TestSimpleDB::testQueryLinear", "[TestSimpleDB][Area3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Area3D()).testQueryLinear();
}

TEST_CASE("TestSimpleDB::testGetNamesDBValues", "[TestSimpleDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Volume3D()).testGetNamesDBValues();
}
TEST_CASE("TestSimpleDB::testQueryNearest", "[TestSimpleDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Volume3D()).testQueryNearest();
}
TEST_CASE("TestSimpleDB::testQueryLinear", "[TestSimpleDB][Volume3D]") {
    spatialdata::spatialdb::TestSimpleDB(spatialdata::spatialdb::TestSimpleDB_Cases::Volume3D()).testQueryLinear();
}

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleDB_Data*
spatialdata::spatialdb::TestSimpleDB_Cases::Point3D(void) {
    spatialdata::spatialdb::TestSimpleDB_Data* data = new TestSimpleDB_Data;assert(data);

    data->numLocs = 1;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 0;
    data->numQueries = 3;

    static const double dbCoordinates[3] = {
        1.00000000e-01,  2.00000000e-01,  3.00000000e-01,
    };
    data->dbCoordinates = dbCoordinates;

    static const double dbValues[2] = {
        6.30000000e+00,  7.40000000e+00,
    };
    data->dbValues = dbValues;

    static const char* names[] = {
        "One",
        "Two",
    };
    data->names = names;

    static const char* units[] = {
        "m",
        "m/s",
    };
    data->units = units;

    static const double queryNearest[3*(3+2)] = {
        4.50000000e+00,  2.30000000e+00,  4.00000000e+00,  6.30000000e+00,  7.40000000e+00,
        3.20000000e+00,  7.40000000e+00,  5.80000000e+00,  6.30000000e+00,  7.40000000e+00,
        4.00000000e+00,  9.80000000e+00,  5.70000000e+00,  6.30000000e+00,  7.40000000e+00,
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[3*(3+2)] = {
        2.90000000e+00,  3.40000000e+00,  8.70000000e+00,  6.30000000e+00,  7.40000000e+00,
        2.20000000e+00,  9.00000000e+00,  8.50000000e+00,  6.30000000e+00,  7.40000000e+00,
        2.00000000e-01,  5.80000000e+00,  6.60000000e+00,  6.30000000e+00,  7.40000000e+00,
    };
    data->queryLinear = queryLinear;

    static const int errFlags[3] = {
        0, 0, 0,};
    data->errFlags = errFlags;

    return data;
} // Point3D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleDB_Data*
spatialdata::spatialdb::TestSimpleDB_Cases::Line3D(void) {
    spatialdata::spatialdb::TestSimpleDB_Data* data = new TestSimpleDB_Data;assert(data);

    data->numLocs = 5;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 1;
    data->numQueries = 4;

    static const double dbCoordinates[5*3] = {
        3.40000000e+00,  9.50000000e+00,  8.70000000e+00,
        5.70000000e+00,  9.90000000e+00,  1.85000000e+01,
        6.85000000e+00,  1.01000000e+01,  2.34000000e+01,
        8.00000000e+00,  1.03000000e+01,  2.83000000e+01,
        1.49000000e+01,  1.15000000e+01,  5.77000000e+01,
    };
    data->dbCoordinates = dbCoordinates;

    static const double dbValues[5*2] = {
        1.00000000e-01,  1.10000000e+00,
        3.00000000e-01,  3.30000000e+00,
        2.00000000e-01,  2.20000000e+00,
        1.00000000e-01,  1.10000000e+00,
        -4.00000000e-01, -4.40000000e+00,
    };
    data->dbValues = dbValues;

    static const char* names[] = {
        "One",
        "Two",
    };
    data->names = names;

    static const char* units[] = {
        "m",
        "m/s",
    };
    data->units = units;

    static const double queryNearest[4*(3+2)] = {
        5.70000000e+00,  9.90000000e+00,  1.85000000e+01,  3.00000000e-01,  3.30000000e+00,
        1.26000000e+01,  1.11000000e+01,  4.79000000e+01, -4.00000000e-01, -4.40000000e+00,
        1.72000000e+01,  1.19000000e+01,  6.75000000e+01, -4.00000000e-01, -4.40000000e+00,
        6.16000000e+00,  9.98000000e+00,  2.04600000e+01,  3.00000000e-01,  3.30000000e+00,
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[4*(3+2)] = {
        5.70000000e+00,  9.90000000e+00,  1.85000000e+01,  3.00000000e-01,  3.30000000e+00,
        1.26000000e+01,  1.11000000e+01,  4.79000000e+01, -2.33333333e-01, -2.56666667e+00,
        1.72000000e+01,  1.19000000e+01,  6.75000000e+01,  0.00000000e+00,  0.00000000e+00,
        6.16000000e+00,  9.98000000e+00,  2.04600000e+01,  2.60000000e-01,  2.86000000e+00,
    };
    data->queryLinear = queryLinear;

    static const int errFlags[4] = {
        0, 0, 1, 0,};
    data->errFlags = errFlags;

    return data;
} // Line3D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleDB_Data*
spatialdata::spatialdb::TestSimpleDB_Cases::Area3D(void) {
    spatialdata::spatialdb::TestSimpleDB_Data* data = new TestSimpleDB_Data;assert(data);

    data->numLocs = 6;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 2;
    data->numQueries = 4;

    static const double dbCoordinates[6*3] = {
        3.40000000e+00,  9.50000000e+00,  8.70000000e+00,
        4.29442719e+00,  9.50000000e+00,  9.14721360e+00,
        6.97770876e+00,  9.50000000e+00,  1.04888544e+01,
        7.63236243e+00,  1.21186147e+01,  9.17954704e+00,
        3.83643578e+00,  1.12457431e+01,  7.82712844e+00,
        4.05465367e+00,  1.21186147e+01,  7.39069266e+00,
    };
    data->dbCoordinates = dbCoordinates;

    static const double dbValues[6*2] = {
        1.00000000e-01,  1.10000000e+00,
        3.00000000e-01,  3.30000000e+00,
        2.00000000e-01,  2.20000000e+00,
        1.00000000e-01,  1.10000000e+00,
        -4.00000000e-01, -4.40000000e+00,
        -3.00000000e-01, -3.20000000e+00,
    };
    data->dbValues = dbValues;

    static const char* names[] = {
        "One",
        "Two",
    };
    data->names = names;

    static const char* units[] = {
        "m",
        "m/s",
    };
    data->units = units;

    static const double queryNearest[4*(3+2)] = {
        6.30149946e+00,  1.03728716e+01,  9.60520501e+00,  2.00000000e-01,  2.20000000e+00,
        3.78727022e+00,  1.01546537e+01,  8.48447656e+00,  1.00000000e-01,  1.10000000e+00,
        6.95615313e+00,  1.29914862e+01,  8.29589766e+00,  1.00000000e-01,  1.10000000e+00,
        4.89452639e+00,  1.19003968e+01,  7.94701520e+00, -3.00000000e-01, -3.20000000e+00,
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[4*(3+2)] = {
        6.30149946e+00,  1.03728716e+01,  9.60520501e+00,  2.00000000e-01,  2.20000000e+00,
        3.78727022e+00,  1.01546537e+01,  8.48447656e+00, -3.75000000e-02, -4.12500000e-01,
        6.95615313e+00,  1.29914862e+01,  8.29589766e+00,  0.00000000e+00,  0.00000000e+00,
        4.89452639e+00,  1.19003968e+01,  7.94701520e+00, -2.25000000e-01, -2.42500000e+00,
    };
    data->queryLinear = queryLinear;

    static const int errFlags[4] = {
        0, 0, 1, 0,};
    data->errFlags = errFlags;

    return data;
} // Area3D


// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestSimpleDB_Data*
spatialdata::spatialdb::TestSimpleDB_Cases::Volume3D(void) {
    spatialdata::spatialdb::TestSimpleDB_Data* data = new TestSimpleDB_Data;assert(data);

    data->numLocs = 8;
    data->spaceDim = 3;
    data->numValues = 2;
    data->dataDim = 3;
    data->numQueries = 5;

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
    data->dbCoordinates = dbCoordinates;

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
    data->dbValues = dbValues;

    static const char* names[] = {
        "One",
        "Two",
    };
    data->names = names;

    static const char* units[] = {
        "m",
        "m/s",
    };
    data->units = units;

    static const double queryNearest[5*(3+2)] = {
        4.38173419e+00,  8.36254772e+00,  8.74899281e+00,  1.00000000e-01,  1.10000000e+00,
        2.35495601e+00,  1.00264422e+01,  9.00123360e+00,  5.00000000e-01,  4.60000000e+00,
        3.91112675e+00,  1.07838373e+01,  9.69020768e+00,  7.00000000e-01,  5.20000000e+00,
        3.87701461e+00,  1.04910673e+01,  9.08761157e+00,  7.00000000e-01,  5.20000000e+00,
        3.01795532e+00,  8.84019490e+00,  8.79326896e+00,  3.00000000e-01,  3.30000000e+00,
    };
    data->queryNearest = queryNearest;

    static const double queryLinear[5*(3+2)] = {
        4.38173419e+00,  8.36254772e+00,  8.74899281e+00,  1.35000000e-01,  1.49500000e+00,
        2.35495601e+00,  1.00264422e+01,  9.00123360e+00,  4.10000000e-01,  3.85500000e+00,
        3.91112675e+00,  1.07838373e+01,  9.69020768e+00,  0.00000000e+00,  0.00000000e+00,
        3.87701461e+00,  1.04910673e+01,  9.08761157e+00,  5.30000000e-01,  4.42000000e+00,
        3.01795532e+00,  8.84019490e+00,  8.79326896e+00,  2.00000000e-01,  2.15500000e+00,
    };
    data->queryLinear = queryLinear;

    static const int errFlags[5] = {
        0, 0, 1, 0, 0, };
    data->errFlags = errFlags;

    return data;
} // Volume3D


// End of file
