// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/geocoords/TestCSGeoLocalCart.hh
 *
 * @brief C++ TestCSGeoLocalCart object
 *
 * C++ unit testing for CSGeoLocalCart.
 */

#if !defined(spatialdata_geocoords_testcsgeolocalcart_hh)
#define spatialdata_geocoords_testcsgeolocalcart_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCSGeoLocalCart;
  } // geocoords
} // spatialdata

/// C++ unit testing for CSGeoLocalCart
class spatialdata::geocoords::TestCSGeoLocalCart : public CppUnit::TestFixture
{ // class TestCSGeoLocalCart

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCSGeoLocalCart );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testOrigin );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testToProjForm );
  CPPUNIT_TEST( testFromProjForm );
  CPPUNIT_TEST( testRadialDir );
  CPPUNIT_TEST( testPickle );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test origin()
  void testOrigin(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test toProjForm()
  void testToProjForm(void);

  /// Test fromProjForm()
  void testFromProjForm(void);

  /// Test radialDir()
  void testRadialDir(void);

  /// Test pickle() and unpickle()
  void testPickle(void);

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
public :

  static const char* _ELLIPSOID; ///< Name of reference ellipsoid
  static const char* _DATUMHORIZ; ///< Name of horizontal datum
  static const char* _DATUMVERT; ///< Name of vertical datum
  static const double _ORIGINLON; ///< Longitude of origin in degrees
  static const double _ORIGINLAT; ///< Latitude of origin in degrees
  static const double _ORIGINELEV; ///< Elevation of origin in meters
  static const double _ORIGINX; ///< X coordinate of origin
  static const double _ORIGINY; ///< Y coordinate of origin
  static const double _ORIGINZ; ///< Z coordinate of origin
  static const int _NUMLOCS; ///< Number of points
  static const double _XYZECEF[]; ///< Coordinate of points in ECEF
  static const double _XYZLOCAL[]; ///< Coordinate of points in local system
  
}; // class TestCSGeoLocalCart

#endif // spatialdata_geocoords_testcsgeolocalcart_hh


// End of file 
