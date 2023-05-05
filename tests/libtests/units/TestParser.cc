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

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/units/Parser.hh" // USES Parser

#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace units {
        class TestParser;
    } // units
} // spatialdata

class spatialdata::units::TestParser : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestParser);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testLength);
    CPPUNIT_TEST(testTime);
    CPPUNIT_TEST(testVelocity);
    CPPUNIT_TEST(testDensity);
    CPPUNIT_TEST(testPressure);
    CPPUNIT_TEST(testError);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test constructor.
    void testConstructor(void);

    /// Test parse() with length scale.
    void testLength(void);

    /// Test parse() with time scale.
    void testTime(void);

    /// Test parse() with velocity scale.
    void testVelocity(void);

    /// Test parse() with density scale.
    void testDensity(void);

    /// Test parse() with pressure scale.
    void testPressure(void);

    /// Test trapping errors with parse().
    void testError(void);

    // PRIVATE MEMBERS /////////////////////////////////////////////////////
private:

    static const double _tolerance;
}; // class TestParser
const double spatialdata::units::TestParser::_tolerance = 1.0e-6;

CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::units::TestParser);

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestParser::testConstructor(void) {
    // Test without prior initialization.
    Parser parserA;

    // Test with prior initialization.
    Parser parserB;
} // testConstructor


// ----------------------------------------------------------------------
// Test parse() with length scale.
void
spatialdata::units::TestParser::testLength(void) {
    Parser parser;

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'cm'.", 0.01, parser.parse("cm"), _tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'inch'.", 0.0254, parser.parse("inch"), _tolerance);
} // testLength


// ----------------------------------------------------------------------
// Test parse() with time scale.
void
spatialdata::units::TestParser::testTime(void) {
    Parser parser;

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'minute'.", 60.0, parser.parse("minute"), _tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'millisecond'.", 0.001, parser.parse("millisecond"), _tolerance);
} // testTime


// ----------------------------------------------------------------------
// Test parse() with velocity scale.
void
spatialdata::units::TestParser::testVelocity(void) {
    Parser parser;

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'cm/s'.", 0.01, parser.parse("cm/s"), _tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'km/hour'.", 1.0/3.6, parser.parse("km/hour"), _tolerance);
} // testVelocity


// ----------------------------------------------------------------------
// Test parse() with density scale.
void
spatialdata::units::TestParser::testDensity(void) {
    Parser parser;

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'kg/m**3'.", 1.0, parser.parse("kg/m**3"), _tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'g/cm**3'.", 1000.0, parser.parse("g/cm**3"), _tolerance);
} // testDensity


// ----------------------------------------------------------------------
// Test parse() with pressure scale.
void
spatialdata::units::TestParser::testPressure(void) {
    Parser parser;

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'pascal'.", 1.0, parser.parse("pascal"), _tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch when parsing 'MPa'.", 1.0e+06, parser.parse("MPa"), _tolerance);
} // testPressure


// ----------------------------------------------------------------------
// Test trapping errors with parse().
void
spatialdata::units::TestParser::testError(void) {
    Parser parser;

    CPPUNIT_ASSERT_THROW(parser.parse("abc"), std::runtime_error);
} // testError


// End of file
