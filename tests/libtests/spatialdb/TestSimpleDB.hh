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

/** @file tests/libtests/spatialdb/TestSimpleDB.hh
 *
 * @brief C++ TestSimpleDB object
 *
 * C++ unit testing for SimpleDB. This object is an abstract base
 * class with children classes specific to the type of data in the database.
 */

#if !defined(spatialdata_spatialdb_testsimpledb_hh)
#define spatialdata_spatialdb_testsimpledb_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDB;
    class SimpleDB; // USES SimpleDB
    class SimpleDBTestData; // USES SimpleDBTestData
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDB : public CppUnit::TestFixture
{ // class TestSimpleDB

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDB );
  CPPUNIT_TEST( testConstructorA );
  CPPUNIT_TEST( testConstructorB );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructorA(void);

  /// Test constructor with label
  void testConstructorB(void);

  /// Test label()
  void testLabel(void);

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Test query() using nearest neighbor
   *
   * @param data Data for database
   */
  void _testQueryNearest(const SimpleDBTestData& data);

  /** Test query() using linear interpolation
   *
   * @param data Data for database
   */
  void _testQueryLinear(const SimpleDBTestData& data);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Populate database with data.
   *
   * @param db Database
   * @param data Data for database
   */
  void _setupDB(SimpleDB* const db,
		const SimpleDBTestData& data);

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
  void _checkQuery(SimpleDB& db,
		   char** const names,
		   const double* queryData,
		   const int* flagsE,
		   const int numQueries,
		   const int spaceDim,
		   const int numVals);

}; // class TestSimpleDB

#endif // spatialdata_spatialdb_testsimpledb_hh


// End of file 
