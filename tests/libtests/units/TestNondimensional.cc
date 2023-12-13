// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()
#include <valarray> // USES std::valarray

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace units {
        class TestNondimensional;
    } // units
} // spatialdata

class spatialdata::units::TestNondimensional {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test constructors.
    static
    void testConstructors(void);

    /// Test accessors.
    static
    void testAccessors(void);

    /// Test computeDensityScale.
    static
    void testComputeDensityScale(void);

    /// Test computePressureScale.
    static
    void testComputePressureScale(void);

    /// Test nondimensionalize() and dimensionalize().
    static
    void testNondimensionalize(void);

    /// Test nondimensionalie() and dimensionalize() with arrays.
    static
    void testNondimensionalizeArray(void);

}; // class TestNondimensional

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestNondimensional::testConstructors", "[TestNondimensional]") {
    spatialdata::units::TestNondimensional::testConstructors();
}
TEST_CASE("TestNondimensional::testAccessors", "[TestNondimensional]") {
    spatialdata::units::TestNondimensional::testAccessors();
}
TEST_CASE("TestNondimensional::testComputeDensityScale", "[TestNondimensional]") {
    spatialdata::units::TestNondimensional::testComputeDensityScale();
}
TEST_CASE("TestNondimensional::testComputePressureScale", "[TestNondimensional]") {
    spatialdata::units::TestNondimensional::testComputePressureScale();
}
TEST_CASE("TestNondimensional::testNondimensionalize", "[TestNondimensional]") {
    spatialdata::units::TestNondimensional::testNondimensionalize();
}
TEST_CASE("TestNondimensional::testNondimensionalizeArray", "[TestNondimensional]") {
    spatialdata::units::TestNondimensional::testNondimensionalizeArray();
}

// ------------------------------------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestNondimensional::testConstructors(void) {
    const double defaultLength(1.0);
    const double defaultPressure(1.0);
    const double defaultTime(1.0);
    const double defaultDensity(1.0);
    const double defaultTemperature(1.0);

    Nondimensional dim;
    CHECK(defaultLength == dim._length);
    CHECK(defaultPressure == dim._pressure);
    CHECK(defaultTime == dim._time);
    CHECK(defaultDensity == dim._density);
    CHECK(defaultTemperature == dim._temperature);

    dim._length = 2.0;
    dim._pressure = 3.0;
    dim._time = 4.0;
    dim._density = 5.0;
    dim._temperature = 6.0;
    Nondimensional dimCopy(dim);
    CHECK(dim._length == dimCopy._length);
    CHECK(dim._pressure == dimCopy._pressure);
    CHECK(dim._time == dimCopy._time);
    CHECK(dim._density == dimCopy._density);
    CHECK(dim._temperature == dimCopy._temperature);

    Nondimensional dimAssign;
    dimAssign = dim;
    CHECK(dim._length == dimAssign._length);
    CHECK(dim._pressure == dimAssign._pressure);
    CHECK(dim._time == dimAssign._time);
    CHECK(dim._density == dimAssign._density);
    CHECK(dim._temperature == dimAssign._temperature);
} // testConstructors


// ------------------------------------------------------------------------------------------------
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
    INFO("Testing setting length scale.");
    dim.setLengthScale(length);
    CHECK(length == dim.getLengthScale());
    CHECK(1.0 == dim.getPressureScale());
    CHECK(1.0 == dim.getTimeScale());
    CHECK(1.0 == dim.getDensityScale());
    CHECK(1.0 == dim.getTemperatureScale());

    // Pressure scale
    INFO("Testing setting pressure scale.");
    dim.setPressureScale(pressure);
    CHECK(length == dim.getLengthScale());
    CHECK(pressure == dim.getPressureScale());
    CHECK(1.0 == dim.getTimeScale());
    CHECK(1.0 == dim.getDensityScale());
    CHECK(1.0 == dim.getTemperatureScale());

    // Time scale
    INFO("Testing setting time scale.");
    dim.setTimeScale(time);
    CHECK(length == dim.getLengthScale());
    CHECK(pressure == dim.getPressureScale());
    CHECK(time == dim.getTimeScale());
    CHECK(1.0 == dim.getDensityScale());
    CHECK(1.0 == dim.getTemperatureScale());

    // Density scale
    INFO("Testing setting density scale.");
    dim.setDensityScale(density);
    CHECK(length == dim.getLengthScale());
    CHECK(pressure == dim.getPressureScale());
    CHECK(time == dim.getTimeScale());
    CHECK(density == dim.getDensityScale());
    CHECK(1.0 == dim.getTemperatureScale());

    // Temperature scale
    INFO("Testing setting temperature scale.");
    dim.setTemperatureScale(temperature);
    CHECK(length == dim.getLengthScale());
    CHECK(pressure == dim.getPressureScale());
    CHECK(time == dim.getTimeScale());
    CHECK(density == dim.getDensityScale());
    CHECK(temperature == dim.getTemperatureScale());
} // testAccessors


// ------------------------------------------------------------------------------------------------
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
    CHECK_THAT(dim.getPressureScale(), Catch::Matchers::WithinAbs(pressureScale, pressureScale*1.0e-6));
} // testComputePressureScale


// ------------------------------------------------------------------------------------------------
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
    CHECK_THAT(dim.getDensityScale(), Catch::Matchers::WithinAbs(densityScale, densityScale*1.0e-6));
} // testComputeDensityScale


// ------------------------------------------------------------------------------------------------
// Test nondimensionalize() and dimensionalize().
void
spatialdata::units::TestNondimensional::testNondimensionalize(void) {
    const double scale = 4.0;
    const double value = 3.0;
    const double valueE = 0.75;

    Nondimensional dim;
    const double tolerance = 1.0e-6;
    CHECK_THAT(dim.nondimensionalize(value, scale), Catch::Matchers::WithinAbs(valueE, tolerance));
    CHECK_THAT(dim.dimensionalize(valueE, scale), Catch::Matchers::WithinAbs(value, tolerance));
} // testNondimensionalize


// ------------------------------------------------------------------------------------------------
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
        CHECK_THAT(v[i], Catch::Matchers::WithinAbs(valuesE[i], tolerance));
    } // for

    v = std::valarray<double>(valuesE, nvalues);
    dim.dimensionalize(&v[0], nvalues, scale);
    for (size_t i = 0; i < nvalues; ++i) {
        CHECK_THAT(v[i], Catch::Matchers::WithinAbs(values[i], tolerance));
    } // for
} // testNondimensionalizeArray


// End of file
