// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "spatialdata/spatialdb/SimpleGridAscii.hh" // Test subject

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USE CSGeo

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridAscii;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleGridAscii {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test read() and write() with CSCart.
    static
    void testIOCSCart(void);

    /// Test read() and write() with CSGeo.
    static
    void testIOCSGeo(void);

    /// Test read() with comments.
    static
    void testReadComments(void);

}; // class TestSimpleGridAscii

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSimpleGridAscii::testIOCSCart", "[TestSimpleGridAscii]") {
    spatialdata::spatialdb::TestSimpleGridAscii::testIOCSCart();
}
TEST_CASE("TestSimpleGridAscii::testIOCSGeo", "[TestSimpleGridAscii]") {
    spatialdata::spatialdb::TestSimpleGridAscii::testIOCSGeo();
}
TEST_CASE("TestSimpleGridAscii::testReadComments", "[TestSimpleGridAscii]") {
    spatialdata::spatialdb::TestSimpleGridAscii::testReadComments();
}

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

    CHECK(numX == dbIn._numX);
    CHECK(numY == dbIn._numY);
    CHECK(numZ == dbIn._numZ);
    CHECK(dataDim == dbIn._dataDim);
    CHECK(spaceDim == dbIn._spaceDim);
    REQUIRE(numValues == dbIn._numValues);

    CHECK(dbIn._names);
    CHECK(dbIn._units);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        CHECK(std::string(names[iVal]) == dbIn._names[iVal]);
        CHECK(std::string(units[iVal]) == dbIn._units[iVal]);
    } // for

    // Check to make sure values were read in correctly
    assert(dbIn._data);
    const double tolerance = 1.0e-06;
    for (size_t iX = 0, i = 0; iX < numX; ++iX) {
        for (size_t iZ = 0; iZ < numZ; ++iZ) {
            for (size_t iY = 0; iY < numY; ++iY) {
                const size_t iD = dbIn._getDataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    const double toleranceV = (fabs(data[i]) > 0.0) ? tolerance*data[i] : tolerance;
                    CHECK_THAT(dbIn._data[iD+iVal], Catch::Matchers::WithinAbs(data[i], toleranceV));
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
        REQUIRE(errE[iLoc] == err);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            const double valueE = dataE[iLoc*numValues+iVal];
            const double toleranceV = fabs(valueE) > 0.0 ? tolerance*valueE : tolerance;
            CHECK_THAT(data[iVal], Catch::Matchers::WithinAbs(valueE, tolerance));
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

    CHECK(numX == dbIn._numX);
    CHECK(numY == dbIn._numY);
    CHECK(numZ == dbIn._numZ);
    CHECK(dataDim == dbIn._dataDim);
    CHECK(spaceDim == dbIn._spaceDim);
    REQUIRE(numValues == dbIn._numValues);

    CHECK(dbIn._names);
    CHECK(dbIn._units);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        CHECK(std::string(names[iVal]) == dbIn._names[iVal]);
        CHECK(std::string(units[iVal]) == dbIn._units[iVal]);
    } // for

    // Check to make sure values were read in correctly
    assert(dbIn._data);
    const double tolerance = 1.0e-06;
    for (size_t iX = 0, i = 0; iX < numX; ++iX) {
        for (size_t iZ = 0; iZ < numZ; ++iZ) {
            for (size_t iY = 0; iY < numY; ++iY) {
                const size_t iD = dbIn._getDataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    const double toleranceV = (fabs(data[i]) > 0.0) ? tolerance*data[i] : tolerance;
                    CHECK_THAT(dbIn._data[iD+iVal], Catch::Matchers::WithinAbs(data[i], toleranceV));
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
        REQUIRE(errE[iLoc] == err);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            const double valueE = dataE[iLoc*numValues+iVal];
            const double toleranceV = fabs(valueE) > 0.0 ? tolerance*valueE : tolerance;
            CHECK_THAT(data[iVal], Catch::Matchers::WithinAbs(valueE, tolerance));
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

    CHECK(numX == dbIn._numX);
    CHECK(numY == dbIn._numY);
    CHECK(numZ == dbIn._numZ);
    CHECK(dataDim == dbIn._dataDim);
    CHECK(spaceDim == dbIn._spaceDim);
    REQUIRE(numValues == dbIn._numValues);

    CHECK(dbIn._names);
    CHECK(dbIn._units);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        CHECK(std::string(names[iVal]) == dbIn._names[iVal]);
        CHECK(std::string(units[iVal]) == dbIn._units[iVal]);
    } // for

    // Check coordinates
    assert(dbIn._x);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < numX; ++i) {
        CHECK_THAT(dbIn._x[i], Catch::Matchers::WithinAbs(x[i], tolerance));
    } // for
    for (size_t i = 0; i < numY; ++i) {
        CHECK_THAT(dbIn._y[i], Catch::Matchers::WithinAbs(y[i], tolerance));
    } // for
    for (size_t i = 0; i < numZ; ++i) {
        CHECK_THAT(dbIn._z[i], Catch::Matchers::WithinAbs(z[i], tolerance));
    } // for

    // Check to make sure values were read in correctly
    assert(dbIn._data);
    for (size_t iX = 0, i = 0; iX < numX; ++iX) {
        for (size_t iZ = 0; iZ < numZ; ++iZ) {
            for (size_t iY = 0; iY < numY; ++iY) {
                const size_t iD = dbIn._getDataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    const double toleranceV = (fabs(data[i]) > 0.0) ? tolerance*data[i] : tolerance;
                    CHECK_THAT(dbIn._data[iD+iVal], Catch::Matchers::WithinAbs(data[i], toleranceV));
                } // for
            } // for
        } // for
    } // for
} // testReadComments


// End of file
