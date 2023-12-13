// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <math.h> // USES M_PI

#include <strings.h> // USES strcasecmp()
#include <sstream> // USES std::stringstream

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace geocoords {
        class TestCSGeo;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestCSGeo {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test constructor
    static
    void testConstructor(void);

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test computeSurfaceNormal().
    static
    void testComputeSurfaceNormal(void);

    /// Test pickle() & unpickle()
    static
    void testPickle(void);

}; // class TestCSGeo

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestCSGeo::testConstructor", "[TestCSGeo]") {
    spatialdata::geocoords::TestCSGeo::testConstructor();
}
TEST_CASE("TestCSGeo::testAccessors", "[TestCSGeo]") {
    spatialdata::geocoords::TestCSGeo::testAccessors();
}
TEST_CASE("TestCSGeo::testComputeSurfaceNormal", "[TestCSGeo]") {
    spatialdata::geocoords::TestCSGeo::testComputeSurfaceNormal();
}
TEST_CASE("TestCSGeo::testPickle", "[TestCSGeo]") {
    spatialdata::geocoords::TestCSGeo::testPickle();
}

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeo::testConstructor(void) {
    const std::string defaultCSString("EPSG:4326");
    const size_t defaultSpaceDim(3);

    CSGeo cs;
    CHECK(CoordSys::GEOGRAPHIC == cs.getCSType());
    CHECK(defaultCSString == std::string(cs.getString()));
    CHECK(defaultSpaceDim == cs.getSpaceDim());

    const std::string cloneCSString("EPSG:4269");
    const size_t cloneSpaceDim(2);

    cs.setSpaceDim(2);
    CoordSys* csClone = cs.clone();assert(csClone);
    CHECK(CoordSys::GEOGRAPHIC == csClone->getCSType());
    CHECK(cloneSpaceDim == csClone->getSpaceDim());
    delete csClone;csClone = NULL;
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::geocoords::TestCSGeo::testAccessors(void) {
    const std::string csString("EPSG:4269"); // +proj=longlat +datum=NAD83
    const size_t spaceDim(2);

    CSGeo cs;
    cs.setString(csString.c_str());
    cs.setSpaceDim(spaceDim);

    CHECK(csString == std::string(cs.getString()));
    CHECK(spaceDim == cs.getSpaceDim());
} // testAccessors


// ----------------------------------------------------------------------
// Test computeSurfaceNormal().
void
spatialdata::geocoords::TestCSGeo::testComputeSurfaceNormal(void) {
    CSGeo cs;

    { // WGS84
        cs.setString("EPSG:4326");
        const size_t numLocs = 4;
        const size_t numDims = 3;
        const size_t size = numLocs * numDims;
        const double coords[size] = {
            28.0, 23.0, 3.4,
            42.0, 34.0, 3.5,
            -12.0, 65.7, 12.6,
            64.3, -163.0, -1.5,
        };
        double* dirs = new double[size];
        cs.setSpaceDim(numDims);
        cs.computeSurfaceNormal(dirs, coords, numLocs, numDims);
        for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
            CHECK(0.0 == dirs[i++]);
            CHECK(0.0 == dirs[i++]);
            CHECK(1.0 == dirs[i++]);
        } // for
        delete[] dirs;dirs = 0;
    } // WGS84

    { // UTM zone 10
        cs.setString("EPSG:26910");
        const size_t numLocs = 4;
        const size_t numDims = 3;
        const size_t size = numLocs * numDims;
        const double coords[size] = {
            570000.0, 4150000.0, -1.0,
            400000.0, 4000000.0, 20.0,
            300000.0, 4250000.0, 30.0,
            550000.0, 4100000.0, 40.0,
        };
        double* dirs = new double[size];
        cs.setSpaceDim(numDims);
        cs.computeSurfaceNormal(dirs, coords, numLocs, numDims);
        for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
            CHECK(0.0 == dirs[i++]);
            CHECK(0.0 == dirs[i++]);
            CHECK(1.0 == dirs[i++]);
        } // for
        delete[] dirs;dirs = 0;
    } // UTM zone 10

    { // Geocentric ECEF
        cs.setString("EPSG:4978");

        const size_t numLocs = 5;
        const size_t numDims = 3;
        const size_t size = numLocs * numDims;
        const double coords[size] = {
            0.0, 0.0, 6356752.31424518, // (lon=0.0, lat=90.0)
            6378137.00, 0.0, 0.0, // (lon=0.0, lat=0.0)
            0.0, -6378137.00, 0.0, // (lon=-90.0, lat=0.0)
            -2684785.48, -4296554.90, 3861564.10, // (lon=-122.0, lat=37.5)
            -2680581.35, -4289826.89, 3855476.48, // (lon=-122.0, lat=37.5, elev=-10km)
        };
        const double dirsE[size] = {
            0.0, 0.0, 1.0,
            1.0, 0.0, 0.0,
            0.0, -1.0, 0.0,
            -0.4204132183640867, -0.6728017898133232, 0.6087614290087207,
            -0.4204132183640867, -0.6728017898133232, 0.6087614290087207,
        };
        double* dirs = new double[size];
        cs.computeSurfaceNormal(dirs, coords, numLocs, numDims);

        const double tolerance = 1.0e-6;
        for (size_t i = 0; i < size; ++i) {
            if (fabs(dirsE[i]) > tolerance) {
                CHECK_THAT(dirs[i]/dirsE[i], Catch::Matchers::WithinAbs(1.0, tolerance));
            } else {
                CHECK_THAT(dirs[i], Catch::Matchers::WithinAbs(dirsE[i], tolerance));
            } // if/else
        }
        delete[] dirs;dirs = 0;
    } // Geocentric ECEF
} // testComputeSurfaceNormal


// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSGeo::testPickle(void) {
    const std::string csString("+proj=lonlat +datum=WGS84");
    const size_t spaceDim(2);

    CSGeo csA;
    csA.setString(csString.c_str());
    csA.setSpaceDim(spaceDim);

    std::stringstream s;
    csA.pickle(s);

    CSGeo csB;
    csB.unpickle(s);

    CHECK(csString == std::string(csB.getString()));
    CHECK(spaceDim == csB.getSpaceDim());
} // testPickle


// End of file
