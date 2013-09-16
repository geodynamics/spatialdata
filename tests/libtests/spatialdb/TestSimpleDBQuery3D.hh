// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestSimpleDBQuery3D.hh
 *
 * @brief C++ TestSimpleDBQuery3D object
 *
 * C++ unit testing for SimpleDBQuery.
 */

#if !defined(spatialdata_spatialdb_testsimpledbquery3d_hh)
#define spatialdata_spatialdb_testsimpledbquery3d_hh

#include "TestSimpleDBQuery.hh" // ISA TestSimpleDBQuery

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDBQuery3D;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDBQuery3D : public TestSimpleDBQuery
{ // class TestSimpleDBQuery3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBQuery3D );
  CPPUNIT_TEST( testQueryVals );
  CPPUNIT_TEST( testDistSquared );
  CPPUNIT_TEST( testArea );
  CPPUNIT_TEST( testVolume );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test queryVals()
  void testQueryVals(void);

  /// Test distSquared()
  void testDistSquared(void);

  /// Test area()
  void testArea(void);

  /// Test volume()
  void testVolume(void);

}; // class TestSimpleDBQuery3D

#endif // spatialdata_spatialdb_testsimpledbquery3d_hh


// End of file 
