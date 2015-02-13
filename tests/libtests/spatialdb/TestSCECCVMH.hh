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

/** @file tests/libtests/spatialdb/TestSCECCVMH.hh
 *
 * @brief C++ TestSCECCVMH object
 *
 * C++ unit testing for SCECCVMH.
 */

#if !defined(spatialdata_spatialdb_testsceccvmh_hh)
#define spatialdata_spatialdb_testsceccvmh_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSCECCVMH;
    class SCECCVMH; // USES SCECCVMH
  } // spatialdb
} // spatialdata

/// C++ unit testing for SCECCVMH
class spatialdata::spatialdb::TestSCECCVMH : public CppUnit::TestFixture
{ // class TestSCECCVMH

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSCECCVMH );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testDataDir );
  CPPUNIT_TEST( testSquashed );
  CPPUNIT_TEST( testQueryVals );
  CPPUNIT_TEST( testCalcDensity );
  CPPUNIT_TEST( testCalcVs );
#if defined(SCECCVMH_DATADIR)
  CPPUNIT_TEST( testQuery );
  CPPUNIT_TEST( testQuerySquashed );
#endif

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test label()
  void testLabel(void);

  /// Test dataDir()
  void testDataDir(void);

  /// Test squashed()
  void testSquashed(void);

  /// Test queryVals()
  void testQueryVals(void);

  /// Test query()
  void testQuery(void);

  /// Test querySquashed()
  void testQuerySquashed(void);

  /// Test calcDensity()
  void testCalcDensity(void);

  /// Test calcVs()
  void testCalcVs(void);

}; // class TestSCECCVMH

#endif // spatialdata_spatialdb_testsceccvmh_hh


// End of file 
