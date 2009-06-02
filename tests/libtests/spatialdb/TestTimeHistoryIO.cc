// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestTimeHistoryIO.hh" // Implementation of class methods

#include "spatialdata/spatialdb/TimeHistoryIO.hh" // USES TimeHistoryIO
#include "spatialdata/units/Parser.hh" // USES Parser

#include <string.h> // USES strcmp()
#include <sstream> // USES std::ostringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestTimeHistoryIO );

// ----------------------------------------------------------------------
// Test write(), read().
void
spatialdata::spatialdb::TestTimeHistoryIO::testIO(void)
{ // testIO
  const int npts = 6;
  const double time[npts] = { 0.0, 0.2, 0.8, 1.0, 2.0, 10.0 };
  const double amplitude[npts] = { 0.0, 0.4, 1.6, 2.0, 4.0, 0.0 };
  const char* timeUnits = "minute";

  const char* filename = "data/timehistory.dat";
  TimeHistoryIO::write(time, npts, amplitude, npts, timeUnits, filename);

  int nptsIn = 0;
  double* timeIn = 0;
  double* amplitudeIn = 0;
  TimeHistoryIO::read(&timeIn, &amplitudeIn, &nptsIn, filename);

  units::Parser parser;
  const double scale = parser.parse(timeUnits);
  CPPUNIT_ASSERT(scale > 0.0);

  CPPUNIT_ASSERT_EQUAL(npts, nptsIn);
  const double tolerance = 1.0e-06;
  for (int i=0; i < npts; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitude[i], amplitudeIn[i]/scale,
				 tolerance);
} // testIO

// ----------------------------------------------------------------------
// Test read() with time history file that contains comments.
void
spatialdata::spatialdb::TestTimeHistoryIO::testReadComments(void)
{ // testReadComments
  const int npts = 6;
  const double time[npts] = { 0.0, 0.2, 0.8, 1.0, 2.0, 10.0 };
  const double amplitude[npts] = { 0.0, 0.4, 1.6, 2.0, 4.0, 0.0 };
  const char* filename = "data/timehistory_comments.dat";

  int nptsIn = 0;
  double* timeIn = 0;
  double* amplitudeIn = 0;
  TimeHistoryIO::read(&timeIn, &amplitudeIn, &nptsIn, filename);

  CPPUNIT_ASSERT_EQUAL(npts, nptsIn);
  const double tolerance = 1.0e-06;
  for (int i=0; i < npts; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(amplitude[i], amplitudeIn[i],
				 tolerance);
} // testReadComments


// End of file 
