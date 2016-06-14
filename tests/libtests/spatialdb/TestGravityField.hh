// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestGravityField.hh
 *
 * @brief C++ TestGravityField object
 *
 * C++ unit testing for GravityField.
 */

#if !defined(spatialdata_spatialdb_testgravityfield_hh)
#define spatialdata_spatialdb_testgravityfield_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestGravityField;
    class GravityField; // USES GravityField
  } // spatialdb
} // spatialdata

/// C++ unit testing for GravityField
class spatialdata::spatialdb::TestGravityField : public CppUnit::TestFixture
{ // class TestGravityField

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGravityField );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testGravityDir );
  CPPUNIT_TEST( testAcceleration );
  CPPUNIT_TEST( testQueryVals );
  CPPUNIT_TEST( testQueryCart2 );
  CPPUNIT_TEST( testQueryCart3 );
  CPPUNIT_TEST( testQueryGeographic );
  CPPUNIT_TEST( testQueryGeoProj );
  CPPUNIT_TEST( testQueryGeocentric );
  CPPUNIT_TEST( testQueryGeoLocal );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test label()
  void testLabel(void);

  /// Test gravityDir()
  void testGravityDir(void);

  /// Test acceleration()
  void testAcceleration(void);

  /// Test queryVals()
  void testQueryVals(void);

  /// Test query() with 2-D Cartesian coordinates.
  void testQueryCart2(void);

  /// Test query() with 3-D Cartesian coordinates.
  void testQueryCart3(void);

  /// Test query() with geographic coordinates.
  void testQueryGeographic(void);

  /// Test query() with projected geographic coordinates.
  void testQueryGeoProj(void);

  /// Test query() with geocentric coordinates.
  void testQueryGeocentric(void);

  /// Test query() with geocentric coordinates and local origin.
  void testQueryGeoLocal(void);

}; // class TestGravityField

#endif // spatialdata_spatialdb_testgravityfield_hh


// End of file 
