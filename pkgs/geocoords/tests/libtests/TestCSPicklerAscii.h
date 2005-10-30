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

/** @file tests/libtests/TestCSPicklerAscii.h
 *
 * @brief C++ TestCSPicklerAscii object
 *
 * C++ unit testing for CSPicklerAscii
 */

#if !defined(spatialdata_geocoords_testcspicklerascii_h)
#define spatialdata_geocoords_testcspicklerascii_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCSPicklerAscii;
  } // geocoords
} // spatialdata

/// C++ unit testing for CSCart
class spatialdata::geocoords::TestCSPicklerAscii : public CppUnit::TestFixture
{ // class TestCSCart

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCSPicklerAscii );
  CPPUNIT_TEST( testPickleCSCart );
  CPPUNIT_TEST( testPickleCSGeo );
  CPPUNIT_TEST( testPickleCSGeoProj );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test pickle() & unpickle() for CSCart
  void testPickleCSCart(void);

  /// Test pickle() & unpickle() for CSGeo
  void testPickleCSGeo(void);

  /// Test pickle() & unpickle() for CSGeoProj
  void testPickleCSGeoProj(void);

}; // class TestCSPickleAscii

#endif // spatialdata_geocoords_testcspickleascii_h

// version
// $Id$

// End of file 
