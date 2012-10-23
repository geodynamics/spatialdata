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
    class TestSimpleGridDBLine1D;
    class TestSimpleGridDBLine2D;
    class TestSimpleGridDBLine3D;
    class TestSimpleGridDBArea2D;
    class TestSimpleGridDBArea3D;
    class TestSimpleGridDBVolume3D;
  } // spatialdb
} // spatialdata

// ----------------------------------------------------------------------
/// C++ unit testing for SimpleGridDB with line data.
class spatialdata::spatialdb::TestSimpleGridDBLine1D : public TestSimpleGridDB
{ // class TestSimpleGridDBLine1D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBLine1D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST( testRead );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup data.
  void setUp();

}; // class TestSimpleGridDBLine1D


// ----------------------------------------------------------------------
/// C++ unit testing for SimpleGridDB with line data.
class spatialdata::spatialdb::TestSimpleGridDBLine2D : public TestSimpleGridDB
{ // class TestSimpleGridDBLine2D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBLine2D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST( testRead );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup data.
  void setUp();

}; // class TestSimpleGridDBLine2D


// ----------------------------------------------------------------------
/// C++ unit testing for SimpleGridDB with line data.
class spatialdata::spatialdb::TestSimpleGridDBLine3D : public TestSimpleGridDB
{ // class TestSimpleGridDBLine3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBLine3D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST( testRead );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup data.
  void setUp();

}; // class TestSimpleGridDBLine3D


// ----------------------------------------------------------------------
/// C++ unit testing for SimpleGridDB with area data.
class spatialdata::spatialdb::TestSimpleGridDBArea2D : public TestSimpleGridDB
{ // class TestSimpleGridDBArea2D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBArea2D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST( testRead );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup data.
  void setUp();

}; // class TestSimpleGridDBArea2D


// ----------------------------------------------------------------------
/// C++ unit testing for SimpleGridDB with area data.
class spatialdata::spatialdb::TestSimpleGridDBArea3D : public TestSimpleGridDB
{ // class TestSimpleGridDBArea3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBArea3D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST( testRead );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup data.
  void setUp();

}; // class TestSimpleGridDBArea3D


// ----------------------------------------------------------------------
/// C++ unit testing for SimpleGridDB with area data.
class spatialdata::spatialdb::TestSimpleGridDBVolume3D : public TestSimpleGridDB
{ // class TestSimpleGridDBVolume3D

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDBVolume3D );

  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST( testRead );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup data.
  void setUp();

}; // class TestSimpleGridDBVolume3D

#endif // spatialdata_spatialdb_testsimplegriddbcases_hh


// End of file 
