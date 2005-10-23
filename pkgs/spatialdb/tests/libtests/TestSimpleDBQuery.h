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

/** @file tests/libtests/TestSimpleDBQuery.h
 *
 * @brief C++ TestSimpleDBQuery object
 *
 * C++ unit testing for SimpleDBQuery.
 */

#if !defined(spatialdata_spatialdb_testsimpledbquery_h)
#define spatialdata_spatialdb_testsimpledbquery_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleDBQuery;
    class SimpleDB; // USES SimpleDB
    class SimpleDBQuery; // USES SimpleDBQuery
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDBQuery
class spatialdata::spatialdb::TestSimpleDBQuery : public CppUnit::TestFixture
{ // class TestSimpleDBQuery

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleDBQuery );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testDistSquared );
  CPPUNIT_TEST( testArea );
  CPPUNIT_TEST( testVolume );
  CPPUNIT_TEST( testQueryType );
  CPPUNIT_TEST( testQueryVals );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup test subject
  void setUp(void);

  /// Cleanup test subject
  void tearDown(void);

  /// Test constructor
  void testConstructor(void);

  /// Test DistSquared()
  void testDistSquared(void);

  /// Test Area()
  void testArea(void);

  /// Test Volume()
  void testVolume(void);

  /// Test QueryType()
  void testQueryType(void);

  /// Test QueryVals()
  void testQueryVals(void);

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  SimpleDB* _pDB; ///< Database for test subject
  SimpleDBQuery* _pQuery; ///< Test subject

  static const double DATA[]; ///< Data for database
  static const char* NAMES[]; ///< Names of values in database
  static const int NUMLOCS; ///< Number of locations in database
  static const int NUMVALS; ///< Number of values in database
  static const SimpleDB::TopoEnum TOPOLOGY; ///< Topology of data in database

  static const double COORDS[]; ///< Coordinates for points
  static const double AREADIR[]; ///< Direction associated with area
  static const int NUMPTS; ///< Number of points
  static const double DIST2; ///< Square of distance b/t points 0 and 1
  static const double AREA; ///< Area of triangle formed by pts 0, 1, 2
  static const double VOLUME; ///< Volume of tetrahedron formed by pts 0,1,2,3

}; // class TestSimpleDBQuery

#endif // spatialdata_spatialdb_testsimpledbquery_h

// version
// $Id: TestSimpleDBQuery.h,v 1.1 2005/05/25 18:43:05 baagaard Exp $

// End of file 
