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

#if !defined(_spatial_testspatialdb_h)
#define _spatial_testspatialdb_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatial {
  class TestSpatialDB;
  class SpatialDB; // USES SpatialDB
}; // spatial

/// C++ unit testing for SimpleIO
class spatial::TestSpatialDB : public CppUnit::TestFixture
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

#endif // _spatial_testspatialdb

// version
// $Id: TestSpatialDB.h,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
