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

#include "TestNondimensional.hh" // Implementation of class methods

#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

#include <valarray> // USES std::valarray

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::units::TestNondimensional );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestNondimensional::testConstructor(void)
{ // testConstructor
  Nondimensional dim;
  CPPUNIT_ASSERT_EQUAL(1.0, dim._length);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._pressure);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._time);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._density);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._temperature);
} // testConstructor

// ----------------------------------------------------------------------
// Test copy constructor.
void
spatialdata::units::TestNondimensional::testCopyConstructor(void)
{ // testCopyConstructor
  Nondimensional dim;
  dim._length = 2.0;
  dim._pressure = 3.0;
  dim._time = 4.0;
  dim._density = 5.0;
  dim._temperature = 7.0;

  Nondimensional dim2(dim);
  CPPUNIT_ASSERT_EQUAL(2.0, dim2._length);
  CPPUNIT_ASSERT_EQUAL(3.0, dim2._pressure);
  CPPUNIT_ASSERT_EQUAL(4.0, dim2._time);
  CPPUNIT_ASSERT_EQUAL(5.0, dim2._density);
  CPPUNIT_ASSERT_EQUAL(7.0, dim2._temperature);
} // testCopyConstructor

// ----------------------------------------------------------------------
// Test assignment.
void
spatialdata::units::TestNondimensional::testAssignment(void)
{ // testAssignment
  Nondimensional dim;
  dim._length = 2.0;
  dim._pressure = 3.0;
  dim._time = 4.0;
  dim._density = 5.0;
  dim._temperature = 7.0;

  Nondimensional dim2;
  dim2 = dim;
  CPPUNIT_ASSERT_EQUAL(2.0, dim2._length);
  CPPUNIT_ASSERT_EQUAL(3.0, dim2._pressure);
  CPPUNIT_ASSERT_EQUAL(4.0, dim2._time);
  CPPUNIT_ASSERT_EQUAL(5.0, dim2._density);
  CPPUNIT_ASSERT_EQUAL(7.0, dim2._temperature);
} // testAssignment

// ----------------------------------------------------------------------
// Test lengthScale().
void
spatialdata::units::TestNondimensional::testLengthScale(void)
{ // testLengthScale
  Nondimensional dim;

  const double scale = 4.0;
  dim.lengthScale(scale);
  CPPUNIT_ASSERT_EQUAL(scale, dim.lengthScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.pressureScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.timeScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.densityScale());
} // testLengthScale

// ----------------------------------------------------------------------
// Test pressureScale().
void
spatialdata::units::TestNondimensional::testPressureScale(void)
{ // testPressureScale
  Nondimensional dim;

  const double scale = 4.0;
  dim.pressureScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim.lengthScale());
  CPPUNIT_ASSERT_EQUAL(scale, dim.pressureScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.timeScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.densityScale());
} // testPressureScale

// ----------------------------------------------------------------------
// Test timeScale().
void
spatialdata::units::TestNondimensional::testTimeScale(void)
{ // testTimeScale
  Nondimensional dim;

  const double scale = 4.0;
  dim.timeScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim.lengthScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.pressureScale());
  CPPUNIT_ASSERT_EQUAL(scale, dim.timeScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.densityScale());
} // testTimeScale

// ----------------------------------------------------------------------
// Test densityScale().
void
spatialdata::units::TestNondimensional::testDensityScale(void)
{ // testDensityScale
  Nondimensional dim;

  const double scale = 4.0;
  dim.densityScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim.lengthScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.pressureScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.timeScale());
  CPPUNIT_ASSERT_EQUAL(scale, dim.densityScale());
} // testDensityScale

// ----------------------------------------------------------------------
// Test temperatureScale().
void
spatialdata::units::TestNondimensional::testTemperatureScale(void)
{ // testTemperatureScale
  Nondimensional dim;

  const double scale = 4.0;
  dim.temperatureScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim.lengthScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.pressureScale());
  CPPUNIT_ASSERT_EQUAL(1.0, dim.timeScale());
  CPPUNIT_ASSERT_EQUAL(scale, dim.temperatureScale());
} // testTemperatureScale

// ----------------------------------------------------------------------
// Test nondimensionalize().
void
spatialdata::units::TestNondimensional::testNondimensionalize(void)
{ // testNondimensionalize
  const double scale = 4.0;
  const double value = 3.0;
  const double valueE = 0.75;

  Nondimensional dim;
  CPPUNIT_ASSERT_EQUAL(valueE, dim.nondimensionalize(value, scale));
} // testNondimensionalize

// ----------------------------------------------------------------------
// Test dimensionalize().
void
spatialdata::units::TestNondimensional::testDimensionalize(void)
{ // testDimensionalize
  const double scale = 4.0;
  const double value = 0.75;
  const double valueE = 3.0;

  Nondimensional dim;
  CPPUNIT_ASSERT_EQUAL(valueE, dim.dimensionalize(value, scale));
} // testNondimensionalize

// ----------------------------------------------------------------------
// Test nondimensionalize() with arrays.
void
spatialdata::units::TestNondimensional::testNondimensionalizeArray(void)
{ // testNondimensionalizeArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 2.0, 5.0, 7.0 };
  const double valuesE[] = { 0.2, 0.5, 0.7 };

  Nondimensional dim;
  std::valarray<double> v(values, nvalues);
  dim.nondimensionalize(&v[0], nvalues, scale);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testNondimensionalizeArray

// ----------------------------------------------------------------------
// Test dimensionalize() with arrays.
void
spatialdata::units::TestNondimensional::testDimensionalizeArray(void)
{ // testDimensionalizeArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 0.2, 0.5, 0.7 };
  const double valuesE[] = { 2.0, 5.0, 7.0 };

  Nondimensional dim;
  std::valarray<double> v(values, nvalues);
  dim.dimensionalize(&v[0], nvalues, scale);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testDimensionalizeArray


// End of file 
