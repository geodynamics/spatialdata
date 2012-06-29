// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestSimpleGridDBCases.hh
 *
 * @brief C++ TestSimpleGridDBVolume3D object
 *
 * C++ unit testing for SimpleGridDB. 
 */

#if !defined(spatialdata_spatialdb_testsimplegriddbcases_hh)
#define spatialdata_spatialdb_testsimplegriddbcases_hh

#include "TestSimpleGridDB.hh" // ISA TestSimpleGridDB

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleGridDBVolume3D;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleGridDB with volume data.
class spatialdata::spatialdb::TestSimpleGridDBVolume3D : public TestSimpleGridDB
{ // class TestSimpleGridDBVolume3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBVolume3D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test queryNearest()
  void testQueryNearest(void);

  /// Test queryLinear()
  void testQueryLinear(void);

}; // class TestSimpleGridDBVolume3D

#endif // spatialdata_spatialdb_testsimplegriddbvolume3d_hh


// End of file 
