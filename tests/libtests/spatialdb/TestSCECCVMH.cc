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

#include "spatialdata/spatialdb/SCECCVMH.hh" // USES SCECCVMH
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

namespace spatialdata {
    namespace spatialdb {
        class TestSCECCVMH;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSCECCVMH {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test constructor.
    static
    void testConstructor(void);

    /// Test accessors().
    static
    void testAccessors(void);

    /// Test getNamesDBValues().
    static
    void testGetNamesDBValues(void);

    /// Test setQueryValues().
    static
    void testQueryVals(void);

    /// Test calcDensity().
    static
    void testCalcDensity(void);

    /// Test calcVs().
    static
    void testCalcVs(void);

    /// Test query().
    static
    void testQuery(void);

    /// Test querySquashed().
    static
    void testQuerySquashed(void);

}; // class TestSCECCVMH

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSCECCVMH::testConstructor", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testConstructor();
}
TEST_CASE("TestSCECCVMH::testAccessors", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testAccessors();
}
TEST_CASE("TestSCECCVMH::testGetNamesDBValues", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testGetNamesDBValues();
}
TEST_CASE("TestSCECCVMH::testQueryVals", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testQueryVals();
}
TEST_CASE("TestSCECCVMH::testQuery", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testQuery();
}
TEST_CASE("TestSCECCVMH::testQuerySquashed", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testQuerySquashed();
}
TEST_CASE("TestSCECCVMH::testCalcDensity", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testCalcDensity();
}
TEST_CASE("TestSCECCVMH::testCalcVs", "[TestSCECCVMH]") {
    spatialdata::spatialdb::TestSCECCVMH::testCalcVs();
}

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestSCECCVMH::testConstructor(void) {
    SCECCVMH db;

    const size_t numValues = 7;
    CHECK(numValues == db._querySize);
    for (size_t i = 0; i < numValues; ++i) {
        CHECK(i == db._queryValues[i]);
    } // for
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestSCECCVMH::testAccessors(void) {
    SCECCVMH db;

    // Description
    const std::string description("database 2");
    db.setDescription(description.c_str());
    CHECK(description == std::string(db.getDescription()));

    // Data directory
    const std::string dataDir("/path/to/data/dir");
    db.setDataDir(dataDir.c_str());
    CHECK(dataDir == db._dataDir);

    // Squashing
    const double limitDefault = -2000.0;
    CHECK(false == db._squashTopo);
    CHECK(limitDefault == db._squashLimit);

    db.setSquashFlag(true);
    CHECK(true == db._squashTopo);
    CHECK(limitDefault == db._squashLimit);

    const double limit = -4000.0;
    db.setSquashFlag(true, limit);
    CHECK(true == db._squashTopo);
    CHECK(limit == db._squashLimit);
} // testAccessors


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestSCECCVMH::testGetNamesDBValues(void) {
    const size_t numValuesE = 7;
    const char* valueNamesE[numValuesE] = {
        "vp",
        "vs",
        "density",
        "topo-elev",
        "basement-depth",
        "moho-depth",
        "vp-tag",
    };

    SCECCVMH db;
    const char** valueNames = NULL;
    size_t numValues = 0;
    db.getNamesDBValues(&valueNames, &numValues);
    REQUIRE(numValuesE == numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CHECK(std::string(valueNamesE[i]) == std::string(valueNames[i]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ----------------------------------------------------------------------
// Test setQueryValues().
void
spatialdata::spatialdb::TestSCECCVMH::testQueryVals(void) {
    SCECCVMH db;

    { // all values
        const size_t querySize = 7;
        const char* queryNames[7] = {
            "moho-depth",
            "topo-elev",
            "vp-tag",
            "Basement-Depth",
            "vP",
            "DenSity",
            "VS"
        };
        const size_t queryVals[7] = {
            SCECCVMH::QUERY_MOHODEPTH,
            SCECCVMH::QUERY_TOPOELEV,
            SCECCVMH::QUERY_VPTAG,
            SCECCVMH::QUERY_BASEDEPTH,
            SCECCVMH::QUERY_VP,
            SCECCVMH::QUERY_DENSITY,
            SCECCVMH::QUERY_VS
        };

        db.setQueryValues(queryNames, querySize);
        REQUIRE(querySize == db._querySize);
        for (size_t i = 0; i < querySize; ++i) {
            CHECK(queryVals[i] == db._queryValues[i]);
        }
    } // all values

    { // subset of values
        const size_t querySize = 3;
        const char* queryNames[3] = {
            "Basement-Depth",
            "vp-tag",
            "VS"
        };
        const size_t queryVals[3] = {
            SCECCVMH::QUERY_BASEDEPTH,
            SCECCVMH::QUERY_VPTAG,
            SCECCVMH::QUERY_VS
        };

        db.setQueryValues(queryNames, querySize);
        REQUIRE(querySize == db._querySize);
        for (size_t i = 0; i < querySize; ++i) {
            CHECK(queryVals[i] == db._queryValues[i]);
        }
    } // subset of values
} // testQueryVals


// ----------------------------------------------------------------------
// Test calcDensity()
void
spatialdata::spatialdb::TestSCECCVMH::testCalcDensity(void) {
    const size_t size = 10;
    const double vp[10] = {
        -99999.00,
        5540.545410,
        4384.126953,
        4142.553223,
        5226.578125,
        4181.372070,
        6351.574219,
        4932.721191,
        1480.0,
        1860.0,
    };
    const double densityE[10] = {
        2000.00,
        3126.848633,
        2741.375488,
        2660.851074,
        3022.192871,
        2673.790527,
        3397.191406,
        2924.240234,
        1000.0,
        2000.0,
    };

    SCECCVMH db;
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < size; ++i) {
        const double density = db._calcDensity(vp[i]);
        const double toleranceV = fabs(densityE[i]) * tolerance;
        CHECK_THAT(density, Catch::Matchers::WithinAbs(densityE[i], toleranceV));
    } // for
} // testCalcDensity


// ----------------------------------------------------------------------
// Test calcVs()
void
spatialdata::spatialdb::TestSCECCVMH::testCalcVs(void) {
    const size_t size = 10;
    const double vp[10] = {
        -99999.00,
        5540.545410,
        4384.126953,
        4142.553223,
        5226.578125,
        4181.372070,
        6351.574219,
        4932.721191,
        1480.0,
        1860.0,
    };
    const double vsE[10] = {
        (1500.0-1360.0)/1.16,
        3323.004705,
        2584.759846,
        2398.752778,
        3148.777937,
        2432.217302,
        3707.466393753004,
        2968.477865,
        0.0,
        431.0344827586207,
    };

    SCECCVMH db;
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < size; ++i) {
        const double vs = db._calcVs(vp[i]);
        const double toleranceV = fabs(vsE[i]) > 0.0 ? fabs(vsE[i]) * tolerance : tolerance;
        CHECK_THAT(vs, Catch::Matchers::WithinAbs(vsE[i], toleranceV));
    } // for
} // testCalcVs


#if !defined(SCECCVMH_DATADIR)
// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestSCECCVMH::testQuery(void) {
    INFO("SCECCVMH_DATADIR not defined. Skipping test.");
}


// ----------------------------------------------------------------------
// Test query() with squashing.
void
spatialdata::spatialdb::TestSCECCVMH::testQuerySquashed(void) {
    INFO("SCECCVMH_DATADIR not defined. Skipping test.");
}


#else
// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestSCECCVMH::testQuery(void) {
    SCECCVMH db;
    db.setDataDir(SCECCVMH_DATADIR);

    spatialdata::geocoords::CSGeo cs;
    cs.setString("+proj=lonlat +ellipsoid=clrk66 +datum=NAD27");

    const size_t numLocs = 18;
    const size_t spaceDim = 3;
    const double lonlatelev[18*3] = {
        -118.560000,  32.550000,  -2450.00,
        -118.513208,  33.884888,  -1400.00,
        -118.520000,  34.120000,  -1400.00,
        -116.400000,  32.340000,  -1000.00,
        -118.337765,  34.095691,  -1770.00,
        -118.337765,  34.095691, -17700.00,
        -117.989344,  34.034148,  -3000.00,

        -125.000000,  35.000000,  -40000.0, // outside domain
        -125.000000,  35.000000,  -35000.0,
        -125.000000,  35.000000,  -28300.0,
        -125.000000,  35.000000,  -15000.0,
        -125.000000,  35.000000,  -4000.0,
        -125.000000,  35.000000,  0.0,

        -115.000000,  30.000000,  -800000.0, // outside domain
        -115.000000,  30.000000,  -4539.0,

        -117.989344,  34.034148,  5000.00, // above domain
        -117.989344,  34.034148,  -500000.0, // below domain
        -117.682186,  34.357760,  1793.81,
    };
    const double tolerance = 1.0e-06;

    db.open();
    { // all values
        const size_t querySize = 7;
        const char* queryNames[7] = {
            "moho-depth",
            "topo-elev",
            "vp-tag",
            "Basement-Depth",
            "vP",
            "DenSity",
            "VS"
        };
        const double values[18*7] = {
            -27991.001953, -1115.499268,  2.0, -1326.415405,  5560.209473,  3133.403158,  3333.334131,
            // -27991.00,   -1115.50,      2.00,   -1326.42, 5540.545410,   3126.848633,   3323.004705,
            -27165.316406,   -56.893856,  2.0, -1431.710449,  4384.126953,  2741.375651,  2584.759474,
            -31178.105469,   489.975189,  2.0,    26.471289,  4142.553223,  2660.851074,  2398.752778,
            -34526.414062,   801.209961,  2.0,   631.073059,  5226.578125,  3022.192708,  3148.777736,
            -27857.322266,   106.671280,  3.0, -2361.386963,  4181.372070,  2673.790690,  2432.217302,
            -27857.322266,   106.671280,  0.0, -2361.386963,  6351.574219,  3397.191406,  3707.466394,
            -28512.111328,    93.515053,  2.0, -2860.919189,  4932.721191,  2924.240397,  2968.477965,

            -26312.804688, -50.465275, 1.0, -2875.716553, 7819.771973, 3886.590658, 4473.594442,
            -26312.804688, -50.465275, 1.0, -2875.716553, 7800.935059, 3880.311686, 4459.966373,
            -26312.804688, -50.465275, 0.0, -2875.716553, 6925.244140, 3588.414714, 3962.891997,
            -26312.804688, -50.465275, 0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
            -26312.804688, -50.465275, 0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
            -26312.804688, -50.465275, 0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,

            -26906.470703, 3.366069, 1.0, -973.515442, 7800.0, 3880.0, 4459.29424,
            -26906.470703, 3.366069, 2.0, -973.515442, 6642.105469, 3494.035156, 3834.988779,

            -28512.111328,    93.515053,  0.0, -2860.919189, 6649.152832, 3496.384277, 3838.102107,
            -28512.111328,    93.515053,  0.0, -2860.919189, 8159.479492, 3999.826497, 4751.5155415,
            -34629.367188,  2266.779785,  2.0, 2001.1707764, 4491.211426, 2777.070475, 2664.4122143,
        };
        const int flags[18] = {
            0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0,
            0, 0,
            0
        };

        db.setQueryValues(queryNames, querySize);
        double data[querySize];

        for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
            int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
            REQUIRE(flags[iLoc] == err);

            for (size_t iVal = 0; iVal < querySize; ++iVal) {
                const double dataE = values[iLoc*querySize+iVal];
                const double toleranceV = fabs(dataE) > 0.0 ? fabs(dataE) * tolerance : tolerance;
                CHECK_THAT(data[iVal], Catch::Matchers::WithinAbs(dataE, toleranceV));
            } // for
        } // for
    } // all values

    { // subset values
        const size_t querySize = 2;
        const char* queryNames[2] = {
            "DenSity",
            "vp-tag",
        };
        const double values[18*2] = {
            3133.403158,   2.0,
            2741.375651,   2.0,
            2660.851074,   2.0,
            3022.192708,   2.0,
            2673.790690,   3.0,
            3397.191406,   0.0,
            2924.240397,   2.0,
            3886.590657,   1.0,
            3880.311686,   1.0,
            3588.414714,   0.0,
            3475.256510,   0.0,
            3475.256510,   0.0,
            3475.256510,   0.0,
            3880.000000,   1.0,
            3494.035156,   2.0,
            3496.384277,   0.0,
            3999.826497,   0.0,
            2777.070475,   2.0,
        };
        const int flags[18] = {
            0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0,
            0, 0,
            0
        };

        db.setQueryValues(queryNames, querySize);

        double data[querySize];

        for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
            int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
            REQUIRE(flags[iLoc] == err);

            for (size_t iVal = 0; iVal < querySize; ++iVal) {
                const double dataE = values[iLoc*querySize+iVal];
                const double toleranceV = fabs(dataE) > 0.0 ? fabs(dataE) * tolerance : tolerance;
                CHECK_THAT(data[iVal], Catch::Matchers::WithinAbs(dataE, toleranceV));
            } // for
        } // for
    } // subset values

    { // subset values
        const size_t querySize = 1;
        const char* queryNames[1] = {
            "vs",
        };
        const double values[18*1] = {
            3333.334131,
            2584.759474,
            2398.752778,
            3148.777736,
            2432.217302,
            3707.466394,
            2968.477965,

            4473.594442,
            4459.966373,
            3962.891997,
            3810.172109,
            3810.172109,
            3810.172109,

            4459.29424,
            3834.988779,

            3838.102107,
            4751.5155415,
            2664.4122143,
        };
        const int flags[18] = {
            0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0,
            0, 0,
            0
        };

        db.setQueryValues(queryNames, querySize);

        double data[querySize];

        for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
            int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
            REQUIRE(flags[iLoc] == err);

            for (size_t iVal = 0; iVal < querySize; ++iVal) {
                const double dataE = values[iLoc*querySize+iVal];
                const double toleranceV = fabs(dataE) > 0.0 ? fabs(dataE) * tolerance : tolerance;
                CHECK_THAT(data[iVal], Catch::Matchers::WithinAbs(dataE, toleranceV));
            } // for
        } // for
    } // subset values

    db.close();
} // testQuery


// ----------------------------------------------------------------------
// Test query() with squashing.
void
spatialdata::spatialdb::TestSCECCVMH::testQuerySquashed(void) {
    SCECCVMH db;
    db.setDataDir(SCECCVMH_DATADIR);

    spatialdata::geocoords::CSGeo cs;
    cs.setString("+proj=lonlat +ellipsoid=clrk66 +datum=NAD27");

    const size_t numLocs = 18;
    const size_t spaceDim = 3;
    const double lonlatelev[18*3] = {
        -118.560000,  32.550000,  -2450.00,
        -118.513208,  33.884888,  -1400.00+56.893856,
        -118.520000,  34.120000,  -1400.00-489.975189,
        -116.400000,  32.340000,  -1000.00-801.209961,
        -118.337765,  34.095691,  -1770.00-106.671280,
        -118.337765,  34.095691, -17700.00,
        -117.989344,  34.034148,  -3000.00,

        -125.000000,  35.000000,  -40000.0, // outside domain
        -125.000000,  35.000000,  -35000.0,
        -125.000000,  35.000000,  -28300.0,
        -125.000000,  35.000000,  -15000.0,
        -125.000000,  35.000000,  -4000.0,
        -125.000000,  35.000000,  0.0-50.465275,

        -115.000000,  30.000000,  -800000.0, // outside domain
        -115.000000,  30.000000,  -4539.0,

        -117.989344,  34.034148,  5000.00, // above domain
        -117.989344,  34.034148,  -500000.0, // below domain
        -117.682186,  34.357760,  1793.81,
    };
    const double tolerance = 1.0e-06;

    db.open();
    { // all values
        const int querySize = 7;
        const char* queryNames[7] = {
            "moho-depth",
            "topo-elev",
            "vp-tag",
            "Basement-Depth",
            "vP",
            "DenSity",
            "VS"
        };
        const double values[18*7] = {
            -27991.001953, -1115.499268,  2.0, -1326.415405,  5560.209473,  3133.403158,  3333.334131,
            // -27991.00,   -1115.50,      2.00,   -1326.42, 5540.545410,   3126.848633,   3323.004705,
            -27165.316406,   -56.893856,  2.0, -1431.710449,  4384.126953,  2741.375651,  2584.759474,
            -31178.105469,   489.975189,  2.0,    26.471289,  4142.553223,  2660.851074,  2398.752778,
            -34526.414062,   801.209961,  2.0,   631.073059,  5226.578125,  3022.192708,  3148.777736,
            -27857.322266,   106.671280,  3.0, -2361.386963,  4181.372070,  2673.790690,  2432.217302,
            -27857.322266,   106.671280,  0.0, -2361.386963,  6351.574219,  3397.191406,  3707.466394,
            -28512.111328,    93.515053,  2.0, -2860.919189,  4932.721191,  2924.240397,  2968.477965,

            -26312.804688,   -50.465275,  1.0, -2875.716553, 7819.771973, 3886.590658, 4473.594442,
            -26312.804688,   -50.465275,  1.0, -2875.716553, 7800.935059, 3880.311686, 4459.966373,
            -26312.804688,   -50.465275,  0.0, -2875.716553, 6925.244140, 3588.414714, 3962.891997,
            -26312.804688,   -50.465275,  0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
            -26312.804688,   -50.465275,  0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,
            -26312.804688,   -50.465275,  0.0, -2875.716553, 6585.769531, 3475.256510, 3810.172109,

            -26906.470703,   3.36606908,  1.0,  -973.515442, 7800.0, 3880.0, 4459.29424,
            -26906.470703,   3.36606908,  2.0,  -973.515442, 6642.105469, 3494.035156, 3834.988779,

            -28512.111328,    93.515053,  0.0, -2860.919189, 6649.152832, 3496.384277, 3838.102107,
            -28512.111328,    93.515053,  0.0, -2860.919189, 8159.479492, 3999.826497, 4751.5155415,
            -34629.367188,  2266.779785,  4.0, 2001.1707764, 3705.773438, 2515.257812, 2022.2184806,
        };
        const int flags[18] = {
            0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0,
            0, 0,
            0
        };

        db.setSquashFlag(true);
        db.setQueryValues(queryNames, querySize);

        double data[querySize];

        for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
            int err = db.query(data, querySize, &lonlatelev[iLoc*spaceDim], spaceDim, &cs);
            REQUIRE(flags[iLoc] == err);

            for (size_t iVal = 0; iVal < querySize; ++iVal) {
                const double dataE = values[iLoc*querySize+iVal];
                const double toleranceV = fabs(dataE) > 0.0 ? fabs(dataE) * tolerance : tolerance;
                CHECK_THAT(data[iVal], Catch::Matchers::WithinAbs(dataE, toleranceV));
            } // for
        } // for
    } // all values

    db.close();
} // testQuerySquashed


#endif

// End of file
