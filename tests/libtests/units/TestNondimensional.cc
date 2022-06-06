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
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default length scale", defaultLength, dim._length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default pressure scale", defaultPressure, dim._pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default time scale", defaultTime, dim._time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default density scale", defaultDensity, dim._density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default temperature scale", defaultTemperature, dim._temperature);

    dim._length = 2.0;
    dim._pressure = 3.0;
    dim._time = 4.0;
    dim._density = 5.0;
    dim._temperature = 6.0;
    Nondimensional dimCopy(dim);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in copy length scale", dim._length, dimCopy._length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in copy pressure scale", dim._pressure, dimCopy._pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in copy time scale", dim._time, dimCopy._time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in copy density scale", dim._density, dimCopy._density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in copy temperature scale", dim._temperature, dimCopy._temperature);

    Nondimensional dimAssign;
    dimAssign = dim;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in assign length scale", dim._length, dimAssign._length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in assign pressure scale", dim._pressure, dimAssign._pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in assign time scale", dim._time, dimAssign._time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in assign density scale", dim._density, dimAssign._density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in assign temperature scale", dim._temperature, dimAssign._temperature);
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
    dim.setLengthScale(length);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set length scale: Mismatch in length scale.", length, dim.getLengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set length scale: Mismatch in pressure scale.", 1.0, dim.getPressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set length scale: Mismatch in time scale.", 1.0, dim.getTimeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set length scale: Mismatch in density scale.", 1.0, dim.getDensityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set length scale: Mismatch in temperature scale.", 1.0, dim.getTemperatureScale());

    // Pressure scale
    dim.setPressureScale(pressure);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set pressure scale. Mismatch in length scale.", length, dim.getLengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set pressure scale. Mismatch in pressure scale.", pressure, dim.getPressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set pressure scale. Mismatch in time scale.", 1.0, dim.getTimeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set pressure scale. Mismatch in density scale.", 1.0, dim.getDensityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set pressure scale. Mismatch in temperature scale.", 1.0, dim.getTemperatureScale());

    // Time scale
    dim.setTimeScale(time);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set time scale. Mismatch in length scale.", length, dim.getLengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set time scale. Mismatch in pressure scale.", pressure, dim.getPressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set time scale. Mismatch in time scale.", time, dim.getTimeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set time scale. Mismatch in density scale.", 1.0, dim.getDensityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set time scale. Mismatch in temperature scale.", 1.0, dim.getTemperatureScale());

    // Density scale
    dim.setDensityScale(density);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set density scale. Mismatch in length scale.", length, dim.getLengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set density scale. Mismatch in pressure scale.", pressure, dim.getPressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set density scale. Mismatch in time scale.", time, dim.getTimeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set density scale. Mismatch in density scale.", density, dim.getDensityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set density scale. Mismatch in temperature scale.", 1.0, dim.getTemperatureScale());

    // Temperature scale
    dim.setTemperatureScale(temperature);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set temperature scale. Mismatch in length scale.", length, dim.getLengthScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set temperature scale. Mismatch in pressure scale.", pressure, dim.getPressureScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set temperature scale. Mismatch in time scale.", time, dim.getTimeScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set temperature scale. Mismatch in density scale.", density, dim.getDensityScale());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Set temperature scale. Mismatch in temperature scale.", temperature, dim.getTemperatureScale());
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
    dim.setTimeScale(timeScale);
    dim.setDensityScale(densityScale);
    dim.setLengthScale(lengthScale);
    dim.computePressureScale();
    CPPUNIT_ASSERT_EQUAL(pressureScale, dim.getPressureScale());
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
    dim.setTimeScale(timeScale);
    dim.setPressureScale(pressureScale);
    dim.setLengthScale(lengthScale);
    dim.computeDensityScale();
    CPPUNIT_ASSERT_EQUAL(densityScale, dim.getDensityScale());
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
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in nondimensionalized value.",
                                         valueE, dim.nondimensionalize(value, scale), tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in dimensionalize value.",
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
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in nondimensionalized values.", valuesE[i], v[i], tolerance);
    } // for

    v = std::valarray<double>(valuesE, nvalues);
    dim.dimensionalize(&v[0], nvalues, scale);
    for (size_t i = 0; i < nvalues; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in dimensionalized values.", values[i], v[i], tolerance);
    } // for
} // testNondimensionalizeArray


// End of file
