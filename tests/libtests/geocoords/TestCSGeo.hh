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

/** @file tests/libtests/geocoords/TestCSGeo.hh
 *
 * @brief C++ TestCSGeo object
 *
 * C++ unit testing for CSGeo.
 */

#if !defined(spatialdata_geocoords_testcsgeo_hh)
#define spatialdata_geocoords_testcsgeo_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCSGeo;
  } // geocoords
} // spatialdata

/// C++ unit testing for CSGeo
class spatialdata::geocoords::TestCSGeo : public CppUnit::TestFixture
{ // class TestCSGeo

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCSGeo );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testEllipsoid );
  CPPUNIT_TEST( testDatumHoriz );
  CPPUNIT_TEST( testDatumVert );
  CPPUNIT_TEST( testGeocentric );
  CPPUNIT_TEST( testToMeters );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testToProjForm );
  CPPUNIT_TEST( testFromProjForm );
  CPPUNIT_TEST( testPickle );
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

  /// Test toMeters()
  void testToMeters(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test toProjForm()
  void testToProjForm(void);

  /// Test fromProjForm()
  void testFromProjForm(void);

  /// Test pickle() & unpickle()
  void testPickle(void);

}; // class TestCSGeo

#endif // spatialdata_geocoords_testcsgeo_hh

// version
// $Id$

// End of file 
