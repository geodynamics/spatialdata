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

#include "spatialdata/spatialdb/TimeHistory.hh" // USES TimeHistory
#include "spatialdata/spatialdb/TimeHistoryIO.hh" // USES TimeHistoryIO
#include "spatialdata/units/Parser.hh" // USES Parser

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestTimeHistory;
        class TimeHistory; // USES TimeHistory
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestTimeHistory : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestTimeHistory);

    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testOpenClose);
    CPPUNIT_TEST(testQuery);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test accessors.
    void testAccessors(void);

    /// Test open() and close()
    void testOpenClose(void);

    /// Test query().
    void testQuery(void);

}; // class TestTimeHistory
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestTimeHistory);

// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestTimeHistory::testAccessors(void) {
    const std::string label("time history A");
    const std::string filename("file.th");

    TimeHistory th;
    th.setDescription(label.c_str());
    CPPUNIT_ASSERT_EQUAL(label, std::string(th.getDescription()));

    th.setFilename(filename.c_str());
    CPPUNIT_ASSERT_EQUAL(filename, std::string(th.getFilename()));
} // testAccessors


// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestTimeHistory::testOpenClose(void) {
    const size_t npts = 6;
    const double time[npts] = { 0.0, 0.2, 0.8, 1.0, 2.0, 10.0 };
    const double amplitude[npts] = { 0.0, 0.4, 1.6, 2.0, 4.0, 0.0 };
    const char* timeUnits = "minute";

    const char* filename = "data/timehistory.data";
    TimeHistoryIO::write(time, npts, amplitude, npts, timeUnits, filename);

    TimeHistory th;
    th.setFilename(filename);

    th.close(); // Test calling close on upopened db

    th.open();

    units::Parser parser;
    const double scale = parser.parse(timeUnits);
    CPPUNIT_ASSERT(scale > 0.0);

    CPPUNIT_ASSERT_EQUAL(size_t(0), th._ilower);
    CPPUNIT_ASSERT_EQUAL(npts, th._npts);
    CPPUNIT_ASSERT(th._time);
    CPPUNIT_ASSERT(th._amplitude);
    const double tolerance = 1.0e-06;
    for (size_t i = 0; i < npts; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(time[i], th._time[i]/scale, tolerance);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitude[i], th._amplitude[i], tolerance);
    } // for

    th.close();
    CPPUNIT_ASSERT_EQUAL(size_t(0), th._npts);
    CPPUNIT_ASSERT(!th._time);
    CPPUNIT_ASSERT(!th._amplitude);

    th.close(); // Test calling close when already closed
} // testOpenClose


// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestTimeHistory::testQuery(void) {
    const char* filename = "data/timehistory.timedb";
    const size_t nqueries = 7;
    const double timeQ[nqueries] = {
        0.5, 0.0, 0.6, 2.0, 5.0, 20.0, 8.0
    };
    const double amplitudeE[nqueries] = {
        1.0, 0.0, 1.2, 4.0, 2.5, 0.0, 1.0
    };
    const int errE[nqueries] = {
        0, 0, 0, 0, 0, 1, 0
    };

    TimeHistory th;
    th.setFilename(filename);

    th.open();

    const double tolerance = 1.0e-06;
    double amplitude = 0.0;
    for (size_t i = 0; i < nqueries; ++i) {
        int err = th.query(&amplitude, timeQ[i]);
        CPPUNIT_ASSERT_EQUAL(errE[i], err);
        if (0 == errE[i]) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitudeE[i], amplitude, tolerance);
        } // if
    } // for

    th.close();
} // testQuery


// End of file
