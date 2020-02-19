// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestSimpleDBQuery.hh
 *
 * @brief C++ TestSimpleDBQuery object
 *
 * C++ unit testing for SimpleDBQuery.
 */

#if !defined(spatialdata_spatialdb_testsimpledbquery_hh)
#define spatialdata_spatialdb_testsimpledbquery_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDBQuery;
    class SimpleDB; // USES SimpleDB
    class SimpleDBQueryData; // USES TestSimpleDBQueryData
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDBQuery
class spatialdata::spatialdb::TestSimpleDBQuery : public CppUnit::TestFixture
{ // class TestSimpleDBQuery

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBQuery );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testQueryType );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test queryType()
  void testQueryType(void);

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /* Test setQueryValues()
   *
   * @param data Data for database
   */
  void _testQueryVals(const SimpleDBQueryData& data);

  /** Test distSquared()
   *
   * @param data Data for database
   */
  void _testDistSquared(const SimpleDBQueryData& data);

  /** Test area().
   *
   * @param data Data for database
   */
  void _testArea(const SimpleDBQueryData& data);

  /* Test volume()
   *
   * @param data Data for database
   */
  void _testVolume(const SimpleDBQueryData& data);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Populate database with data.
   *
   * @param db Database
   * @param data Data for database
   */
  void _setupDB(SimpleDB* const db,
		const SimpleDBQueryData& data);

}; // class TestSimpleDBQuery

#endif // spatialdata_spatialdb_testsimpledbquery_hh


// End of file 
