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

/** @file tests/libtests/spatialdb/TestSpatialDB.hh
 *
 * @brief C++ TestSpatialDB object
 *
 * C++ unit testing for SpatialDB.
 */

#if !defined(spatialdata_spatialdb_testspatialdb_hh)
#define spatialdata_spatialdb_testspatialdb_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSpatialDB;
    class SpatialDB; // USES SpatialDB
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleIO
class spatialdata::spatialdb::TestSpatialDB : public CppUnit::TestFixture
{ // class TestSpatialDB

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSpatialDB );
  CPPUNIT_TEST( testDB );
  CPPUNIT_TEST( testDBmulti );
  CPPUNIT_TEST( testDB_c );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup test subject
  void setUp(void);

  /// Cleanup test subject
  void tearDown(void);

  /// Test SpatialDB
  void testDB(void);

  /// Test SpatialDB queries w/multiple points.
  void testDBmulti(void);

  /// Test SpatialDB w/C query
  void testDB_c(void);

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  SpatialDB* _pDB; ///< Test subject

}; // class TestSpatialDB

#endif // spatialdata_spatialdb_testspatialdb_hh


// End of file 
