// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestSimpleDBArea3D.hh
 *
 * @brief C++ TestSimpleDBArea3D object
 *
 * C++ unit testing for SimpleDB. This object tests the areal
 * interpolation.
 */

#if !defined(spatialdata_spatialdb_testsimpledbarea3d_hh)
#define spatialdata_spatialdb_testsimpledbarea3d_hh

#include "TestSimpleDB.hh" // ISA TestSimpleDB

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDBArea3D;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDBArea3D : public TestSimpleDB
{ // class TestSimpleDBArea3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBArea3D );
  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test queryNearest()
  void testQueryNearest(void);

  /// Test queryLinear()
  void testQueryLinear(void);

}; // class TestSimpleDBArea3D

#endif // spatialdata_spatialdb_testsimpledbarea3d_hh


// End of file 
