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

#include "spatialdata/units/Parser.hh" // USES Parser

#include <stdexcept> // USES std::runtime_error

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace units {
        class TestParser;
    } // units
} // spatialdata

class spatialdata::units::TestParser {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test constructor.
    static
    void testConstructor(void);

    /// Test parse() with length scale.
    static
    void testLength(void);

    /// Test parse() with time scale.
    static
    void testTime(void);

    /// Test parse() with velocity scale.
    static
    void testVelocity(void);

    /// Test parse() with density scale.
    static
    void testDensity(void);

    /// Test parse() with pressure scale.
    static
    void testPressure(void);

    /// Test trapping errors with parse().
    static
    void testError(void);

    // PRIVATE MEMBERS ////////////////////////////////////////////////////////////////////////////
private:

    static const double _tolerance;
}; // class TestParser
const double spatialdata::units::TestParser::_tolerance = 1.0e-6;

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestParser::testConstructor", "[TestParser]") {
    spatialdata::units::TestParser::testConstructor();
}
TEST_CASE("TestParser::testLength", "[TestParser]") {
    spatialdata::units::TestParser::testLength();
}
TEST_CASE("TestParser::testTime", "[TestParser]") {
    spatialdata::units::TestParser::testTime();
}
TEST_CASE("TestParser::testVelocity", "[TestParser]") {
    spatialdata::units::TestParser::testVelocity();
}
TEST_CASE("TestParser::testDensity", "[TestParser]") {
    spatialdata::units::TestParser::testDensity();
}
TEST_CASE("TestParser::testPressure", "[TestParser]") {
    spatialdata::units::TestParser::testPressure();
}
TEST_CASE("TestParser::testError", "[TestParser]") {
    spatialdata::units::TestParser::testError();
}

// ------------------------------------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestParser::testConstructor(void) {
    // Test without prior initialization.
    Parser parserA;

    // Test with prior initialization.
    Parser parserB;
} // testConstructor


// ------------------------------------------------------------------------------------------------
// Test parse() with length scale.
void
spatialdata::units::TestParser::testLength(void) {
    Parser parser;

    CHECK_THAT(parser.parse("cm"), Catch::Matchers::WithinAbs(0.01, _tolerance));
    CHECK_THAT(parser.parse("inch"), Catch::Matchers::WithinAbs(0.0254, _tolerance));
} // testLength


// ------------------------------------------------------------------------------------------------
// Test parse() with time scale.
void
spatialdata::units::TestParser::testTime(void) {
    Parser parser;

    CHECK_THAT(parser.parse("minute"), Catch::Matchers::WithinAbs(60.0, _tolerance));
    CHECK_THAT(parser.parse("millisecond"), Catch::Matchers::WithinAbs(0.001, _tolerance));
} // testTime


// ------------------------------------------------------------------------------------------------
// Test parse() with velocity scale.
void
spatialdata::units::TestParser::testVelocity(void) {
    Parser parser;

    CHECK_THAT(parser.parse("cm/s"), Catch::Matchers::WithinAbs(0.01, _tolerance));
    CHECK_THAT(parser.parse("km/hour"), Catch::Matchers::WithinAbs(1.0/3.6, _tolerance));
} // testVelocity


// ------------------------------------------------------------------------------------------------
// Test parse() with density scale.
void
spatialdata::units::TestParser::testDensity(void) {
    Parser parser;

    CHECK_THAT(parser.parse("kg/m**3"), Catch::Matchers::WithinAbs(1.0, _tolerance));
    CHECK_THAT(parser.parse("g/cm**3"), Catch::Matchers::WithinAbs(1000.0, _tolerance));
} // testDensity


// ------------------------------------------------------------------------------------------------
// Test parse() with pressure scale.
void
spatialdata::units::TestParser::testPressure(void) {
    Parser parser;

    CHECK_THAT(parser.parse("pascal"), Catch::Matchers::WithinAbs(1.0, _tolerance));
    CHECK_THAT(parser.parse("MPa"), Catch::Matchers::WithinAbs(1.0e+06, _tolerance));
} // testPressure


// ------------------------------------------------------------------------------------------------
// Test trapping errors with parse().
void
spatialdata::units::TestParser::testError(void) {
    Parser parser;

    CHECK_THROWS_AS(parser.parse("abc"), std::runtime_error);
} // testError


// End of file
