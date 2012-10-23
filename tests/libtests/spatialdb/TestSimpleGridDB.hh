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

/** @file tests/libtests/spatialdb/TestSimpleGridDB.hh
 *
 * @brief C++ TestSimpleGridDB object
 *
 * C++ unit testing for SimpleGridDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testsimplegriddb_hh)
#define spatialdata_spatialdb_testsimplegriddb_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/spatialdbfwd.hh"

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleGridDB;
    class SimpleGridDBTestData; // USES SimpleGridDBTestData
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleGridDB
class spatialdata::spatialdb::TestSimpleGridDB : public CppUnit::TestFixture
{ // class TestSimpleGridDB

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleGridDB );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testFilename );
  CPPUNIT_TEST( testQueryType );
  CPPUNIT_TEST( testSearch );
  CPPUNIT_TEST( testDataIndex );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup testing data.
  void setUp(void);

  /// Tear down testing data.
  void tearDown(void);

  /// Test constructor
  void testConstructor(void);

  /// Test label()
  void testLabel(void);

  /// Test filename()
  void testFilename(void);

  /// Test queryType()
  void testQueryType(void);

  /// Test _search()
  void testSearch(void);

  /// Test _dataIndex()
  void testDataIndex(void);

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  // Tests in derived classes.

  /// Test query() using nearest neighbor.
  void testQueryNearest(void);

  /// Test query() using linear interpolation.
  void testQueryLinear(void);

  /// Test read().
  void testRead(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Populate database with data.
   *
   * @param db Database
   * @param data Data for database
   */
  void _setupDB(SimpleGridDB* const db);

  /** Test query method by doing query and checking values returned.
   * 
   * @param db Database to query
   * @param names Names of values in database
   * @param queryData Query locations and expected values
   * @param flagsE Array of expected return values
   * @param numQueries Number of queries
   * @param spaceDim Number of coordinates per location
   * @param numVals Number of values in database
   */
  void _checkQuery(SimpleGridDB& db,
		   char** const names,
		   const double* queryData,
		   const int* flagsE,
		   const int numQueries,
		   const int spaceDim,
		   const int numVals);

protected :
  // PROTECTED MEMBERS //////////////////////////////////////////////////

  SimpleGridDBTestData* _data; ///< Test data.

}; // class TestSimpleGridDB

#endif // spatialdata_spatialdb_testsimplegriddb_hh


// End of file 
