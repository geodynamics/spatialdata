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

/** @file tests/libtests/TestGeoid.h
 *
 * @brief C++ TestGeoid object
 *
 * C++ unit testing for TestGeoid.
 */

#if !defined(spatialdata_geocoords_testgeoid_h)
#define spatialdata_geocoords_testgeoid_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
  class TestGeoid;
  } // geocoords
} // spatialdata

/// C++ unit testing for Geoid
class spatialdata::geocoords::TestGeoid : public CppUnit::TestFixture
{ // class TestGeoid

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoid );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testElevation );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test elevation()
  void testElevation(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _LONLAT[]; ///< Array of geographic locations
  static const double _GEOIDHT[]; ///< Array of geoid heights
  static const int _NUMLOCS; ///< Number of locations

}; // class TestGeoid

#endif // spatialdata_geocoords_testgeoid

// version
// $Id: TestGeoid.h,v 1.1 2005/06/19 19:38:36 baagaard Exp $

// End of file 
