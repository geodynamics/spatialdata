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

#include "spatialdata/spatialdb/SimpleIOAscii.hh" // Test subject

#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleIOAscii;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestSimpleIOAscii {
    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test filename(), read(), write().
    static
    void testWriteRead(void);

    /// Test filename(), read() with spatial database file that contains
    /// comments.
    static
    void testReadComments(void);

}; // class TestSimpleIOAscii

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSimpleIOAscii::testWriteRead", "[TestSimpleIOAscii]") {
    spatialdata::spatialdb::TestSimpleIOAscii::testWriteRead();
}
TEST_CASE("TestSimpleIOAscii::testReadComments", "[TestSimpleIOAscii]") {
    spatialdata::spatialdb::TestSimpleIOAscii::testReadComments();
}

// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleIOAscii::testWriteRead(void) {
    const size_t spaceDimE = 3;
    const size_t numLocsE = 5;
    const size_t numValsE = 2;
    const size_t dataDimE = 3;
    const char* names[numValsE] = { "One", "Two" };
    const char* units[numValsE] = { "m", "m" };
    const double coordsE[numLocsE*spaceDimE] = {
        0.6, 0.1, 0.2,
        1.0, 1.1, 1.2,
        4.7, 9.5, 8.7,
        3.4, 0.7, 9.8,
        3.4, 9.8, 5.7,
    };
    const double dataE[numLocsE*numValsE] = {
        6.6, 3.4,
        5.5, 6.7,
        2.3, 4.1,
        5.7, 2.0,
        6.3, 6.7,
    };

    SimpleDBData dataOut;
    dataOut.allocate(numLocsE, numValsE, spaceDimE, dataDimE);
    dataOut.setData(dataE, numLocsE, numValsE);
    dataOut.setCoordinates(coordsE, numLocsE, spaceDimE);
    dataOut.setNames(names, numValsE);
    dataOut.setUnits(units, numValsE);

    const char* filename = "spatialdb_ascii.dat";
    geocoords::CSCart csOut;
    SimpleIOAscii dbIO;
    dbIO.setFilename(filename);
    dbIO.write(dataOut, &csOut);

    SimpleDBData dataIn;
    geocoords::CoordSys* csIn = NULL;
    dbIO.read(&dataIn, &csIn);

    CHECK(numLocsE == dataIn.getNumLocs());
    CHECK(dataDimE == dataIn.getDataDim());
    CHECK(spaceDimE == dataIn.getSpaceDim());
    REQUIRE(numValsE == dataIn.getNumValues());
    for (size_t iVal = 0; iVal < numValsE; ++iVal) {
        CHECK(std::string(names[iVal]) == std::string(dataIn.getName(iVal)));
        CHECK(std::string(units[iVal]) == std::string(dataIn.getUnits(iVal)));
    } // for

    const double tolerance = 1.0e-06;
    for (size_t iLoc = 0, i = 0; iLoc < numLocsE; ++iLoc) {
        const double* coordinates = dataIn.getCoordinates(iLoc);
        for (size_t iDim = 0; iDim < spaceDimE; ++iDim, ++i) {
            const double toleranceV = fabs(coordsE[i]) > 0.0 ? fabs(coordsE[i]) * tolerance : tolerance;
            CHECK_THAT(coordinates[iDim], Catch::Matchers::WithinAbs(coordsE[i], toleranceV));
        } // for
    } // for

    for (size_t iLoc = 0, i = 0; iLoc < numLocsE; ++iLoc) {
        const double* values = dataIn.getData(iLoc);
        for (size_t iVal = 0; iVal < numValsE; ++iVal, ++i) {
            const double toleranceV = fabs(dataE[i]) > 0.0 ? fabs(dataE[i]) * tolerance : tolerance;
            CHECK_THAT(values[iVal], Catch::Matchers::WithinAbs(dataE[i], toleranceV));
        } // for
    } // for

    delete csIn;csIn = NULL;
} // testWriteRead


// ----------------------------------------------------------------------
// Test filename(), read() with spatial database file that contains
// comments.
void
spatialdata::spatialdb::TestSimpleIOAscii::testReadComments(void) {
    const size_t spaceDimE = 3;
    const size_t numLocsE = 5;
    const size_t numValsE = 2;
    const size_t dataDimE = 3;
    const char* names[numValsE] = { "One", "Two" };
    const char* units[numValsE] = { "m", "m" };
    const double coordsE[numLocsE*spaceDimE] = {
        0.6, 0.1, 0.2,
        1.0, 1.1, 1.2,
        4.7, 9.5, 8.7,
        3.4, 0.7, 9.8,
        3.4, 9.8, 5.7,
    };
    const double dataE[numLocsE*numValsE] = {
        6.6, 3.4,
        5.5, 6.7,
        2.3, 4.1,
        5.7, 2.0,
        6.3, 6.7,
    };

    const char* filename = "data/spatial_comments.dat";
    SimpleIOAscii dbIO;
    dbIO.setFilename(filename);

    SimpleDBData dataIn;
    geocoords::CoordSys* csIn = NULL;
    dbIO.read(&dataIn, &csIn);

    CHECK(numLocsE == dataIn.getNumLocs());
    CHECK(numValsE == dataIn.getNumValues());
    CHECK(dataDimE == dataIn.getDataDim());
    CHECK(spaceDimE == dataIn.getSpaceDim());
    for (size_t iVal = 0; iVal < numValsE; ++iVal) {
        CHECK(std::string(names[iVal]) == std::string(dataIn.getName(iVal)));
        CHECK(std::string(units[iVal]) == std::string(dataIn.getUnits(iVal)));
    } // for

    const double tolerance = 1.0e-06;
    for (size_t iLoc = 0, i = 0; iLoc < numLocsE; ++iLoc) {
        const double* coordinates = dataIn.getCoordinates(iLoc);
        for (size_t iDim = 0; iDim < spaceDimE; ++iDim, ++i) {
            const double toleranceV = fabs(coordsE[i]) > 0.0 ? fabs(coordsE[i]) * tolerance : tolerance;
            CHECK_THAT(coordinates[iDim], Catch::Matchers::WithinAbs(coordsE[i], toleranceV));
        } // for
    } // for

    for (size_t iLoc = 0, i = 0; iLoc < numLocsE; ++iLoc) {
        const double* values = dataIn.getData(iLoc);
        for (size_t iVal = 0; iVal < numValsE; ++iVal, ++i) {
            const double toleranceV = fabs(dataE[i]) > 0.0 ? fabs(dataE[i]) * tolerance : tolerance;
            CHECK_THAT(values[iVal], Catch::Matchers::WithinAbs(dataE[i], toleranceV));
        } // for
    } // for

    delete csIn;csIn = NULL;
} // testReadComments


// End of file
