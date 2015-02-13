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

/** @file tests/libtests/units/TestParser.hh
 *
 * @brief C++ TestParser object
 *
 * C++ unit testing for Parser.
 */

#if !defined(spatialdata_units_testparser_hh)
#define spatialdata_units_testparser_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace units {
    class TestParser;
  } // units
} // spatialdata

/// C++ unit testing for Parser
class spatialdata::units::TestParser : public CppUnit::TestFixture
{ // class TestParser

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestParser );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testLength );
  CPPUNIT_TEST( testTime );
  CPPUNIT_TEST( testVelocity );
  CPPUNIT_TEST( testDensity );
  CPPUNIT_TEST( testPressure );  
  CPPUNIT_TEST( testError );  

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor.
  void testConstructor(void);

  /// Test parse() with length scale.
  void testLength(void);

  /// Test parse() with time scale.
  void testTime(void);

  /// Test parse() with velocity scale.
  void testVelocity(void);

  /// Test parse() with density scale.
  void testDensity(void);

  /// Test parse() with pressure scale.
  void testPressure(void);

  /// Test trapping errors with parse().
  void testError(void);

}; // class TestParser

#endif // spatialdata_units_testparser_hh


// End of file 
