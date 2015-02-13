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

/** @file tests/libtests/spatialdb/TestSimpleDBData.hh
 *
 * @brief C++ TestSimpleDBData object
 *
 * C++ unit testing for SimpleDBData.
 */

#if !defined(spatialdata_spatialdb_testsimpledbdata_hh)
#define spatialdata_spatialdb_testsimpledbdata_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDBData;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDBData
class spatialdata::spatialdb::TestSimpleDBData : public CppUnit::TestFixture
{ // class TestSimpleDBData

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBData );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testAllocate );
  CPPUNIT_TEST( testData );
  CPPUNIT_TEST( testCoordinates );
  CPPUNIT_TEST( testNames );
  CPPUNIT_TEST( testUnits );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor.
  void testConstructor(void);

  /// Test allocate(), numLocs(), numValues(), spaceDim().
  void testAllocate(void);

  /// Test data() and dataDim().
  void testData(void);

  /// Test coordinates()
  void testCoordinates(void);

  /// Test names()
  void testNames(void);

  /// Test units()
  void testUnits(void);

}; // class TestSimpleDBData

#endif // spatialdata_spatialdb_testsimpledbdata_hh


// End of file 
