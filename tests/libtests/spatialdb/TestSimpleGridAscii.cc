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

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB
#include "spatialdata/spatialdb/SimpleGridAscii.hh" // USES SimpleGridAscii

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USE CSGeo

namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridAscii;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleGridAscii : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSimpleGridAscii);

    CPPUNIT_TEST(testIOCSCart);
    CPPUNIT_TEST(testIOCSGeo);
    CPPUNIT_TEST(testReadComments);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test read() and write() with CSCart.
    void testIOCSCart(void);

    /// Test read() and write() with CSGeo.
    void testIOCSGeo(void);

    /// Test read() with comments.
    void testReadComments(void);

}; // class TestSimpleGridAscii
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridAscii);

// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleGridAscii::testIOCSCart(void) {
    const size_t numX = 1;
    const size_t numY = 2;
    const size_t numZ = 3;
    const size_t spaceDim = 3;
    const size_t numValues = 2;
    const size_t dataDim = 2;

    const double x[numX] = { -2.0 };
    const double y[numY] = { 0.0, 1.0 };
    const double z[numZ] = { -2.0, -1.0, 2.0 };

    const double coords[numX*numY*numZ*spaceDim] = {
        -2.0,  0.0, -2.0,
        -2.0,  1.0, -2.0,
        -2.0,  0.0, -1.0,
        -2.0,  1.0, -1.0,
        -2.0,  0.0,  2.0,
        -2.0,  1.0,  2.0,
    };
    const double data[numX*numY*numZ*numValues] = {
        6.6,  3.4,
        5.5,  6.7,
        2.3,  4.1,
        5.7,  2.0,
        6.3,  6.9,
        3.4,  6.4,
    };
    const char* names[numValues] = { "One", "Two" };
    const char* units[numValues] = { "m", "m" };

    geocoords::CSCart csOut;
    SimpleGridDB dbOut;
    dbOut.setCoordSys(csOut);
    dbOut.allocate(numX, numY, numZ, numValues, spaceDim, dataDim);
    dbOut.setX(x, numX);
    dbOut.setY(y, numY);
    dbOut.setZ(z, numZ);
    dbOut.setData(coords, numX*numY*numZ, spaceDim, data, numX*numY*numZ, numValues);
    dbOut.setNames(names, numValues);
    dbOut.setUnits(units, numValues);

    const char* filename = "data/grid_xyz.spatialdb";
    dbOut.setFilename(filename);
    SimpleGridAscii::write(dbOut);

    SimpleGridDB dbIn;
    dbIn.setFilename(filename);
    dbIn.open();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along x axis.", numX, dbIn._numX);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along y axis.", numY, dbIn._numY);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along z axis.", numZ, dbIn._numZ);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValues, dbIn._numValues);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", dataDim, dbIn._dataDim);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", spaceDim, dbIn._spaceDim);

    CPPUNIT_ASSERT(dbIn._names);
    CPPUNIT_ASSERT(dbIn._units);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("", std::string(names[iVal]), dbIn._names[iVal]);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("", std::string(units[iVal]), dbIn._units[iVal]);
    } // for

    // Check to make sure values were read in correctly
    CPPUNIT_ASSERT(dbIn._data);
    const double tolerance = 1.0e-06;
    for (size_t iX = 0, i = 0; iX < numX; ++iX) {
        for (size_t iZ = 0; iZ < numZ; ++iZ) {
            for (size_t iY = 0; iY < numY; ++iY) {
                const size_t iD = dbIn._getDataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in data values.", 1.0, dbIn._data[iD+iVal]/data[i], tolerance);
                } // for
            } // for
        } // for
    } // for

    // Perform simple nearest query to ensure consistency of read/query
    dbIn.setQueryValues(names, numValues);
    const size_t numLocs = 3;
    const double points[numLocs*spaceDim] = {
        -2.0, 1.0, -2.0,
        -5.0, 0.0,  2.0,
        +6.0, 1.0, -1.0,
    };
    const double dataE[numLocs*numValues] = {
        5.5, 6.7,
        6.3, 6.9,
        5.7, 2.0,
    };
    const int errE[numLocs] = { 0, 0 };

    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        double data[numValues];
        int err = dbIn.query(data, numValues, &points[iLoc*spaceDim], spaceDim, &csOut);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("", errE[iLoc], err);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in query.", 1.0, data[iVal]/dataE[iLoc*numValues+iVal], tolerance);
        } // for
    } // for
} // testIOCSCart


// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleGridAscii::testIOCSGeo(void) {
    const size_t numX = 1;
    const size_t numY = 2;
    const size_t numZ = 3;
    const size_t spaceDim = 3;
    const size_t numValues = 10;
    const size_t dataDim = 2;

    const double x[numX] = { -2.0 };
    const double y[numY] = { 0.0, 1.0 };
    const double z[numZ] = { -2.0, -1.0, 2.0 };

    const double coords[numX*numY*numZ*spaceDim] = {
        -2.0,  0.0, -2.0,
        -2.0,  1.0, -2.0,
        -2.0,  0.0, -1.0,
        -2.0,  1.0, -1.0,
        -2.0,  0.0,  2.0,
        -2.0,  1.0,  2.0,
    };
    const double data[numX*numY*numZ*numValues] = {
        6.6,  3.4, 2.3, 8.3, 3.6, 9.4, 8.4, 3.7, 7.3, 1.5,
        5.5,  6.7, 3.4, 9.4, 4.7, 1.5, 9.5, 4.8, 8.4, 2.6,
        2.3,  4.1, 4.5, 0.5, 5.8, 2.6, 0.6, 5.9, 9.5, 3.7,
        5.7,  2.0, 5.6, 1.6, 6.9, 3.7, 1.7, 6.0, 0.6, 4.8,
        6.3,  6.9, 6.7, 2.7, 7.0, 4.8, 2.8, 7.0, 0.7, 5.9,
        3.4,  6.4, 7.8, 3.8, 8.1, 5.9, 3.9, 8.0, 0.8, 6.0,
    };
    const char* names[numValues] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
    const char* units[numValues] = { "m", "none", "m", "Pa", "Pa", "m", "kg", "m", "none", "none" };

    spatialdata::geocoords::CSGeo csOut;
    csOut.setString("+proj=tmerc +datum=WGS84 +lon_0=-122.6765 +lat_0=45.5231 +k=0.9996 +units=m +vunits=m");
    SimpleGridDB dbOut;
    dbOut.setCoordSys(csOut);
    dbOut.allocate(numX, numY, numZ, numValues, spaceDim, dataDim);
    dbOut.setX(x, numX);
    dbOut.setY(y, numY);
    dbOut.setZ(z, numZ);
    dbOut.setData(coords, numX*numY*numZ, spaceDim, data, numX*numY*numZ, numValues);
    dbOut.setNames(names, numValues);
    dbOut.setUnits(units, numValues);

    const char* filename = "data/grid_geo.spatialdb";
    dbOut.setFilename(filename);
    SimpleGridAscii::write(dbOut);

    SimpleGridDB dbIn;
    dbIn.setDescription("GridDB geo");
    dbIn.setFilename(filename);
    dbIn.open();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along x axis.", numX, dbIn._numX);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along y axis.", numY, dbIn._numY);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along z axis.", numZ, dbIn._numZ);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValues, dbIn._numValues);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", dataDim, dbIn._dataDim);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", spaceDim, dbIn._spaceDim);

    CPPUNIT_ASSERT(dbIn._names);
    CPPUNIT_ASSERT(dbIn._units);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("", std::string(names[iVal]), dbIn._names[iVal]);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("", std::string(units[iVal]), dbIn._units[iVal]);
    } // for

    // Check to make sure values were read in correctly
    CPPUNIT_ASSERT(dbIn._data);
    const double tolerance = 1.0e-06;
    for (size_t iX = 0, i = 0; iX < numX; ++iX) {
        for (size_t iZ = 0; iZ < numZ; ++iZ) {
            for (size_t iY = 0; iY < numY; ++iY) {
                const size_t iD = dbIn._getDataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    const double toleranceV = tolerance*data[i];
                    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in data values.", data[i], dbIn._data[iD+iVal], toleranceV);
                } // for
            } // for
        } // for
    } // for

    // Perform simple nearest query to ensure consistency of read/query
    dbIn.setQueryValues(names, numValues);
    const size_t numLocs = 3;
    const double points[numLocs*spaceDim] = {
        -2.0, 1.0, -2.0,
        -5.0, 0.0,  2.0,
        +6.0, 1.0, -1.0,
    };
    const double dataE[numLocs*numValues] = {
        5.5, 6.7, 3.4, 9.4, 4.7, 1.5, 9.5, 4.8, 8.4, 2.6,
        6.3, 6.9, 6.7, 2.7, 7.0, 4.8, 2.8, 7.0, 0.7, 5.9,
        5.7, 2.0, 5.6, 1.6, 6.9, 3.7, 1.7, 6.0, 0.6, 4.8,
    };
    const int errE[numLocs] = { 0, 0, 0 };

    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        double data[numValues];
        int err = dbIn.query(data, numValues, &points[iLoc*spaceDim], spaceDim, &csOut);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("", errE[iLoc], err);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            const double toleranceV = tolerance*dataE[iLoc*numValues+iVal];
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in query.", dataE[iLoc*numValues+iVal], data[iVal], toleranceV);
        } // for
    } // for
} // testIOCSGeo


// ----------------------------------------------------------------------
// Test read() with comments.
void
spatialdata::spatialdb::TestSimpleGridAscii::testReadComments(void) {
    const size_t numX = 1;
    const size_t numY = 1;
    const size_t numZ = 5;
    const size_t spaceDim = 3;
    const size_t numValues = 13;
    const size_t dataDim = 1;

    const double x[numX] = { 0.0 };
    const double y[numY] = { 0.0 };
    const double z[numZ] = { -400.01, -100.0, -30.0, -20.0, 0.0  };

    const double data[numX*numY*numZ*numValues] = {
        1.0e+20, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5,
        2.0e+20, 0.4, 1.4, 2.4, 3.4, 4.4, 5.4, 6.4, 7.4, 8.4, 9.4, 10.4, 11.4,
        4.0e+20, 0.3, 1.3, 2.3, 3.3, 4.3, 5.3, 6.3, 7.3, 8.3, 9.3, 10.3, 11.3,
        1.0e+21, 0.2, 1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 10.2, 11.2,
        1.0e+22, 0.1, 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1,
    };
    const char* names[numValues] = {
        "viscosity",
        "viscous_strain_xx",
        "viscous_strain_yy",
        "viscous_strain_zz",
        "viscous_strain_xy",
        "viscous_strain_yz",
        "viscous_strain_xz",
        "total_strain_xx",
        "total_strain_yy",
        "total_strain_zz",
        "total_strain_xy",
        "total_strain_yz",
        "total_strain_xz",
    };
    const char* units[numValues] = {
        "Pa*s",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
    };

    const char* filename = "data/grid_comments.spatialdb";
    SimpleGridDB dbIn;
    dbIn.setDescription("GridDB geo");
    dbIn.setFilename(filename);
    dbIn.open();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along x axis.", numX, dbIn._numX);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along y axis.", numY, dbIn._numY);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points along z axis.", numZ, dbIn._numZ);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValues, dbIn._numValues);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", dataDim, dbIn._dataDim);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", spaceDim, dbIn._spaceDim);

    CPPUNIT_ASSERT(dbIn._names);
    CPPUNIT_ASSERT(dbIn._units);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in value names.", std::string(names[iVal]), dbIn._names[iVal]);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in value units.", std::string(units[iVal]), dbIn._units[iVal]);
    } // for

    // Check coordinates
    CPPUNIT_ASSERT(dbIn._x);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < numX; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in x coordinates.", x[i], dbIn._x[i], tolerance);
    } // for
    for (size_t i = 0; i < numY; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in y coordinates.", y[i], dbIn._y[i], tolerance);
    } // for
    for (size_t i = 0; i < numZ; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in z coordinates.", z[i], dbIn._z[i], tolerance);
    } // for

    // Check to make sure values were read in correctly
    CPPUNIT_ASSERT(dbIn._data);
    for (size_t iX = 0, i = 0; iX < numX; ++iX) {
        for (size_t iZ = 0; iZ < numZ; ++iZ) {
            for (size_t iY = 0; iY < numY; ++iY) {
                const size_t iD = dbIn._getDataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    const double toleranceV = tolerance*data[i];
                    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in data values.", data[i], dbIn._data[iD+iVal], toleranceV);
                } // for
            } // for
        } // for
    } // for
} // testReadComments


// End of file
