// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestGravityField.hh
 *
 * @brief C++ TestGravityField object
 *
 * C++ unit testing for GravityField.
 */

#if !defined(spatialdata_spatialdb_testgravityfield_hh)
#define spatialdata_spatialdb_testgravityfield_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/geocoords/geocoordsfwd.hh" // USES CoordSys

/// Namespace for spatial package
namespace spatialdata {
    namespace spatialdb {
        class TestGravityField;
        class TestGravityField_Data;
    } // spatialdb
} // spatialdata

/// C++ unit testing for GravityField
class spatialdata::spatialdb::TestGravityField : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestGravityField);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testGetNamesDBValues);
    CPPUNIT_TEST(testQueryVals);
    CPPUNIT_TEST(testQuery);

    CPPUNIT_TEST_SUITE_END_ABSTRACT();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Setup test data.
    void setUp(void);

    /// Destroy test data.
    void tearDown(void);

    /// Test constructor
    void testConstructor(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test getNamesDBValues().
    void testGetNamesDBValues(void);

    /// Test setQueryValues()
    void testQueryVals(void);

    /// Test query().
    void testQuery(void);

    // PROTECTED METHODS /////////////////////////////////////////////////////
protected:

    TestGravityField_Data* _data; ///< Test data.

}; // class TestGravityField

class spatialdata::spatialdb::TestGravityField_Data {
    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /// Constructor
    TestGravityField_Data(void);

    /// Destructor
    ~TestGravityField_Data(void);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    spatialdata::geocoords::CoordSys* cs; ///< Coordinate system.
    double gravityAcc; ///< Gravitational acceleration.
    const double* gravityDir; ///< Direction of gravitational acceleration.

    size_t querySize; ///< Number of values in query (1, 2, or 3).
    const char* queryNames[3]; ///< Names of values in query.

    size_t numPoints; ///< Number of query points.
    const double* coordinates; ///< Coordinates of query point.
    const double* gravity; ///< Expected values for query.

}; // TestGravityField_Data

#endif // spatialdata_spatialdb_testgravityfield_hh

// End of file
