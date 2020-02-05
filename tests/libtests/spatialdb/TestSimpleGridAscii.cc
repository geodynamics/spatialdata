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

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB
#include "spatialdata/spatialdb/SimpleGridAscii.hh" // USES SimpleGridAscii

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

namespace spatialdata {
    namespace spatialdb {
        class TestSimpleGridAscii;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleGridAscii : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSimpleGridAscii);

    CPPUNIT_TEST(testIO);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test read(), write().
    void testIO(void);

}; // class TestSimpleGridAscii
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleGridAscii);

// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleGridAscii::testIO(void) {
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
    dbOut.coordsys(csOut);
    dbOut.allocate(numX, numY, numZ, numValues, spaceDim, dataDim);
    dbOut.x(x, numX);
    dbOut.y(y, numY);
    dbOut.z(z, numZ);
    dbOut.data(coords, numX*numY*numZ, spaceDim, data, numX*numY*numZ, numValues);
    dbOut.names(names, numValues);
    dbOut.units(units, numValues);

    const char* filename = "data/grid.spatialdb";
    dbOut.filename(filename);
    SimpleGridAscii::write(dbOut);

    SimpleGridDB dbIn;
    dbIn.filename(filename);
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
                const size_t iD = dbIn._dataIndex(iX, numX, iY, numY, iZ, numZ);
                for (size_t iVal = 0; iVal < numValues; ++iVal, ++i) {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in data values.", 1.0, dbIn._data[iD+iVal]/data[i], tolerance);
                } // for
            } // for
        } // for
    } // for

    // Perform simple nearest query to ensure consistency of read/query
    dbIn.queryVals(names, numValues);
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
} // testIO


// End of file
