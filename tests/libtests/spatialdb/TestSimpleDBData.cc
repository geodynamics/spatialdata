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

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDBData;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleDBData : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSimpleDBData);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAllocate);
    CPPUNIT_TEST(testData);
    CPPUNIT_TEST(testCoordinates);
    CPPUNIT_TEST(testNames);
    CPPUNIT_TEST(testUnits);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test constructor.
    void testConstructor(void);

    /// Test allocate(), getNumLocs(), numValues(), spaceDim().
    void testAllocate(void);

    /// Test data() and dataDim().
    void testData(void);

    /// Test coordinates()
    void testCoordinates(void);

    /// Test names()
    void testNames(void);

    /// Test units()
    void testUnits(void);

}; // class TestSimpleDBData
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestSimpleDBData);

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestSimpleDBData::testConstructor(void) {
    SimpleDBData data;
} // testConstructor


// ----------------------------------------------------------------------
// Test allocate(), getNumLocs(), numValues(), spaceDim().
void
spatialdata::spatialdb::TestSimpleDBData::testAllocate(void) {
    const size_t numLocs = 4;
    const size_t numValues = 5;
    const size_t spaceDim = 3;
    const size_t dataDim = 1;

    SimpleDBData data;
    data.allocate(numLocs, numValues, spaceDim, dataDim);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of points.", numLocs, data.getNumLocs());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValues, data.getNumValues());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in spatial dimension.", spaceDim, data.getSpaceDim());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in data dimension.", dataDim, data.getDataDim());
    CPPUNIT_ASSERT(data._data);
    CPPUNIT_ASSERT(data._coordinates);
    CPPUNIT_ASSERT(data._names);
    CPPUNIT_ASSERT(data._units);
} // testAllocate


// ----------------------------------------------------------------------
// Test data()
void
spatialdata::spatialdb::TestSimpleDBData::testData(void) {
    const size_t numLocs = 4;
    const size_t numValues = 2;
    const size_t spaceDim = 3;
    const size_t dataDim = 1;

    const double valuesE[numLocs*numValues] = {
        0.11, 0.21,
        0.12, 0.22,
        0.13, 0.23,
        0.14, 0.24,
    };

    SimpleDBData data;
    data.allocate(numLocs, numValues, spaceDim, dataDim);
    data.setData(valuesE, numLocs, numValues);

    for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
        const double* values = data.getData(iLoc);
        CPPUNIT_ASSERT(values);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            CPPUNIT_ASSERT_EQUAL(valuesE[i++], values[iVal]);
        } // for
    } // for
} // testData


// ----------------------------------------------------------------------
// Test coordinates()
void
spatialdata::spatialdb::TestSimpleDBData::testCoordinates(void) {
    const size_t numLocs = 4;
    const size_t numValues = 2;
    const size_t spaceDim = 3;
    const size_t dataDim = 1;

    const double coordsE[numLocs*spaceDim] = {
        1.1, 2.1, 3.1,
        1.2, 2.2, 3.2,
        1.3, 2.3, 3.3,
        1.4, 2.4, 3.4,
    };

    SimpleDBData data;
    data.allocate(numLocs, numValues, spaceDim, dataDim);
    data.setCoordinates(coordsE, numLocs, spaceDim);

    for (size_t iLoc = 0, i = 0; iLoc < numLocs; ++iLoc) {
        const double* coords = data.getCoordinates(iLoc);
        CPPUNIT_ASSERT(coords);
        for (size_t iDim = 0; iDim < spaceDim; ++iDim) {
            CPPUNIT_ASSERT_EQUAL(coordsE[i++], coords[iDim]);
        } // for
    } // for
} // testCoordinates


// ----------------------------------------------------------------------
// Test names()
void
spatialdata::spatialdb::TestSimpleDBData::testNames(void) {
    const size_t numLocs = 4;
    const size_t numValues = 2;
    const size_t spaceDim = 3;
    const size_t dataDim = 1;

    const char* namesE[numValues] = {
        "one", "two",
    };

    SimpleDBData data;
    data.allocate(numLocs, numValues, spaceDim, dataDim);
    data.setNames(namesE, numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL(std::string(namesE[i]), std::string(data.getName(i)));
    } // for
} // testNames


// ----------------------------------------------------------------------
// Test units()
void
spatialdata::spatialdb::TestSimpleDBData::testUnits(void) {
    const size_t numLocs = 4;
    const size_t numValues = 2;
    const size_t spaceDim = 3;
    const size_t dataDim = 1;

    const char* unitsE[numValues] = {
        "m", "m/s",
    };

    SimpleDBData data;
    data.allocate(numLocs, numValues, spaceDim, dataDim);
    data.setUnits(unitsE, numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL(std::string(unitsE[i]), std::string(data.getUnits(i)));
    } // for
} // testUnits


// End of file
