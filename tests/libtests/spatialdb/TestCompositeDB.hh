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

/** @file tests/libtests/spatialdb/TestCompositeDB.hh
 *
 * @brief C++ TestCompositeDB object
 *
 * C++ unit testing for CompositeDB.
 */

#if !defined(spatialdata_spatialdb_testcompositedb_hh)
#define spatialdata_spatialdb_testcompositedb_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestCompositeDB;
    class CompositeDB; // USES CompositeDB
  } // spatialdb
} // spatialdata

/// C++ unit testing for CompositeDB
class spatialdata::spatialdb::TestCompositeDB : public CppUnit::TestFixture
{ // class TestCompositeDB

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCompositeDB );

  CPPUNIT_TEST( testConstructorA );
  CPPUNIT_TEST( testConstructorB );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testDBA );
  CPPUNIT_TEST( testDBB );
  CPPUNIT_TEST( testQueryVals );
  CPPUNIT_TEST( testQuery );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructorA(void);

  /// Test constructor with label
  void testConstructorB(void);

  /// Test label()
  void testLabel(void);

  /// Test dbA()
  void testDBA(void);

  /// Test dbB()
  void testDBB(void);

  /// Test queryVals()
  void testQueryVals(void);

  /// Test query()
  void testQuery(void);

}; // class TestCompositeDB

#endif // spatialdata_spatialdb_testcompositedb_hh


// End of file 
