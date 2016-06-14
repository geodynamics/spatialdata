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

/** @file tests/libtests/spatialdb/TestTimeHistory.hh
 *
 * @brief C++ TestTimeHistory object
 *
 * C++ unit testing for TimeHistory.
 */

#if !defined(spatialdata_spatialdb_testtimehistory_hh)
#define spatialdata_spatialdb_testtimehistory_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestTimeHistory;
    class TimeHistory; // USES TimeHistory
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleIO
class spatialdata::spatialdb::TestTimeHistory : public CppUnit::TestFixture
{ // class TestTimeHistory

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestTimeHistory );

  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testFilename );
  CPPUNIT_TEST( testOpenClose );
  CPPUNIT_TEST( testQuery );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test label().
  void testLabel(void);

  /// Test filename().
  void testFilename(void);

  /// Test open() and close()
  void testOpenClose(void);

  /// Test query().
  void testQuery(void);

}; // class TestTimeHistory

#endif // spatialdata_spatialdb_testtimehistory_hh


// End of file 
