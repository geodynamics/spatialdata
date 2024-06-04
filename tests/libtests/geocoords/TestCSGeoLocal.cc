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

#include "spatialdata/geocoords/CSGeoLocal.hh" // USES CSGeoLocal

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <math.h> // USES M_PI

#include <strings.h> // USES strcasecmp()
#include <sstream> // USES std::stringstream

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace geocoords {
        class TestCSGeoLocal;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestCSGeoLocal {
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

}; // class TestCSGeoLocal

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestCSGeoLocal::testConstructor", "[TestCSGeoLocal]") {
    spatialdata::geocoords::TestCSGeoLocal::testConstructor();
}
TEST_CASE("TestCSGeoLocal::testAccessors", "[TestCSGeoLocal]") {
    spatialdata::geocoords::TestCSGeoLocal::testAccessors();
}
TEST_CASE("TestCSGeoLocal::testComputeSurfaceNormal", "[TestCSGeoLocal]") {
    spatialdata::geocoords::TestCSGeoLocal::testComputeSurfaceNormal();
}
TEST_CASE("TestCSGeoLocal::testPickle", "[TestCSGeoLocal]") {
    spatialdata::geocoords::TestCSGeoLocal::testPickle();
}

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeoLocal::testConstructor(void) {
    const std::string& defaultCSString = "EPSG:4326";
    const size_t defaultSpaceDim = 3;
    const double defaultOriginX = 0.0;
    const double defaultOriginY = 0.0;
    const double defaultYAzimuth = 0.0;
    const double tolerance = 1.0e-6;

    CSGeoLocal cs;
    CHECK(CoordSys::GEOGRAPHIC == cs.getCSType());
    CHECK(defaultCSString == std::string(cs.getString()));
    CHECK(defaultSpaceDim == cs.getSpaceDim());
    CHECK(defaultOriginX == 0.0);
    CHECK(defaultOriginY == 0.0);
    CHECK(defaultYAzimuth == 0.0);

    const std::string& cloneCSString = "EPSG:4269";
    const size_t cloneSpaceDim = 2;
    const double cloneOriginX = 10.0;
    const double cloneOriginY = 11.0;
    const double cloneYAzimuth = 12.0;

    cs.setSpaceDim(2);
    cs.setLocal(cloneOriginX, cloneOriginY, cloneYAzimuth);

    CoordSys* csClone = cs.clone();assert(csClone);
    CHECK(CoordSys::GEOGRAPHIC == csClone->getCSType());
    CHECK(cloneSpaceDim == csClone->getSpaceDim());
    double originX, originY, yAzimuth;
    cs.getLocal(&originX, &originY, nullptr);
    cs.getLocal(nullptr, nullptr, &yAzimuth);
    CHECK_THAT(originX, Catch::Matchers::WithinAbs(cloneOriginX, tolerance));
    CHECK_THAT(originY, Catch::Matchers::WithinAbs(cloneOriginY, tolerance));
    CHECK_THAT(yAzimuth, Catch::Matchers::WithinAbs(cloneYAzimuth, tolerance));

    delete csClone;csClone = NULL;
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::geocoords::TestCSGeoLocal::testAccessors(void) {
    const std::string& csString = "EPSG:4269"; // +proj=longlat +datum=NAD83
    const size_t spaceDim = 2;
    const double originX = 10.0;
    const double originY = 11.0;
    const double yAzimuth = 12.0;
    const double tolerance = 1.0e-6;

    CSGeoLocal cs;
    cs.setString(csString.c_str());
    cs.setSpaceDim(spaceDim);
    cs.setLocal(originX, originY, yAzimuth);

    CHECK(csString == std::string(cs.getString()));
    CHECK(spaceDim == cs.getSpaceDim());

    double x, y, yAz;
    cs.getLocal(&x, nullptr, &yAz);
    cs.getLocal(nullptr, &y, nullptr);
    CHECK_THAT(x, Catch::Matchers::WithinAbs(originX, tolerance));
    CHECK_THAT(y, Catch::Matchers::WithinAbs(originY, tolerance));
    CHECK_THAT(yAz, Catch::Matchers::WithinAbs(yAzimuth, tolerance));

} // testAccessors


// ----------------------------------------------------------------------
// Test computeSurfaceNormal().
void
spatialdata::geocoords::TestCSGeoLocal::testComputeSurfaceNormal(void) {
    CSGeoLocal cs;

    { // WGS84
        cs.setString("EPSG:4326");
        cs.setLocal(10.0, 20.0, 0.0);
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
        cs.setLocal(500000.0, 4000000.0, 0.0);
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
        cs.setLocal(0.0, 0.0, 0.0);

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
spatialdata::geocoords::TestCSGeoLocal::testPickle(void) {
    const std::string& csString = "+proj=lonlat +datum=WGS84";
    const size_t spaceDim = 2;
    const double originX = 20.0;
    const double originY = 21.0;
    const double yAzimuth = 30.0;
    const double tolerance = 1.0e-6;

    CSGeoLocal csA;
    csA.setString(csString.c_str());
    csA.setSpaceDim(spaceDim);
    csA.setLocal(originX, originY, yAzimuth);

    std::stringstream s;
    csA.pickle(s);

    CSGeoLocal csB;
    csB.unpickle(s);

    CHECK(csString == std::string(csB.getString()));
    CHECK(spaceDim == csB.getSpaceDim());

    double x, y, yAz;
    csB.getLocal(nullptr, &y, &yAz);
    csB.getLocal(&x, nullptr, nullptr);
    CHECK_THAT(x, Catch::Matchers::WithinAbs(originX, tolerance));
    CHECK_THAT(y, Catch::Matchers::WithinAbs(originY, tolerance));
    CHECK_THAT(yAz, Catch::Matchers::WithinAbs(yAzimuth, tolerance));
} // testPickle


// End of file
