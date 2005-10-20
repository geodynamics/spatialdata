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

/** @file tests/libtests/TestCoordSysGeo.h
 *
 * @brief C++ TestCoordSysGeo object
 *
 * C++ unit testing for CoordSysGeo.
 */

#if !defined(spatialdata_geocoords_testcoordsysgeo_h)
#define spatialdata_geocoords_testcoordsysgeo_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCoordSysGeo;
  } // geocoords
} // spatialdata

/// C++ unit testing for CoordSysGeo
class spatialdata::geocoords::TestCoordSysGeo : public CppUnit::TestFixture
{ // class TestCoordSysGeo

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCoordSysGeo );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testEllipsoid );
  CPPUNIT_TEST( testDatumHoriz );
  CPPUNIT_TEST( testDatumVert );
  CPPUNIT_TEST( testGeocentric );
  CPPUNIT_TEST( testElevToMeters );
  CPPUNIT_TEST( testToProjForm );
  CPPUNIT_TEST( testFromProjForm );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test ellipsoid()
  void testEllipsoid(void);

  /// Test datumHoriz()
  void testDatumHoriz(void);

  /// Test datumVert()
  void testDatumVert(void);

  /// Test isGeocentric()
  void testGeocentric(void);

  /// Test elevToMeters()
  void testElevToMeters(void);

  /// Test toProjForm()
  void testToProjForm(void);

  /// Test fromProjForm()
  void testFromProjForm(void);

}; // class TestCoordSysGeo

#endif // spatialdata_geocoords_testcoordsysgeo

// version
// $Id$

// End of file 
