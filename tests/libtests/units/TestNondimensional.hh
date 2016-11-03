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

/** @file tests/libtests/units/TestNondimensional.hh
 *
 * @brief C++ TestNondimensional object
 *
 * C++ unit testing for Nondimensional.
 */

#if !defined(spatialdata_units_testnondimensional_hh)
#define spatialdata_units_testnondimensional_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace units {
    class TestNondimensional;
  } // units
} // spatialdata

/// C++ unit testing for Nondimensional
class spatialdata::units::TestNondimensional : public CppUnit::TestFixture
{ // class TestNondimensional

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestNondimensional );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testLengthScale );
  CPPUNIT_TEST( testPressureScale );
  CPPUNIT_TEST( testTimeScale );
  CPPUNIT_TEST( testDensityScale );
  CPPUNIT_TEST( testTemperatureScale );
  CPPUNIT_TEST( testNondimensionalize );
  CPPUNIT_TEST( testDimensionalize );
  CPPUNIT_TEST( testNondimensionalizeArray );
  CPPUNIT_TEST( testDimensionalizeArray );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor.
  void testConstructor(void);

  /// Test copy constructor.
  void testCopyConstructor(void);

  /// Test assignment.
  void testAssignment(void);

  /// Test lengthScale().
  void testLengthScale(void);

  /// Test pressureScale().
  void testPressureScale(void);

  /// Test timeScale().
  void testTimeScale(void);

  /// Test densityScale().
  void testDensityScale(void);

  /// Test temperatureScale().
  void testTemperatureScale(void);

  /// Test nondimensionalize().
  void testNondimensionalize(void);

  /// Test dimensionalize().
  void testDimensionalize(void);

  /// Test nondimensionalie() with arrays.
  void testNondimensionalizeArray(void);

  /// Test dimensionalize() with arrays.
  void testDimensionalizeArray(void);

}; // class TestNondimensional

#endif // spatialdata_units_testnondimensional_hh


// End of file 
