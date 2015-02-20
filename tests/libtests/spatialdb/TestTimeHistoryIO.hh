// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestTimeHistoryIO.hh
 *
 * @brief C++ TestTimeHistoryIO object
 *
 * C++ unit testing for TimeHistoryIO.
 */

#if !defined(spatialdata_spatialdb_testtimehistoryio_hh)
#define spatialdata_spatialdb_testtimehistoryio_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace spatialdb {
    class TestTimeHistoryIO;
    class TimeHistoryIO; // USES TimeHistoryIO
  } // spatialdb
} // spatialdata

/// C++ unit testing for TimeHistoryIO
class spatialdata::spatialdb::TestTimeHistoryIO : public CppUnit::TestFixture
{ // class TestTimeHistoryIO

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestTimeHistoryIO );
  CPPUNIT_TEST( testIO );
  CPPUNIT_TEST( testReadComments );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test read(), write().
  void testIO(void);

  /// Test read() with time history file that contains comments.
  void testReadComments(void);

}; // class TestTimeHistoryIO

#endif // spatialdata_spatialdb_testtimehistoryio_hh


// End of file 
