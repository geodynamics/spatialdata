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

/** @file tests/libtests/TestSimpleDB.h
 *
 * @brief C++ TestSimpleDB object
 *
 * C++ unit testing for SimpleDB. This object is an abstract base
 * class. The actual testing is done in objects derived from this one
 * (TestSimpleDBPoint, TestSimpleDBLine, TestSimpleDBArea,
 * TestSimpleDBVolume).
 */

#if !defined(_spatial_testsimpledb_h)
#define _spatial_testsimpledb_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatial {
  class TestSimpleDB;
  class SimpleDB; // USES SimpleDB
}; // spatial

/// C++ unit testing for SimpleDB
class spatial::TestSimpleDB : public CppUnit::TestFixture
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
  SimpleDB* Database(void);

  /** Get data for database.
   *
   * @returns Pointer to data
   */
  virtual const double* Data(void) const = 0;

  /** Get names of values in database.
   *
   * @returns Pointer to names
   */
  virtual const char** Names(void) const = 0;

  /** Get number of locations in database.
   *
   * @returns Number of locations
   */
  virtual int NumLocs(void) const = 0;

  /** Get number of values at each location in database.
   *
   * @returns Number of values
   */
  virtual int NumVals(void) const = 0;

  /** Get topology of data in database.
   *
   * @returns Topology of data
   */
  virtual SimpleDB::TopoEnum Topology(void) const = 0;

  /** Get number of queries.
   *
   * @returns Number of queries
   */
  virtual int NumQueries(void) const = 0;

  /** Get query data for nearest neighbor algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  virtual const double* QueryNearest(void) const = 0;

  /** Get query data for linear interpolation algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  virtual const double* QueryLinear(void) const = 0;

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Check query values.
   *
   * Do query and check values returned.
   * 
   * @param queryData Query locations and expected values
   */
  void CheckQuery(const double* queryData) const;

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  SimpleDB* mpDB; ///< Test subject

}; // class TestSimpleDB

#include "TestSimpleDB.icc" // inline methods

#endif // _spatial_testsimpledb

// version
// $Id: TestSimpleDB.h,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
