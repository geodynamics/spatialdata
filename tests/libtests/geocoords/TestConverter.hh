// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/geocoords/TestConverter.hh
 *
 * @brief C++ TestConverter object
 *
 * C++ unit testing for Converter.
 */

#if !defined(spatialdata_testconverter_hh)
#define spatialdata_testconverter_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestConverter;
  } // geocoords
} // spatialdata

/// C++ unit testing for Converter
class spatialdata::geocoords::TestConverter : public CppUnit::TestFixture
{ // class TestConverter

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestConverter );
  CPPUNIT_TEST( testNAD27ToWGS84 );
  CPPUNIT_TEST( testWGS84ToNAD27 );
  CPPUNIT_TEST( testWGS84ToECEF );
  CPPUNIT_TEST( testECEFToWGS84 );
  CPPUNIT_TEST( testNAD27ToLocal );
  CPPUNIT_TEST( testLocalToNAD27 );
  CPPUNIT_TEST( testCartToCart );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test NAD27 -> WGS84
  void testNAD27ToWGS84(void);

  /// Test WGS84 -> NAD27
  void testWGS84ToNAD27(void);

  /// Test WGS84 -> ECEF
  void testWGS84ToECEF(void);

  /// Test ECEF -> WGS84
  void testECEFToWGS84(void);

  /// Test NAD27 -> local
  void testNAD27ToLocal(void);

  /// Test local -> NAD27
  void testLocalToNAD27(void);

  /// Test xyz -> xyz
  void testCartToCart(void);

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

  static const int _NUMLOCS; ///< Number of locations

}; // class TestConverter

#endif // spatialdata_geocoords_testconverter_hh


// End of file 
