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

/** @file tests/libtests/utils/TestSpatialdataVersion.hh
 *
 * @brief C++ TestSpatialdataVersion object
 *
 * C++ unit testing for SpatialdataVersion.
 */

#if !defined(spatialdata_testspatialdataversion_hh)
#define spatialdata_testspatialdataversion_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace utils {
    class TestSpatialdataVersion;
  } // utils
} // spatialdata

/// C++ unit testing for SpatialdataVersion
class spatialdata::utils::TestSpatialdataVersion : public CppUnit::TestFixture
{ // class TestSpatialdataVersion

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSpatialdataVersion );

  CPPUNIT_TEST( testIsRelease );
  CPPUNIT_TEST( testVersion );
  CPPUNIT_TEST( testGitRevision );
  CPPUNIT_TEST( testGitHash );
  CPPUNIT_TEST( testGitDate );
  CPPUNIT_TEST( testGitBranch );
  CPPUNIT_TEST( testProjVersion );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test isRelease()
  void testIsRelease(void);

  /// Test version()
  void testVersion(void);

  /// Test gitRevision()
  void testGitRevision(void);

  /// Test gitHash()
  void testGitHash(void);

  /// Test gitDate()
  void testGitDate(void);

  /// Test gitBranch()
  void testGitBranch(void);

  /// Test projVersion()
  void testProjVersion(void);

}; // class TestSpatialdataVersion

#endif // spatialdata_utils_testspatialdataversion_hh

// End of file 
