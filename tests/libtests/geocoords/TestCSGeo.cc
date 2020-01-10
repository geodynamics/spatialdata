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
    const int defaultSpaceDim(3);

    CSGeo cs;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying geographic coordinate system type", CoordSys::GEOGRAPHIC, cs.csType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default coordinate system string", defaultCSString, std::string(cs.getString()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default coordinate system dimension", defaultSpaceDim, cs.spaceDim());

    const std::string cloneCSString("EPSG:4269");
    const int cloneSpaceDim(2);

    cs.setSpaceDim(2);
    CoordSys* csClone = cs.clone();CPPUNIT_ASSERT(csClone);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying geographic coordinate system type", CoordSys::GEOGRAPHIC, csClone->csType());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking clone coordinate system dimension", cloneSpaceDim, csClone->spaceDim());
    delete csClone;csClone = NULL;
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::geocoords::TestCSGeo::testAccessors(void) {
    const std::string csString("EPSG:4269"); // +proj=longlat +datum=NAD83
    const int spaceDim(2);

    CSGeo cs;
    cs.setString(csString.c_str());
    cs.setSpaceDim(spaceDim);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking coordinate system string", csString, std::string(cs.getString()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking dimension of coordinate system", spaceDim, cs.spaceDim());
} // testAccessors


// ----------------------------------------------------------------------
// Test computeSurfaceNormal().
void
spatialdata::geocoords::TestCSGeo::testComputeSurfaceNormal(void) {
#if 1
    CPPUNIT_ASSERT_MESSAGE(":TODO: @brad Implement test.", false);
#else
    CSGeo cs;

    { // 2D
        const int numLocs = 1;
        const int numDims = 2;
        const double coords[] = { 28.0, 23.0,
                                  42.0, 34.0,
                                  -12.0, 65.7,
                                  64.3, -163.0 };

        const int size = numLocs * numDims;
        double* dirs = new double[size];
        cs.setSpaceDim(numDims);
        cs.initialize();
        cs.radialDir(dirs, coords, numLocs, numDims);
        for (int i = 0; i < size; ++i) {
            CPPUNIT_ASSERT_EQUAL(0.0, dirs[i]);
        }
        delete[] dirs;dirs = 0;
    } // 2D

    { // 3D
        const int numLocs = 4;
        const int numDims = 3;
        const double coords[] = { 28.0, 23.0, 3.4,
                                  42.0, 34.0, 3.5,
                                  -12.0, 65.7, 12.6,
                                  64.3, -163.0, -1.5 };
        const int size = numLocs * numDims;
        double* dirs = new double[size];
        cs.setSpaceDim(numDims);
        cs.initialize();
        cs.radialDir(dirs, coords, numLocs, numDims);
        for (int iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
            CPPUNIT_ASSERT_EQUAL(dirs[i++], 0.0);
            CPPUNIT_ASSERT_EQUAL(dirs[i++], 0.0);
            CPPUNIT_ASSERT_EQUAL(dirs[i++], 1.0);
        } // for
        delete[] dirs;dirs = 0;
    } // 3D

    cs.isGeocentric(true);

    const int numLocs = 5;
    const int numDims = 3;
    const double coords[] = {
        0.0, 0.0, 6356752.31, // (lon=0.0, lat=90.0)
        6378137.00, 0.0, 0.0, // (lon=0.0, lat=0.0)
        0.0, -6378137.00, 0.0, // (lon=-90.0, lat=0.0)
        -2684785.48, -4296554.90, 3861564.10, // (lon=-122.0, lat=37.5)
        -2680581.35, -4289826.89, 3855476.48, // (lon=-122.0, lat=37.5, elev=-10km)
    };
    const double dirsE[] = {
        0.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        0.0, -1.0, 0.0,
        -0.4214565909579322, -0.67447153394825399, 0.6061868456438223,
        -0.42145822808804162, -0.67447415459479865, 0.60618279154106625,
    };
    const int size = numLocs * numDims;
    double* dirs = new double[size];
    cs.initialize();
    cs.radialDir(dirs, coords, numLocs, numDims);

    const double tolerance = 1.0e-6;
    for (int i = 0; i < size; ++i) {
        if (fabs(dirsE[i]) > tolerance) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dirs[i]/dirsE[i], tolerance);
        } else {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(dirsE[i], dirs[i], tolerance);
        }
    }
    delete[] dirs;dirs = 0;
#endif
} // testComputeSurfaceNormal


// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSGeo::testPickle(void) {
    const std::string csString("+proj=lonlat +datum=WGS84");
    const int spaceDim(2);

    CSGeo csA;
    csA.setString(csString.c_str());
    csA.setSpaceDim(spaceDim);

    std::stringstream s;
    csA.pickle(s);

    CSGeo csB;
    csB.unpickle(s);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking coordinate system string", csString, std::string(csB.getString()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking dimension of coordinate system", spaceDim, csB.spaceDim());
} // testPickle


// End of file
