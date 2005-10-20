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

/** @file tests/libtests/TestSpatialDB.h
 *
 * @brief C++ TestSpatialDB object
 *
 * C++ unit testing for SpatialDB.
 */

#if !defined(spatialdata_spatialdb_testspatialdb_h)
#define spatialdata_spatialdb_testspatialdb_h

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
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup test subject
  void setUp(void);

  /// Cleanup test subject
  void tearDown(void);

  /// Test SpatialDB
  void testDB(void);

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  SpatialDB* mpDB; ///< Test subject

}; // class TestSpatialDB

#endif // spatialdata_spatialdb_testspatialdb

// version
// $Id: TestSpatialDB.h,v 1.1 2005/05/25 18:43:06 baagaard Exp $

// End of file 
