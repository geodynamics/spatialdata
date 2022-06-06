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

/** @file tests/libtests/geocoords/TestConverter.hh
 *
 * @brief C++ TestConverter object
 *
 * C++ unit testing for Converter.
 */

#if !defined(spatialdata_testconverter_hh)
#define spatialdata_testconverter_hh

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/geocoords/geocoordsfwd.hh" // HOLDSA CoordSys

namespace spatialdata {
    namespace geocoords {
        class TestConverter;
        class TestConverter_Data;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestConverter : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestConverter);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testConvert);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Setup testing data.
    void setUp(void);

    /// Deallocate testing data.
    void tearDown(void);

    /// Test constructor.
    void testConstructor(void);

    /// Test convert().
    void testConvert(void);

    // PROTECTED MEMBERS ///////////////////////////////////////////////////////
protected:

    TestConverter_Data* _data; ///< Data for testing.

}; // class TestConverter

class spatialdata::geocoords::TestConverter_Data {
    // PUBLIC METHODS //////////////////////////////////////////////////////////
public:

    /// Constructor
    TestConverter_Data(void);

    /// Destructor
    ~TestConverter_Data(void);

    // PUBLIC MEMBERS //////////////////////////////////////////////////////////
public:

    size_t numPoints; ///< Number of points.
    size_t spaceDim; ///< Dimension of coordinate system.
    const double* coordsSrc; ///< Coordinates of points in source coordinate system.
    const double* coordsDest; ///< Coordinates of points in destination coordinate system.
    const CoordSys* csSrc; ///< Source coordinate system.
    const CoordSys* csDest; ///< Destination coordinate system.

}; // TestConverter_Data

#endif // spatialdata_geocoords_testconverter_hh

// End of file
