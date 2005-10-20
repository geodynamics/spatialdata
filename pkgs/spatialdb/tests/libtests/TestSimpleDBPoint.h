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

/** @file tests/libtests/TestSimpleDBPoint.h
 *
 * @brief C++ TestSimpleDBPoint object
 *
 * C++ unit testing for SimpleDB. This object tests the pointwise
 * interpolation.
 */

#if !defined(spatialdata_spatialdb_testsimpledbpoint_h)
#define spatialdata_spatialdb_testsimpledbpoint_h

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDB;
    class TestSimpleDBPoint;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDBPoint : public TestSimpleDB
{ // class TestSimpleDBPoint

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBPoint );
  CPPUNIT_TEST( testConstructorA );
  CPPUNIT_TEST( testConstructorB );
  CPPUNIT_TEST( testLabel );
  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST_SUITE_END();

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Get data for database.
   *
   * @returns Pointer to data
   */
  const double* Data(void) const;

  /** Get names of values in database.
   *
   * @returns Pointer to names
   */
  const char** Names(void) const;

  /** Get number of locations in database.
   *
   * @returns Number of locations
   */
  int NumLocs(void) const;

  /** Get number of values at each location in database.
   *
   * @returns Number of values
   */
  int NumVals(void) const;

  /** Get topology of data in database.
   *
   * @returns Topology of data
   */
  SimpleDB::TopoEnum Topology(void) const;

  /** Get number of queries.
   *
   * @returns Number of queries
   */
  int NumQueries(void) const;

  /** Get query data for nearest neighbor algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  const double* QueryNearest(void) const;

  /** Get query data for linear interpolation algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  const double* QueryLinear(void) const;

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  static const double DATA[]; ///< Data for database
  static const char* NAMES[]; ///< Names of values in database
  static const int NUMLOCS; ///< Number of locations in database
  static const int NUMVALS; ///< Number of values in database
  static const SimpleDB::TopoEnum TOPOLOGY; ///< Topology of data in database

  static const int NUMQUERIES; ///< Number of queries
  static const double QUERYNEAREST[]; ///< Data for nearest neighbor queries
  static const double QUERYLINEAR[]; ///< Data for linear interpolation queries

}; // class TestSimpleDBPoint

#include "TestSimpleDBPoint.icc" // inline methods

#endif // spatialdata_spatialdb_testsimpledbpoint_h

// version
// $Id: TestSimpleDBPoint.h,v 1.1 2005/05/25 18:43:05 baagaard Exp $

// End of file 
