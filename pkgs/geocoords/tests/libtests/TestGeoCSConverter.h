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
  CPPUNIT_TEST( testConvertGeoDatumH );
  CPPUNIT_TEST( testConvertGeoDatumA );
  CPPUNIT_TEST( testConvertGeoDatumB );
  CPPUNIT_TEST( testConvertGeoXYZ );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test convert() with change in horizontal datum
  void testConvertGeoDatumH(void);

  /// Test convert() with changes in both vertical and horizontal datums
  /// NAD27Elev -> WGS84Geoid
  void testConvertGeoDatumA(void);

  /// Test convert() with changes in both vertical and horizontal datums
  /// WGS84Geoid -> NAD27Elev
  void testConvertGeoDatumB(void);

  /// Test convert() with latlong to geocent
  void testConvertGeoXYZ(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _LONLATNAD27ELEV[]; ///< Array of locations in NAD27
  static const double _LONLATWGS84ELEV[]; ///< Array of locs in WGS84 (elev)
  static const double _LONLATWGS84GEOID[]; ///< Array of locs in WGS (geoid ht)
  static const double _XYZECEF[]; ///< Array of locations in ECEF
  static const int _NUMLOCS; ///< Number of locations

}; // class TestGeoCSConverter

#endif // spatialdata_testgeocsconverter

// version
// $Id: TestGeoCSConverter.h,v 1.3 2005/07/02 00:21:13 baagaard Exp $

// End of file 
