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

/** @file tests/libtests/TestProjector.h
 *
 * @brief C++ TestProjector object
 *
 * C++ unit testing for TestProjector.
 */

#if !defined(spatialdata_testprojector_h)
#define spatialdata_testprojector_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  class TestProjector;
  class Projector; // USES Projector
}; // spatialdata

/// C++ unit testing for Projector
class spatialdata::TestProjector : public CppUnit::TestFixture
{ // class TestProjector

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestProjector );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testProjection );
  CPPUNIT_TEST( testEllipsoid );
  CPPUNIT_TEST( testDatum );
  CPPUNIT_TEST( testUnits );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testProject );
  CPPUNIT_TEST( testInvproject );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test projection()
  void testProjection(void);

  /// Test ellipsoid()
  void testEllipsoid(void);

  /// Test datum()
  void testDatum(void);

  /// Test units()
  void testUnits(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test project()
  void testProject(void);

  /// Test invproject()
  void testInvproject(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _XY[]; ///< Array of projected locations
  static const double _LONLAT[]; ///< Array of geographic locations
  static const int _NUMLOCS; ///< Number of locations

}; // class TestProjector

#endif // spatialdata_testprojector

// version
// $Id: TestProjector.h,v 1.1 2005/05/25 17:29:42 baagaard Exp $

// End of file 
