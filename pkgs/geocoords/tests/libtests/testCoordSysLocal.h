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

/** @file tests/libtests/TestCoordSysLocal.h
 *
 * @brief C++ TestCoordSysLocal object
 *
 * C++ unit testing for CoordSysLocal.
 */

#if !defined(spatialdata_geocoords_testcoordsyslocal_h)
#define spatialdata_geocoords_testcoordsyslocal_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCoordSysLocal;
  } // geocoords
} // spatialdata

/// C++ unit testing for CoordSysLocal
class spatialdata::geocoords::TestCoordSysLocal : public CppUnit::TestFixture
{ // class TestCoordSysLocal

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCoordSysLocal );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testLocalOrigin );
  CPPUNIT_TEST( testXYZToMeters );
  CPPUNIT_TEST( testToProjForm );
  CPPUNIT_TEST( testFromProjForm );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test localOrigin()
  void testLocalOrigin(void);

  /// Test xyzToMeters()
  void testXYZToMeters(void);

  /// Test toProjForm()
  void testToProjForm(void);

  /// Test fromProjForm()
  void testFromProjForm(void);

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
  
}; // class TestCoordSysLocal

#endif // spatialdata_geocoords_testcoordsyslocal

// version
// $Id$

// End of file 
