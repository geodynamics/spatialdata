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

/** @file tests/libtests/geocoords/TestCSGeoProj.hh
 *
 * @brief C++ TestCSGeoProj object
 *
 * C++ unit testing for CSGeoProj.
 */

#if !defined(spatialdata_geocoords_testcsgeolocalcart_hh)
#define spatialdata_geocoords_testcsgeolocalcart_hh

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
  CPPUNIT_TEST( testPickle );
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

  /// Test pickle() and unpickle()
  void testPickle(void);

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
public :

  static const char* _ELLIPSOID; ///< Name of reference ellipsoid
  static const char* _DATUMHORIZ; ///< Name of horizontal datum
  static const char* _DATUMVERT; ///< Name of vertical datum
  static const char* _PROJECTION; ///< Name of projection
  static const char* _UNITS; ///< Units in projection
  static const char* _PROJOPTIONS; ///< Options for projection

  static const int _NUMLOCS; ///< Number of points
  static const double _XYZ[]; ///< Coordinate of points in projected cs
  static const double _LONLATNAD27ELEV[]; ///< Geographic coordinates of points
  
}; // class TestCSGeoProj

#endif // spatialdata_geocoords_testcsgeolocalcart_hh


// End of file 
