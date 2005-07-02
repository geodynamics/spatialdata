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

/** @file tests/libtests/TestGeoCoordSys.h
 *
 * @brief C++ TestGeoCoordSys object
 *
 * C++ unit testing for TestGeoCoordSys.
 */

#if !defined(spatialdata_testgeocoordsys_h)
#define spatialdata_testgeocoordsys_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  class TestGeoCoordSys;
  class GeoCoordSys; // USES GeoCoordSys
}; // spatialdata

/// C++ unit testing for GeoCoordSys
class spatialdata::TestGeoCoordSys : public CppUnit::TestFixture
{ // class TestGeoCoordSys

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoCoordSys );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testCopyConstructor );
  CPPUNIT_TEST( testAssign );
  CPPUNIT_TEST( testProjection );
  CPPUNIT_TEST( testEllipsoid );
  CPPUNIT_TEST( testDatumHoriz );
  CPPUNIT_TEST( testDatumVert );
  CPPUNIT_TEST( testUnits );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testCoordSys );
  CPPUNIT_TEST( testEquals );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test copy constructor
  void testCopyConstructor(void);

  /// Test operator=
  void testAssign(void);

  /// Test projection()
  void testProjection(void);

  /// Test ellipsoid()
  void testEllipsoid(void);

  /// Test datumHoriz()
  void testDatumHoriz(void);

  /// Test datumVert()
  void testDatumVert(void);

  /// Test units()
  void testUnits(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test coordsys()
  void testCoordSys(void);

  /// Test operator==
  void testEquals(void);

}; // class TestGeoCoordSys

#endif // spatialdata_testgeocoordsys

// version
// $Id: TestGeoCoordSys.h,v 1.2 2005/07/02 00:21:13 baagaard Exp $

// End of file 
