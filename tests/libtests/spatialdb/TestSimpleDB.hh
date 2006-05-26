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
 * class. The actual testing is done in objects derived from this one
 * (TestSimpleDBPoint, TestSimpleDBLine, TestSimpleDBArea,
 * TestSimpleDBVolume).
 */

#if !defined(spatialdata_spatialdb_testsimpledb_hh)
#define spatialdata_spatialdb_testsimpledb_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDB;
    class SimpleDB; // USES SimpleDB
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDB : public CppUnit::TestFixture
{ // class TestSimpleDB

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup test subject
  void setUp(void);

  /// Cleanup test subject
  void tearDown(void);

  /// Test constructor
  void testConstructorA(void);

  /// Test constructor with label
  void testConstructorB(void);

  /// Test Label()
  void testLabel(void);

  /// Test Query() using nearest neighbor
  void testQueryNearest(void);

  /// Test Query() using linear interpolation
  void testQueryLinear(void);

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Get database.
   *
   * @returns Pointer to database
   */
  SimpleDB* _database(void);

  /** Get data for database.
   *
   * @returns Pointer to data
   */
  virtual const double* _data(void) const = 0;

  /** Get expected return values for queries.
   *
   * @returns Pointer to head of array
   */
  virtual const int* _errFlags(void) const = 0;

  /** Get names of values in database.
   *
   * @returns Pointer to names
   */
  virtual const char** _names(void) const = 0;

  /** Get units of values in database.
   *
   * @returns Pointer to units
   */
  virtual const char** _units(void) const = 0;

  /** Get number of locations in database.
   *
   * @returns Number of locations
   */
  virtual int _numLocs(void) const = 0;

  /** Get number of values at each location in database.
   *
   * @returns Number of values
   */
  virtual int _numVals(void) const = 0;

  /** Get topology of data in database.
   *
   * @returns Topology of data
   */
  virtual SimpleDB::TopoEnum _topology(void) const = 0;

  /** Get number of queries.
   *
   * @returns Number of queries
   */
  virtual int _numQueries(void) const = 0;

  /** Get query data for nearest neighbor algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  virtual const double* _queryNearest(void) const = 0;

  /** Get query data for linear interpolation algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  virtual const double* _queryLinear(void) const = 0;

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Check query values.
   *
   * Do query and check values returned.
   * 
   * @param queryData Query locations and expected values
   * @param queryErrFlags Array of exepcted return values
   */
  void _checkQuery(const double* queryData,
		   const int* queryErrFlags) const;

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  SimpleDB* _pDB; ///< Test subject

}; // class TestSimpleDB

#include "TestSimpleDB.icc" // inline methods

#endif // spatialdata_spatialdb_testsimpledb_hh

// version
// $Id$

// End of file 
