// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/spatialdb/TimeHistoryIO.hh" // USES TimeHistoryIO
#include "spatialdata/units/Parser.hh" // USES Parser

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestTimeHistoryIO;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestTimeHistoryIO {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test read(), write().
    static
    void testWriteRead(void);

    /// Test read() with time history file that contains comments.
    static
    void testReadComments(void);

}; // class TestTimeHistoryIO

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestTimeHistoryIO::testWriteRead", "[TestTimeHistoryIO]") {
    spatialdata::spatialdb::TestTimeHistoryIO::testWriteRead();
}
TEST_CASE("TestTimeHistoryIO::testReadComments", "[TestTimeHistoryIO]") {
    spatialdata::spatialdb::TestTimeHistoryIO::testReadComments();
}

// ------------------------------------------------------------------------------------------------
// Test write(), read().
void
spatialdata::spatialdb::TestTimeHistoryIO::testWriteRead(void) {
    const size_t npts = 6;
    const double time[npts] = { 0.0, 0.2, 0.8, 1.0, 2.0, 10.0 };
    const double amplitude[npts] = { 0.0, 0.4, 1.6, 2.0, 4.0, 0.0 };
    const char* timeUnits = "minute";

    const char* filename = "timehistory.dat";
    TimeHistoryIO::write(time, npts, amplitude, npts, timeUnits, filename);

    size_t nptsIn = 0;
    double* timeIn = 0;
    double* amplitudeIn = 0;
    TimeHistoryIO::read(&timeIn, &amplitudeIn, &nptsIn, filename);

    units::Parser parser;
    const double scale = parser.parse(timeUnits);
    CHECK(scale > 0.0);

    REQUIRE(npts == nptsIn);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < npts; ++i) {
        CHECK_THAT(timeIn[i]/scale, Catch::Matchers::WithinAbs(time[i], tolerance));
        CHECK_THAT(amplitude[i], Catch::Matchers::WithinAbs(amplitudeIn[i], tolerance));
    } // for

    delete[] timeIn;timeIn = 0;
    delete[] amplitudeIn;amplitudeIn = 0;
} // testWriteRead


// ----------------------------------------------------------------------
// Test read() with time history file that contains comments.
void
spatialdata::spatialdb::TestTimeHistoryIO::testReadComments(void) {
    const size_t npts = 6;
    const double time[npts] = { 0.0, 0.2, 0.8, 1.0, 2.0, 10.0 };
    const double amplitude[npts] = { 0.0, 0.4, 1.6, 2.0, 4.0, 0.0 };
    const char* filename = "data/timehistory_comments.dat";

    size_t nptsIn = 0;
    double* timeIn = 0;
    double* amplitudeIn = 0;
    TimeHistoryIO::read(&timeIn, &amplitudeIn, &nptsIn, filename);

    REQUIRE(npts == nptsIn);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < npts; ++i) {
        CHECK_THAT(timeIn[i], Catch::Matchers::WithinAbs(time[i], tolerance));
        CHECK_THAT(amplitude[i], Catch::Matchers::WithinAbs(amplitudeIn[i], tolerance));
    } // for

    delete[] timeIn;timeIn = 0;
    delete[] amplitudeIn;amplitudeIn = 0;
} // testReadComments


// End of file
