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

/** @file tests/libtests/TestGeoLocalConverter.h
 *
 * @brief C++ TestGeoLocalConverter object
 *
 * C++ unit testing for TestGeoLocalConverter.
 */

#if !defined(spatialdata_testgeolocalconverter_h)
#define spatialdata_testgeolocalconverter_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  class TestGeoLocalConverter;
  class GeoLocalConverter; // USES GeoLocalConverter
}; // spatialdata

/// C++ unit testing for GeoLocalConverter
class spatialdata::TestGeoLocalConverter : public CppUnit::TestFixture
{ // class TestGeoLocalConverter

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoLocalConverter );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testGeoToWGS84 );
  CPPUNIT_TEST( testElevToGeoidHt );
  CPPUNIT_TEST( testWGS84ToECEF );
  CPPUNIT_TEST( testLocalOrigin );
  CPPUNIT_TEST( testConvert );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test geoToWGS84()
  void testGeoToWGS84(void);

  /// Test elevToGeoidHt()
  void testElevToGeoidHt(void);

  /// Test wgs84ToECEF()
  void testWGS84ToECEF(void);

  /// Test localOrigin()
  void testLocalOrigin(void);

  /// Test convert()
  void testConvert(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _LONLATNAD27ELEV[]; ///< Array of locations in NAD27
  static const double _LONLATWGS84ELEV[]; ///< Array of locs in WGS84 (elev)
  static const double _LONLATWGS84GEOID[]; ///< Array of locs in WGS (geoid ht)
  static const double _XYZECEF[]; ///< Array of locations in ECEF
  static const double _XYZLOCAL[]; ///< Array of locations in local XYZ

  static const double _ORIGINLON; ///< Longitude of local origin in NAD27
  static const double _ORIGINLAT; ///< Latitude of local origin in NAD27
  static const double _ORIGINELEV; ///< Elevation of local origin

  static const double _ORIGINX; ///< X coordinate in rotated ECEF
  static const double _ORIGINY; ///< Y coordinate in rotated ECEF
  static const double _ORIGINZ; ///< Z coordinate in rotated ECEF

  static const int _NUMLOCS; ///< Number of locations

}; // class TestGeoLocalConverter

#endif // spatialdata_testgeolocalconverter

// version
// $Id: TestGeoLocalConverter.h,v 1.1 2005/05/25 17:29:42 baagaard Exp $

// End of file 
