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

#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii
#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleIOAscii;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleIOAscii : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSimpleIOAscii);

    CPPUNIT_TEST(testWriteRead);
    CPPUNIT_TEST(testReadComments);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test filename(), read(), write().
    void testWriteRead(void);

    /// Test filename(), read() with spatial database file that contains
    /// comments.
    void testReadComments(void);

}; // class TestSimpleIOAscii
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleIOAscii);

// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleIOAscii::testWriteRead(void) {
    const size_t spaceDim = 3;
    const size_t numLocs = 5;
    const size_t numVals = 2;
    const size_t dataDim = 3;
    const char* names[numVals] = { "One", "Two" };
    const char* units[numVals] = { "m", "m" };
    const double coords[numLocs*spaceDim] = {
        0.6, 0.1, 0.2,
        1.0, 1.1, 1.2,
        4.7, 9.5, 8.7,
        3.4, 0.7, 9.8,
        3.4, 9.8, 5.7,
    };
    const double data[numLocs*numVals] = {
        6.6, 3.4,
        5.5, 6.7,
        2.3, 4.1,
        5.7, 2.0,
        6.3, 6.7,
    };

    SimpleDBData dataOut;
    dataOut.allocate(numLocs, numVals, spaceDim, dataDim);
    dataOut.data(data, numLocs, numVals);
    dataOut.coordinates(coords, numLocs, spaceDim);
    dataOut.names(names, numVals);
    dataOut.units(units, numVals);

    const char* filename = "spatialdb_ascii.dat";
    geocoords::CSCart csOut;
    SimpleIOAscii dbIO;
    dbIO.filename(filename);
    dbIO.write(dataOut, &csOut);

    SimpleDBData dataIn;
    geocoords::CoordSys* csIn = NULL;
    dbIO.read(&dataIn, &csIn);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of locations.", numLocs, dataIn.numLocs());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numVals, dataIn.numValues());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", dataDim, dataIn.dataDim());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", spaceDim, dataIn.spaceDim());
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in value names.", std::string(names[iVal]), std::string(dataIn.name(iVal)));
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mistmatch in value units", std::string(units[iVal]), std::string(dataIn.units(iVal)));
    } // for

    const double tolerance = 1.0e-06;
    for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
        const double* coordinates = dataIn.coordinates(iLoc);
        for (size_t iDim = 0; iDim < spaceDim; ++iDim, ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in coordinates.", 1.0, coordinates[iDim]/coords[i], tolerance);
        } // for
    } // for

    for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
        const double* values = dataIn.data(iLoc);
        for (size_t iVal = 0; iVal < numVals; ++iVal, ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in values.", 1.0, values[iVal]/data[i], tolerance);
        } // for
    } // for

    delete csIn;csIn = NULL;
} // testWriteRead


// ----------------------------------------------------------------------
// Test filename(), read() with spatial database file that contains
// comments.
void
spatialdata::spatialdb::TestSimpleIOAscii::testReadComments(void) { // testReadComments
    const size_t spaceDim = 3;
    const size_t numLocs = 5;
    const size_t numVals = 2;
    const size_t dataDim = 3;
    const char* names[numVals] = { "One", "Two" };
    const char* units[numVals] = { "m", "m" };
    const double coords[numLocs*spaceDim] = {
        0.6, 0.1, 0.2,
        1.0, 1.1, 1.2,
        4.7, 9.5, 8.7,
        3.4, 0.7, 9.8,
        3.4, 9.8, 5.7,
    };
    const double data[numLocs*numVals] = {
        6.6, 3.4,
        5.5, 6.7,
        2.3, 4.1,
        5.7, 2.0,
        6.3, 6.7,
    };

    const char* filename = "data/spatial_comments.dat";
    SimpleIOAscii dbIO;
    dbIO.filename(filename);

    SimpleDBData dataIn;
    geocoords::CoordSys* csIn = NULL;
    dbIO.read(&dataIn, &csIn);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points.", numLocs, dataIn.numLocs());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numVals, dataIn.numValues());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", dataDim, dataIn.dataDim());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", spaceDim, dataIn.spaceDim());
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in value names.", std::string(names[iVal]), std::string(dataIn.name(iVal)));
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in value units.", std::string(units[iVal]), std::string(dataIn.units(iVal)));
    } // for

    const double tolerance = 1.0e-06;
    for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
        const double* coordinates = dataIn.coordinates(iLoc);
        for (size_t iDim = 0; iDim < spaceDim; ++iDim, ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in point coordinates.", 1.0, coordinates[iDim]/coords[i], tolerance);
        } // for
    } // for

    for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
        const double* values = dataIn.data(iLoc);
        for (size_t iVal = 0; iVal < numVals; ++iVal, ++i) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in point values.", 1.0, values[iVal]/data[i], tolerance);
        } // for
    } // for

    delete csIn;csIn = NULL;
} // testReadComments


// End of file
