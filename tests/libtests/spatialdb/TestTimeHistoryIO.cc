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

#include "spatialdata/spatialdb/TimeHistoryIO.hh" // USES TimeHistoryIO
#include "spatialdata/units/Parser.hh" // USES Parser

#include <sstream> // USES std::ostringstream

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestTimeHistoryIO;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestTimeHistoryIO : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestTimeHistoryIO);
    CPPUNIT_TEST(testWriteRead);
    CPPUNIT_TEST(testReadComments);
    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test read(), write().
    void testWriteRead(void);

    /// Test read() with time history file that contains comments.
    void testReadComments(void);

}; // class TestTimeHistoryIO
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestTimeHistoryIO);

// ----------------------------------------------------------------------
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
    CPPUNIT_ASSERT(scale > 0.0);

    CPPUNIT_ASSERT_EQUAL(npts, nptsIn);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < npts; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(time[i], timeIn[i]/scale, tolerance);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitude[i], amplitudeIn[i], tolerance);
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

    CPPUNIT_ASSERT_EQUAL(npts, nptsIn);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < npts; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(time[i], timeIn[i], tolerance);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitude[i], amplitudeIn[i], tolerance);
    } // for

    delete[] timeIn;timeIn = 0;
    delete[] amplitudeIn;amplitudeIn = 0;
} // testReadComments


// End of file
