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

/** @file tests/libtests/TestCSGeoProj.h
 *
 * @brief C++ TestCSGeoProj object
 *
 * C++ unit testing for CSGeoProj.
 */

#if !defined(spatialdata_geocoords_testcsgeolocalcart_h)
#define spatialdata_geocoords_testcsgeolocalcart_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCSGeoProj;
  } // geocoords
} // spatialdata

/// C++ unit testing for CSGeoProj
class spatialdata::geocoords::TestCSGeoProj : public CppUnit::TestFixture
{ // class TestCSGeoProj

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCSGeoProj );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testToProjForm );
  CPPUNIT_TEST( testFromProjForm );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test toProjForm()
  void testToProjForm(void);

  /// Test fromProjForm()
  void testFromProjForm(void);

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
public :

  static const char* _ELLIPSOID; ///< Name of reference ellipsoid
  static const char* _DATUMHORIZ; ///< Name of horizontal datum
  static const char* _DATUMVERT; ///< Name of vertical datum
  static const double _FALSEEASTING; ///< Longitude of origin
  static const double _FALSENORTHING; ///< Latitude of origin
  static const double _SCALEFACTOR; ///< Scale factor (central meridian)
  static const char* _PROJECTION; ///< Name of projection
  static const char* _UNITS; ///< Units in projection

  static const int _NUMLOCS; ///< Number of points
  static const double _XYZ[]; ///< Coordinate of points in projected cs
  static const double _LONLATNAD27ELEV[]; ///< Geographic coordinates of points
  
}; // class TestCSGeoProj

#endif // spatialdata_geocoords_testcsgeolocalcart_h

// version
// $Id$

// End of file 
