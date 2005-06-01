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

/** @file tests/libtests/TestGeoCSConverter.h
 *
 * @brief C++ TestGeoCSConverter object
 *
 * C++ unit testing for TestGeoCSConverter.
 */

#if !defined(spatialdata_testgeocsconverter_h)
#define spatialdata_testgeocsconverter_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  class TestGeoCSConverter;
  class GeoCSConverter; // USES GeoCSConverter
}; // spatialdata

/// C++ unit testing for GeoCSConverter
class spatialdata::TestGeoCSConverter : public CppUnit::TestFixture
{ // class TestGeoCSConverter

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoCSConverter );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testConvertGeoDatum );
  CPPUNIT_TEST( testConvertGeoXYZ );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test convert() with datum switch
  void testConvertGeoDatum(void);

  /// Test convert() with latlong to geocent
  void testConvertGeoXYZ(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _LONLATSRC[]; ///< Array of source locations
  static const double _LONLATDEST[]; ///< Array of destination lat/lon coords
  static const double _XYZDEST[]; ///< Array of destination xyz coordinates
  static const int _NUMLOCS; ///< Number of locations

}; // class TestGeoCSConverter

#endif // spatialdata_testgeocsconverter

// version
// $Id: TestGeoCSConverter.h,v 1.2 2005/06/01 16:51:58 baagaard Exp $

// End of file 
