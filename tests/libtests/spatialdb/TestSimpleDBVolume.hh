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

/** @file tests/libtests/spatialdb/TestSimpleDBVolume.hh
 *
 * @brief C++ TestSimpleDBVolume object
 *
 * C++ unit testing for SimpleDB. This object tests the volumetric
 * interpolation.
 */

#if !defined(spatialdata_spatialdb_testsimpledbvolume_hh)
#define spatialdata_spatialdb_testsimpledbvolume_hh

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDB;
    class TestSimpleDBVolume;
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDB
class spatialdata::spatialdb::TestSimpleDBVolume : public TestSimpleDB
{ // class TestSimpleDBVolume

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBVolume );
  CPPUNIT_TEST( testQueryNearest );
  CPPUNIT_TEST( testQueryLinear );
  CPPUNIT_TEST_SUITE_END();

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Get data for database.
   *
   * @returns Pointer to data
   */
  const double* _data(void) const;

  /** Get expected return values for queries.
   *
   * @returns Pointer to head of array
   */
  const int* _errFlags(void) const;

  /** Get names of values in database.
   *
   * @returns Pointer to names
   */
  const char** _names(void) const;

  /** Get units of values in database.
   *
   * @returns Pointer to units
   */
  const char** _units(void) const;

  /** Get number of locations in database.
   *
   * @returns Number of locations
   */
  int _numLocs(void) const;

  /** Get number of values at each location in database.
   *
   * @returns Number of values
   */
  int _numVals(void) const;

  /** Get topology of data in database.
   *
   * @returns Topology of data
   */
  SimpleDB::TopoEnum _topology(void) const;

  /** Get number of queries.
   *
   * @returns Number of queries
   */
  int _numQueries(void) const;

  /** Get query data for nearest neighbor algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  const double* _queryNearest(void) const;

  /** Get query data for linear interpolation algorithm.
   *
   * numCoords = 3
   * Coordinates for iQuery begin at iQuery*(numCoords+numVals)
   * Expected values for iQuery begin at iQuery*(numCoords+numVals)+numCoords
   *
   * @returns Pointer to data
   */
  const double* _queryLinear(void) const;

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  static const double DATA[]; ///< Data for database
  static const int ERRFLAGS[]; ///< Expected query return values
  static const char* NAMES[]; ///< Names of values in database
  static const char* UNITS[]; ///< Units of values in database
  static const int NUMLOCS; ///< Number of locations in database
  static const int NUMVALS; ///< Number of values in database
  static const SimpleDB::TopoEnum TOPOLOGY; ///< Topology of data in database

  static const int NUMQUERIES; ///< Number of queries
  static const double QUERYNEAREST[]; ///< Data for nearest neighbor queries
  static const double QUERYLINEAR[]; ///< Data for linear interpolation queries

}; // class TestSimpleDBVolume

#include "TestSimpleDBVolume.icc" // inline methods

#endif // spatialdata_spatialdb_testsimpledbvolume_hh

// version
// $Id$

// End of file 
