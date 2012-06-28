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

/** @file tests/libtests/spatialdb/TestGeoProjGridDB.hh
 *
 * @brief C++ TestGeoProjGridDB object
 *
 * C++ unit testing for GeoProjGridDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testgeoprojgriddb_hh)
#define spatialdata_spatialdb_testgeoprojgriddb_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/spatialdb/spatialdbfwd.hh"

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestGeoProjGridDB;
    class GeoProjGridDBTestData; // USES GeoProjGridDBTestData
  } // spatialdb
} // spatialdata

/// C++ unit testing for GeoProjGridDB
class spatialdata::spatialdb::TestGeoProjGridDB : public CppUnit::TestFixture
{ // class TestGeoProjGridDB

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoProjGridDB );

  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testFilename );
  CPPUNIT_TEST( testQueryType );
  CPPUNIT_TEST( testSearch );
  CPPUNIT_TEST( testDataIndex );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

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

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Test query() using nearest neighbor
   *
   * @param data Data for database
   */
  void _testQueryNearest(const GeoProjGridDBTestData& data);

  /** Test query() using linear interpolation
   *
   * @param data Data for database
   */
  void _testQueryLinear(const GeoProjGridDBTestData& data);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Populate database with data.
   *
   * @param db Database
   * @param data Data for database
   */
  void _setupDB(GeoProjGridDB* const db,
		const GeoProjGridDBTestData& data);

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
  void _checkQuery(GeoProjGridDB& db,
		   char** const names,
		   const double* queryData,
		   const int* flagsE,
		   const int numQueries,
		   const int spaceDim,
		   const int numVals);

}; // class TestGeoProjGridDB

#endif // spatialdata_spatialdb_testgeoprojgriddb_hh


// End of file 
