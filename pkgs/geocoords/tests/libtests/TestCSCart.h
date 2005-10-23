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

/** @file tests/libtests/TestCSCart.h
 *
 * @brief C++ TestCSCart object
 *
 * C++ unit testing for CSCart.
 */

#if !defined(spatialdata_geocoords_testcscart_h)
#define spatialdata_geocoords_testcscart_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCSCart;
  } // geocoords
} // spatialdata

/// C++ unit testing for CSCart
class spatialdata::geocoords::TestCSCart : public CppUnit::TestFixture
{ // class TestCSCart

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCSCart );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testToMeters );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test toMeters()
  void testToMeters(void);

  /// Test initialize()
  void testInitialize(void);

}; // class TestCSCart

#endif // spatialdata_geocoords_testcscart_h

// version
// $Id$

// End of file 
