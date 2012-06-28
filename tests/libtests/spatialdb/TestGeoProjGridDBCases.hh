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

/** @file tests/libtests/spatialdb/TestGeoProjGridDBCases.hh
 *
 * @brief C++ TestGeoProjGridDBVolume3D object
 *
 * C++ unit testing for GeoProjGridDB. 
 */

#if !defined(spatialdata_spatialdb_testgeoprojgriddbcases_hh)
#define spatialdata_spatialdb_testgeoprojgriddbcases_hh

#include "TestGeoProjGridDB.hh" // ISA TestGeoProjGridDB

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestGeoProjGridDBVolume3D;
  } // spatialdb
} // spatialdata

/// C++ unit testing for GeoProjGridDB with volume data.
class spatialdata::spatialdb::TestGeoProjGridDBVolume3D : public TestGeoProjGridDB
{ // class TestGeoProjGridDBVolume3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoProjGridDBVolume3D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test queryNearest()
  void testQueryNearest(void);

  /// Test queryLinear()
  void testQueryLinear(void);

}; // class TestGeoProjGridDBVolume3D

#endif // spatialdata_spatialdb_testgeoprojgriddbvolume3d_hh


// End of file 
