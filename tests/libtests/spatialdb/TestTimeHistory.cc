// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestTimeHistory.hh" // implementation of class methods

#include "spatialdata/spatialdb/TimeHistory.hh" // USES TimeHistory
#include "spatialdata/spatialdb/TimeHistoryIO.hh" // USES TimeHistoryIO
#include "spatialdata/units/Parser.hh" // USES Parser

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestTimeHistory );

// ----------------------------------------------------------------------
// Test label().
void
spatialdata::spatialdb::TestTimeHistory::testLabel(void)
{ // testLabel
  const std::string& label = "time history A";

  TimeHistory th;
  th.label(label.c_str());
  CPPUNIT_ASSERT_EQUAL(label, std::string(th.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test filename().
void
spatialdata::spatialdb::TestTimeHistory::testFilename(void)
{ // testFilename
  const std::string& filename = "file.th";

  TimeHistory th;
  th.filename(filename.c_str());
  CPPUNIT_ASSERT_EQUAL(filename, std::string(th.filename()));
} // testFilename

// ----------------------------------------------------------------------
// Test open() and close()
void
spatialdata::spatialdb::TestTimeHistory::testOpenClose(void)
{ // testOpenClose
  const int npts = 6;
  const double time[npts] = { 0.0, 0.2, 0.8, 1.0, 2.0, 10.0 };
  const double amplitude[npts] = { 0.0, 0.4, 1.6, 2.0, 4.0, 0.0 };
  const char* timeUnits = "minute";

  const char* filename = "data/timehistory.data";
  TimeHistoryIO::write(time, npts, amplitude, npts, timeUnits, filename);

  TimeHistory th;
  th.filename(filename);

  // Test calling close on upopened db
  th.close();

  th.open();

  units::Parser parser;
  const double scale = parser.parse(timeUnits);
  CPPUNIT_ASSERT(scale > 0.0);

  CPPUNIT_ASSERT_EQUAL(0, th._ilower);
  CPPUNIT_ASSERT_EQUAL(npts, th._npts);
  CPPUNIT_ASSERT(0 != th._time);
  CPPUNIT_ASSERT(0 != th._amplitude);
  const double tolerance = 1.0e-06;
  for (int i=0; i < npts; ++i) {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(time[i], th._time[i]/scale, tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitude[i], th._amplitude[i],
				 tolerance);
  } // for

  th.close();
  CPPUNIT_ASSERT_EQUAL(0, th._npts);
  CPPUNIT_ASSERT(0 == th._time);
  CPPUNIT_ASSERT(0 == th._amplitude);

  th.close(); // Test calling close when already closed
} // testOpenClose

// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestTimeHistory::testQuery(void)
{ // testQuery
  const char* filename = "data/timehistory.timedb";
  const int nqueries = 7;
  const double timeQ[nqueries] =
    { 0.5, 0.0, 0.6, 2.0, 5.0, 20.0, 8.0 };
  const double amplitudeE[nqueries] =
    { 1.0, 0.0, 1.2, 4.0, 2.5, 0.0, 1.0 };
  const int errE[nqueries] =
    { 0, 0, 0, 0, 0, 1, 0 };

  TimeHistory th;
  th.filename(filename);

  th.open();
  
  const double tolerance = 1.0e-06;
  double amplitude = 0.0;
  for (int i=0; i < nqueries; ++i) {
    int err = th.query(&amplitude, timeQ[i]);
    CPPUNIT_ASSERT_EQUAL(errE[i], err);
    if (0 == errE[i])
      CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitudeE[i], amplitude, tolerance);
  } // for

  th.close();
} // testQuery


// End of file 
