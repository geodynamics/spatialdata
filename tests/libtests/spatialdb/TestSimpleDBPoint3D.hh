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

/** @file tests/libtests/spatialdb/TestSimpleDBPoint3D.hh
 *
 * @brief C++ TestSimpleDBPoint3D object
 *
 * C++ unit testing for SimpleDB. This object tests the point
 * interpolation.
 */

#if !defined(spatialdata_spatialdb_testsimpledbpoint3d_hh)
#define spatialdata_spatialdb_testsimpledbpoint3d_hh

#include "TestSimpleDB.hh" // ISA TestSimpleDB

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDBPoint3D;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDBPoint3D : public TestSimpleDB
{ // class TestSimpleDBPoint3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBPoint3D );
  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test queryNearest()
  void testQueryNearest(void);

  /// Test queryLinear()
  void testQueryLinear(void);

}; // class TestSimpleDBPoint3D

#endif // spatialdata_spatialdb_testsimpledbpoint3d_hh


// End of file 
