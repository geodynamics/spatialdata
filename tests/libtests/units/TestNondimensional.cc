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

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

#include <valarray> // USES std::valarray

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace units {
        class TestNondimensional;
    } // units
} // spatialdata

class spatialdata::units::TestNondimensional : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestNondimensional);

    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testComputeDensityScale);
    CPPUNIT_TEST(testComputePressureScale);
    CPPUNIT_TEST(testNondimensionalize);
    CPPUNIT_TEST(testNondimensionalizeArray);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test constructors.
    void testConstructors(void);

    /// Test accessors.
    void testAccessors(void);

    /// Test computeDensityScale.
    void testComputeDensityScale(void);

    /// Test computePressureScale.
    void testComputePressureScale(void);

    /// Test nondimensionalize() and dimensionalize().
    void testNondimensionalize(void);

    /// Test nondimensionalie() and dimensionalize() with arrays.
    void testNondimensionalizeArray(void);

}; // class TestNondimensional

CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::units::TestNondimensional);

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestNondimensional::testConstructors(void) {
    const double defaultLength(1.0);
    const double defaultPressure(1.0);
    const double defaultTime(1.0);
    const double defaultDensity(1.0);
    const double defaultTemperature(1.0);

    Nondimensional dim;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default length scale", defaultLength, dim._length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default pressure scale", defaultPressure, dim._pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default time scale", defaultTime, dim._time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default density scale", defaultDensity, dim._density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default temperature scale", defaultTemperature, dim._temperature);

    dim._length = 2.0;
    dim._pressure = 3.0;
    dim._time = 4.0;
    dim._density = 5.0;
    dim._temperature = 6.0;
    Nondimensional dimCopy(dim);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy length scale", dim._length, dimCopy._length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy pressure scale", dim._pressure, dimCopy._pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy time scale", dim._time, dimCopy._time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy density scale", dim._density, dimCopy._density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy temperature scale", dim._temperature, dimCopy._temperature);

    Nondimensional dimAssign;
    dimAssign = dim;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy length scale", dim._length, dimAssign._length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy pressure scale", dim._pressure, dimAssign._pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy time scale", dim._time, dimAssign._time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy density scale", dim._density, dimAssign._density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking copy temperature scale", dim._temperature, dimAssign._temperature);
} // testConstructors


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::units::TestNondimensional::testAccessors(void) {
    const double length(4.0);
    const double pressure(5.0);
    const double time(6.0);
    const double density(7.0);
    const double temperature(8.0);

    Nondimensional dim;

    // Length scale
    dim.lengthScale(length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying length scale was set", length, dim.lengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying pressure scale is unchanged", 1.0, dim.pressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying time scale is unchanged", 1.0, dim.timeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying density scale is unchanged", 1.0, dim.densityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying temperature scale is unchanged", 1.0, dim.temperatureScale());

    // Pressure scale
    dim.pressureScale(pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying length scale is unchanged", length, dim.lengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying pressure scale was set", pressure, dim.pressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying time scale is unchanged", 1.0, dim.timeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying density scale is unchanged", 1.0, dim.densityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying temperature scale is unchanged", 1.0, dim.temperatureScale());

    // Time scale
    dim.timeScale(time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying length scale is unchanged", length, dim.lengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying pressure scale is unchanged", pressure, dim.pressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying time scale was set", time, dim.timeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying density scale is unchanged", 1.0, dim.densityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying temperature scale is unchanged", 1.0, dim.temperatureScale());

    // Density scale
    dim.densityScale(density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying length scale is unchanged", length, dim.lengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying pressure scale is unchanged", pressure, dim.pressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying time scale is unchanged", time, dim.timeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying density scale was set", density, dim.densityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying temperature scale is unchanged", 1.0, dim.temperatureScale());

    // Temperature scale
    dim.temperatureScale(temperature);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying length scale is unchanged", length, dim.lengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying pressure scale is unchanged", pressure, dim.pressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying time scale is unchanged", time, dim.timeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying density scale is unchanged", density, dim.densityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying temperature scale was set", temperature, dim.temperatureScale());
} // testAccessors


// ----------------------------------------------------------------------
// Test computePressureScale().
void
spatialdata::units::TestNondimensional::testComputePressureScale(void) {
    const double timeScale = 2.0;
    const double densityScale = 3.0;
    const double lengthScale = 7.0;

    const double velocityScale = lengthScale / timeScale;
    const double pressureScale = densityScale * velocityScale * velocityScale;

    Nondimensional dim;
    dim.timeScale(timeScale);
    dim.densityScale(densityScale);
    dim.lengthScale(lengthScale);
    dim.computePressureScale();
    CPPUNIT_ASSERT_EQUAL(pressureScale, dim.pressureScale());
} // testComputePressureScale


// ----------------------------------------------------------------------
// Test computeDensityScale().
void
spatialdata::units::TestNondimensional::testComputeDensityScale(void) {
    const double timeScale = 2.0;
    const double pressureScale = 3.0;
    const double lengthScale = 7.0;

    const double velocityScale = lengthScale / timeScale;
    const double densityScale = pressureScale / (velocityScale * velocityScale);

    Nondimensional dim;
    dim.timeScale(timeScale);
    dim.pressureScale(pressureScale);
    dim.lengthScale(lengthScale);
    dim.computeDensityScale();
    CPPUNIT_ASSERT_EQUAL(densityScale, dim.densityScale());
} // testComputeDensityScale


// ----------------------------------------------------------------------
// Test nondimensionalize() and dimensionalize().
void
spatialdata::units::TestNondimensional::testNondimensionalize(void) {
    const double scale = 4.0;
    const double value = 3.0;
    const double valueE = 0.75;

    Nondimensional dim;
    const double tolerance = 1.0e-6;
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Checking nondimensionalized value.",
                                         valueE, dim.nondimensionalize(value, scale), tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Checking dimensionalize value.",
                                         value, dim.dimensionalize(valueE, scale), tolerance);
} // testNondimensionalize


// ----------------------------------------------------------------------
// Test nondimensionalize() and dimensionalize() with arrays.
void
spatialdata::units::TestNondimensional::testNondimensionalizeArray(void) {
    const double scale = 10.0;
    const size_t nvalues = 3;
    const double values[nvalues] = { 2.0, 5.0, 7.0 };
    const double valuesE[nvalues] = { 0.2, 0.5, 0.7 };

    Nondimensional dim;

    std::valarray<double> v(values, nvalues);
    dim.nondimensionalize(&v[0], nvalues, scale);
    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < nvalues; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Checking nondimensionalized values.", valuesE[i], v[i], tolerance);
    } // for

    v = std::valarray<double>(valuesE, nvalues);
    dim.dimensionalize(&v[0], nvalues, scale);
    for (size_t i = 0; i < nvalues; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Checking dimensionalized values.", values[i], v[i], tolerance);
    } // for
} // testNondimensionalizeArray


// End of file
