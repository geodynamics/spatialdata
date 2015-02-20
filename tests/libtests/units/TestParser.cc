// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestParser.hh" // Implementation of class methods

#include "spatialdata/units/Parser.hh" // USES Parser

#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::units::TestParser );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestParser::testConstructor(void)
{ // testConstructor
  // Test without prior initialization.
  Parser parserA;

  // Test with prior initialization.
  Parser parserB;
} // testConstructor

// ----------------------------------------------------------------------
// Test parse() with length scale.
void
spatialdata::units::TestParser::testLength(void)
{ // testLength
  Parser parser;

  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.01, parser.parse("cm"), tolerance);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0254, parser.parse("inch"), tolerance);
} // testLength

// ----------------------------------------------------------------------
// Test parse() with time scale.
void
spatialdata::units::TestParser::testTime(void)
{ // testTime
  Parser parser;

  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(60.0, parser.parse("minute"), tolerance);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.001, parser.parse("millisecond"), tolerance);
} // testTime

// ----------------------------------------------------------------------
// Test parse() with velocity scale.
void
spatialdata::units::TestParser::testVelocity(void)
{ // testVelocity
  Parser parser;

  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.01, parser.parse("cm/s"), tolerance);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0/3.6, parser.parse("km/hour"), tolerance);
} // testVelocity

// ----------------------------------------------------------------------
// Test parse() with density scale.
void
spatialdata::units::TestParser::testDensity(void)
{ // testDensity
  Parser parser;

  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, parser.parse("kg/m**3"), tolerance);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(1000.0, parser.parse("g/cm**3"), tolerance);
} // testDensity

// ----------------------------------------------------------------------
// Test parse() with pressure scale.
void
spatialdata::units::TestParser::testPressure(void)
{ // testPressure
  Parser parser;

  CPPUNIT_ASSERT_EQUAL(1.0, parser.parse("pascal"));

  CPPUNIT_ASSERT_EQUAL(1.0e+06, parser.parse("MPa"));
} // testPressure


// ----------------------------------------------------------------------
// Test trapping errors with parse().
void
spatialdata::units::TestParser::testError(void)
{ // testError
  Parser parser;

  CPPUNIT_ASSERT_THROW(parser.parse("abc"), std::runtime_error);
} // testError


// End of file 
