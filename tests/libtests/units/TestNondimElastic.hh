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

/** @file tests/libtests/units/TestNondimElastic.hh
 *
 * @brief C++ TestNondimElastic object
 *
 * C++ unit testing for NondimElastic.
 */

#if !defined(spatialdata_units_testnondimelastic_hh)
#define spatialdata_units_testnondimelastic_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace units {
    class TestNondimElastic;
  } // units
} // spatialdata

/// C++ unit testing for NondimElastic
class spatialdata::units::TestNondimElastic : public CppUnit::TestFixture
{ // class TestNondimElastic

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestNondimElastic );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssignment );
  CPPUNIT_TEST( testLengthScale );
  CPPUNIT_TEST( testPressureScale );
  CPPUNIT_TEST( testTimeScale );
  CPPUNIT_TEST( testDensityScale );
  CPPUNIT_TEST( testUtonLength );
  CPPUNIT_TEST( testNtouLength );
  CPPUNIT_TEST( testUtonLengthArray );
  CPPUNIT_TEST( testNtouLengthArray );
  CPPUNIT_TEST( testUtonPressure );
  CPPUNIT_TEST( testNtouPressure );
  CPPUNIT_TEST( testUtonPressureArray );
  CPPUNIT_TEST( testNtouPressureArray );
  CPPUNIT_TEST( testUtonTime );
  CPPUNIT_TEST( testNtouTime );
  CPPUNIT_TEST( testUtonTimeArray );
  CPPUNIT_TEST( testNtouTimeArray );
  CPPUNIT_TEST( testUtonDensity );
  CPPUNIT_TEST( testNtouDensity );
  CPPUNIT_TEST( testUtonDensityArray );
  CPPUNIT_TEST( testNtouDensityArray );

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

  /// Test utonLength().
  void testUtonLength(void);

  /// Test ntouLength().
  void testNtouLength(void);

  /// Test utonLength() with arrays.
  void testUtonLengthArray(void);

  /// Test ntouLength() with arrays.
  void testNtouLengthArray(void);

  /// Test utonPressure().
  void testUtonPressure(void);

  /// Test ntouPressure().
  void testNtouPressure(void);

  /// Test utonPressure() with arrays.
  void testUtonPressureArray(void);

  /// Test ntouPressure() with arrays.
  void testNtouPressureArray(void);

  /// Test utonTime().
  void testUtonTime(void);

  /// Test ntouTime().
  void testNtouTime(void);

  /// Test utonTime() with arrays.
  void testUtonTimeArray(void);

  /// Test ntouTime() with arrays.
  void testNtouTimeArray(void);

  /// Test utonDensity().
  void testUtonDensity(void);

  /// Test ntouDensity().
  void testNtouDensity(void);

  /// Test utonDensity() with arrays.
  void testUtonDensityArray(void);

  /// Test ntouDensity() with arrays.
  void testNtouDensityArray(void);

}; // class TestNondimElastic

#endif // spatialdata_units_testnondimelastic_hh


// End of file 
