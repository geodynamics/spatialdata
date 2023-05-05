// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
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

#include "spatialdata/spatialdb/spatialdbfwd.hh" // USES SimpleDB, SimpleDBQuery

/// Namespace for spatial package
namespace spatialdata {
    namespace spatialdb {
        class TestSimpleDBQuery;
        class TestSimpleDBQuery_Data;
    } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleDBQuery
class spatialdata::spatialdb::TestSimpleDBQuery : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSimpleDBQuery);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testQueryVals);
    CPPUNIT_TEST(testDistSquared);
    CPPUNIT_TEST(testArea);
    CPPUNIT_TEST(testVolume);

    CPPUNIT_TEST_SUITE_END_ABSTRACT();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Setup query.
    void setUp(void);

    /// Destroy query.
    void tearDown(void);

    /// Test constructor
    void testConstructor(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test setQueryValues()
    void testQueryVals(void);

    /// Test distSquared()
    void testDistSquared(void);

    /// Test area().
    void testArea(void);

    /// Test volume().
    void testVolume(void);

    // PROTECTED MEMBERS ////////////////////////////////////////////////////
protected:

    /// Populdate database with values.
    void _initializeDB(void);

    // PROTECTED MEMBERS ////////////////////////////////////////////////////
protected:

    SimpleDB* _db; ///< Database for test subject.
    SimpleDBQuery* _query; ///< Test subject.
    TestSimpleDBQuery_Data* _data; ///< Test data.

}; // class TestSimpleDBQuery

class spatialdata::spatialdb::TestSimpleDBQuery_Data {
    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Constructor
    TestSimpleDBQuery_Data(void);

    /// Destructor
    ~TestSimpleDBQuery_Data(void);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    /// @name Database information
    //@{
    size_t numLocs; ///< Number of locations in database.
    size_t spaceDim; ///< Spatial dimension for coordinates of locations.
    size_t numValues; ///< Number of values per location in database.
    size_t dataDim; ///< Spatial dimension of data in database.
    const double* dbCoordinates; ///< Database locations.
    const double* dbValues; ///< Database values at locations.
    const char** names; ///< Names of values in database.
    const char** units; ///< Units of values in database.
    //@}

    /// @name Query information
    //@{
    size_t numPoints; ///< Number of points for locations
    const double* coordinates; ///< Coordinates of query locations
    double dist2; ///< Expected value for distance squared
    double area; ///< Expected value for area
    const double* areaDir; ///< Expected value for area direction
    double volume; ///< Expected value for volume
    //@}

}; // TestSimpleDBQuery_Data

#endif // spatialdata_spatialdb_testsimpledbquery_hh

// End of file
