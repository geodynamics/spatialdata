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

/** @file tests/libtests/spatialdb/TestUniformDB.hh
 *
 * @brief C++ TestUniformDB object
 *
 * C++ unit testing for UniformDB.
 */

#if !defined(spatialdata_spatialdb_testuniformdb_hh)
#define spatialdata_spatialdb_testuniformdb_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestUniformDB;
    class UniformDB; // USES UniformDB
  } // spatialdb
} // spatialdata

/// C++ unit testing for UniformDB
class spatialdata::spatialdb::TestUniformDB : public CppUnit::TestFixture
{ // class TestUniformDB

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestUniformDB );

  CPPUNIT_TEST( testConstructorA );
  CPPUNIT_TEST( testConstructorB );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testSetData );
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

  /// Test setData()
  void testSetData(void);

  /// Test queryVals()
  void testQueryVals(void);

  /// Test query()
  void testQuery(void);

}; // class TestUniformDB

#endif // spatialdata_spatialdb_testuniformdb_hh


// End of file 
