// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include <math.h> // USES M_PI

#include <string.h> // USES memcpy() and strcmp()
#include <strings.h> // USES strcasecmp()
#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace geocoords {
        class TestCSGeo;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestCSGeo : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestCSGeo);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testComputeSurfaceNormal);
    CPPUNIT_TEST(testPickle);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test constructor
    void testConstructor(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test computeSurfaceNormal().
    void testComputeSurfaceNormal(void);

    /// Test pickle() & unpickle()
    void testPickle(void);

}; // class TestCSGeo
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::geocoords::TestCSGeo);

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeo::testConstructor(void) {
    const std::string defaultCSString("EPSG:4326");
    const size_t defaultSpaceDim(3);

    CSGeo cs;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in coordinate system type.", CoordSys::GEOGRAPHIC, cs.getCSType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default coordinate system string.", defaultCSString, std::string(cs.getString()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mis match in default coordinate system dimension.", defaultSpaceDim, cs.getSpaceDim());

    const std::string cloneCSString("EPSG:4269");
    const size_t cloneSpaceDim(2);

    cs.setSpaceDim(2);
    CoordSys* csClone = cs.clone();CPPUNIT_ASSERT(csClone);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in clone coordinate system type.", CoordSys::GEOGRAPHIC, csClone->getCSType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in clone coordinate system dimension.", cloneSpaceDim, csClone->getSpaceDim());
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

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in coordinate system string.", csString, std::string(cs.getString()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in dimension of coordinate system.", spaceDim, cs.getSpaceDim());
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
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in x-component of surface normal (WGS84).", 0.0, dirs[i++]);
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in y-component of surface normal (WGS84).", 0.0, dirs[i++]);
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in z-component of surface normal (WGS84).", 1.0, dirs[i++]);
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
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in x-component of surface normal (UTM).", 0.0, dirs[i++]);
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in y-component of surface normal (UTM).", 0.0, dirs[i++]);
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in z-component of surface normal (UTM).", 1.0, dirs[i++]);
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
                std::cout << "dirE: " << dirsE[i] << ", dir: " << dirs[i] << std::endl;
                CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in relative value (ECEF).", 1.0, dirs[i]/dirsE[i], tolerance);
            } else {
                CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in absolute value (ECEF).", dirsE[i], dirs[i], tolerance);
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

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in coordinate system string.", csString, std::string(csB.getString()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in dimension of coordinate system.", spaceDim, csB.getSpaceDim());
} // testPickle


// End of file
