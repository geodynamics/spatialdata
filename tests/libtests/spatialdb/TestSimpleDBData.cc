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

#include "spatialdata/spatialdb/SimpleDBData.hh" // Test subject

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDBData;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleDBData {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test constructor.
    static
    void testConstructor(void);

    /// Test allocate(), getNumLocs(), numValues(), spaceDim().
    static
    void testAllocate(void);

    /// Test data() and dataDim().
    static
    void testData(void);

    /// Test coordinates()
    static
    void testCoordinates(void);

    /// Test names()
    static
    void testNames(void);

    /// Test units()
    static
    void testUnits(void);

}; // class TestSimpleDBData

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSimpleDBData::testConstructor", "[TestSimpleDBData]") {
    spatialdata::spatialdb::TestSimpleDBData::testConstructor();
}
TEST_CASE("TestSimpleDBData::testAllocate", "[TestSimpleDBData]") {
    spatialdata::spatialdb::TestSimpleDBData::testAllocate();
}
TEST_CASE("TestSimpleDBData::testData", "[TestSimpleDBData]") {
    spatialdata::spatialdb::TestSimpleDBData::testData();
}
TEST_CASE("TestSimpleDBData::testCoordinates", "[TestSimpleDBData]") {
    spatialdata::spatialdb::TestSimpleDBData::testCoordinates();
}
TEST_CASE("TestSimpleDBData::testNames", "[TestSimpleDBData]") {
    spatialdata::spatialdb::TestSimpleDBData::testNames();
}
TEST_CASE("TestSimpleDBData::testUnits", "[TestSimpleDBData]") {
    spatialdata::spatialdb::TestSimpleDBData::testUnits();
}

// ------------------------------------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestSimpleDBData::testConstructor(void) {
    SimpleDBData data;
} // testConstructor


// ------------------------------------------------------------------------------------------------
// Test allocate(), getNumLocs(), numValues(), spaceDim().
void
spatialdata::spatialdb::TestSimpleDBData::testAllocate(void) {
    const size_t numLocs = 4;
    const size_t numValues = 5;
    const size_t spaceDim = 3;
    const size_t dataDim = 1;

    SimpleDBData data;
    data.allocate(numLocs, numValues, spaceDim, dataDim);

    CHECK(numLocs == data.getNumLocs());
    CHECK(numValues == data.getNumValues());
    CHECK(spaceDim == data.getSpaceDim());
    CHECK(dataDim == data.getDataDim());

    assert(data._data);
    assert(data._coordinates);
    assert(data._names);
    assert(data._units);
} // testAllocate


// ------------------------------------------------------------------------------------------------
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
        assert(values);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            CHECK(valuesE[i++] == values[iVal]);
        } // for
    } // for
} // testData


// ------------------------------------------------------------------------------------------------
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
        assert(coords);
        for (size_t iDim = 0; iDim < spaceDim; ++iDim) {
            CHECK(coordsE[i++] == coords[iDim]);
        } // for
    } // for
} // testCoordinates


// ------------------------------------------------------------------------------------------------
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
        CHECK(std::string(namesE[i]) == std::string(data.getName(i)));
    } // for
} // testNames


// ------------------------------------------------------------------------------------------------
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
        CHECK(std::string(unitsE[i]) == std::string(data.getUnits(i)));
    } // for
} // testUnits


// End of file
