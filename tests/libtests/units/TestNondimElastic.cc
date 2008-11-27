// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestNondimElastic.hh" // Implementation of class methods

#include "spatialdata/units/NondimElastic.hh" // USES NondimElastic

#include <valarray> // USES std::valarray

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::units::TestNondimElastic );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::units::TestNondimElastic::testConstructor(void)
{ // testConstructor
  NondimElastic dim;
  CPPUNIT_ASSERT_EQUAL(1.0, dim._length);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._pressure);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._time);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._density);
} // testConstructor

// ----------------------------------------------------------------------
// Test copy constructor.
void
spatialdata::units::TestNondimElastic::testCopyConstructor(void)
{ // testCopyConstructor
  NondimElastic dim;
  dim._length = 2.0;
  dim._pressure = 3.0;
  dim._time = 4.0;
  dim._density = 5.0;

  NondimElastic dim2(dim);
  CPPUNIT_ASSERT_EQUAL(2.0, dim2._length);
  CPPUNIT_ASSERT_EQUAL(3.0, dim2._pressure);
  CPPUNIT_ASSERT_EQUAL(4.0, dim2._time);
  CPPUNIT_ASSERT_EQUAL(5.0, dim2._density);
} // testCopyConstructor

// ----------------------------------------------------------------------
// Test assignment.
void
spatialdata::units::TestNondimElastic::testAssignment(void)
{ // testAssignment
  NondimElastic dim;
  dim._length = 2.0;
  dim._pressure = 3.0;
  dim._time = 4.0;
  dim._density = 5.0;

  NondimElastic dim2;
  dim2 = dim;
  CPPUNIT_ASSERT_EQUAL(2.0, dim2._length);
  CPPUNIT_ASSERT_EQUAL(3.0, dim2._pressure);
  CPPUNIT_ASSERT_EQUAL(4.0, dim2._time);
  CPPUNIT_ASSERT_EQUAL(5.0, dim2._density);
} // testAssignment

// ----------------------------------------------------------------------
// Test lengthScale().
void
spatialdata::units::TestNondimElastic::testLengthScale(void)
{ // testLengthScale
  NondimElastic dim;

  const double scale = 4.0;
  dim.lengthScale(scale);
  CPPUNIT_ASSERT_EQUAL(scale, dim._length);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._pressure);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._time);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._density);
} // testLengthScale

// ----------------------------------------------------------------------
// Test pressureScale().
void
spatialdata::units::TestNondimElastic::testPressureScale(void)
{ // testPressureScale
  NondimElastic dim;

  const double scale = 4.0;
  dim.pressureScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._length);
  CPPUNIT_ASSERT_EQUAL(scale, dim._pressure);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._time);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._density);
} // testPressureScale

// ----------------------------------------------------------------------
// Test timeScale().
void
spatialdata::units::TestNondimElastic::testTimeScale(void)
{ // testTimeScale
  NondimElastic dim;

  const double scale = 4.0;
  dim.timeScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._length);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._pressure);
  CPPUNIT_ASSERT_EQUAL(scale, dim._time);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._density);
} // testTimeScale

// ----------------------------------------------------------------------
// Test densityScale().
void
spatialdata::units::TestNondimElastic::testDensityScale(void)
{ // testDensityScale
  NondimElastic dim;

  const double scale = 4.0;
  dim.densityScale(scale);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._length);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._pressure);
  CPPUNIT_ASSERT_EQUAL(1.0, dim._time);
  CPPUNIT_ASSERT_EQUAL(scale, dim._density);
} // testDensityScale

// ----------------------------------------------------------------------
// Test utonLength().
void
spatialdata::units::TestNondimElastic::testUtonLength(void)
{ // testUtonLength
  const double scale = 4.0;
  const double value = 3.0;
  const double valueE = 0.75;

  NondimElastic dim;
  dim.lengthScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.utonLength(value));
} // testUtonLength

// ----------------------------------------------------------------------
// Test ntouLength().
void
spatialdata::units::TestNondimElastic::testNtouLength(void)
{ // testNtouLength
  const double scale = 4.0;
  const double value = 0.75;
  const double valueE = 3.0;

  NondimElastic dim;
  dim.lengthScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.ntouLength(value));
} // testNtouLength

// ----------------------------------------------------------------------
// Test utonLength() with arrays.
void
spatialdata::units::TestNondimElastic::testUtonLengthArray(void)
{ // testUtonLengthArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 2.0, 5.0, 7.0 };
  const double valuesE[] = { 0.2, 0.5, 0.7 };

  NondimElastic dim;
  dim.lengthScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.utonLength(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testUtonLengthArray

// ----------------------------------------------------------------------
// Test ntouLength() with arrays.
void
spatialdata::units::TestNondimElastic::testNtouLengthArray(void)
{ // testNtouLengthArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 0.2, 0.5, 0.7 };
  const double valuesE[] = { 2.0, 5.0, 7.0 };

  NondimElastic dim;
  dim.lengthScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.ntouLength(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testNtouLengthArray

// ----------------------------------------------------------------------
// Test utonPressure().
void
spatialdata::units::TestNondimElastic::testUtonPressure(void)
{ // testUtonPressure
  const double scale = 4.0;
  const double value = 3.0;
  const double valueE = 0.75;

  NondimElastic dim;
  dim.pressureScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.utonPressure(value));
} // testUtonPressure

// ----------------------------------------------------------------------
// Test ntouPressure().
void
spatialdata::units::TestNondimElastic::testNtouPressure(void)
{ // testNtouPressure
  const double scale = 4.0;
  const double value = 0.75;
  const double valueE = 3.0;

  NondimElastic dim;
  dim.pressureScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.ntouPressure(value));
} // testNtouPressure

// ----------------------------------------------------------------------
// Test utonPressure() with arrays.
void
spatialdata::units::TestNondimElastic::testUtonPressureArray(void)
{ // testUtonPressureArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 2.0, 5.0, 7.0 };
  const double valuesE[] = { 0.2, 0.5, 0.7 };

  NondimElastic dim;
  dim.pressureScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.utonPressure(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testUtonPressureArray

// ----------------------------------------------------------------------
// Test ntouPressure() with arrays.
void
spatialdata::units::TestNondimElastic::testNtouPressureArray(void)
{ // testNtouPressureArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 0.2, 0.5, 0.7 };
  const double valuesE[] = { 2.0, 5.0, 7.0 };

  NondimElastic dim;
  dim.pressureScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.ntouPressure(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testNtouPressureArray

// ----------------------------------------------------------------------
// Test utonTime().
void
spatialdata::units::TestNondimElastic::testUtonTime(void)
{ // testUtonTime
  const double scale = 4.0;
  const double value = 3.0;
  const double valueE = 0.75;

  NondimElastic dim;
  dim.timeScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.utonTime(value));
} // testUtonTime

// ----------------------------------------------------------------------
// Test ntouTime().
void
spatialdata::units::TestNondimElastic::testNtouTime(void)
{ // testNtouTime
  const double scale = 4.0;
  const double value = 0.75;
  const double valueE = 3.0;

  NondimElastic dim;
  dim.timeScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.ntouTime(value));
} // testNtouTime

// ----------------------------------------------------------------------
// Test utonTime() with arrays.
void
spatialdata::units::TestNondimElastic::testUtonTimeArray(void)
{ // testUtonTimeArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 2.0, 5.0, 7.0 };
  const double valuesE[] = { 0.2, 0.5, 0.7 };

  NondimElastic dim;
  dim.timeScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.utonTime(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testUtonTimeArray

// ----------------------------------------------------------------------
// Test ntouTime() with arrays.
void
spatialdata::units::TestNondimElastic::testNtouTimeArray(void)
{ // testNtouTimeArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 0.2, 0.5, 0.7 };
  const double valuesE[] = { 2.0, 5.0, 7.0 };

  NondimElastic dim;
  dim.timeScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.ntouTime(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testNtouTimeArray

// ----------------------------------------------------------------------
// Test utonDensity().
void
spatialdata::units::TestNondimElastic::testUtonDensity(void)
{ // testUtonDensity
  const double scale = 4.0;
  const double value = 3.0;
  const double valueE = 0.75;

  NondimElastic dim;
  dim.densityScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.utonDensity(value));
} // testUtonDensity

// ----------------------------------------------------------------------
// Test ntouDensity().
void
spatialdata::units::TestNondimElastic::testNtouDensity(void)
{ // testNtouDensity
  const double scale = 4.0;
  const double value = 0.75;
  const double valueE = 3.0;

  NondimElastic dim;
  dim.densityScale(scale);
  CPPUNIT_ASSERT_EQUAL(valueE, dim.ntouDensity(value));
} // testNtouDensity

// ----------------------------------------------------------------------
// Test utonDensity() with arrays.
void
spatialdata::units::TestNondimElastic::testUtonDensityArray(void)
{ // testUtonDensityArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 2.0, 5.0, 7.0 };
  const double valuesE[] = { 0.2, 0.5, 0.7 };

  NondimElastic dim;
  dim.densityScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.utonDensity(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testUtonDensityArray

// ----------------------------------------------------------------------
// Test ntouDensity() with arrays.
void
spatialdata::units::TestNondimElastic::testNtouDensityArray(void)
{ // testNtouDensityArray
  const double scale = 10.0;
  const int nvalues = 3;
  const double values[] = { 0.2, 0.5, 0.7 };
  const double valuesE[] = { 2.0, 5.0, 7.0 };

  NondimElastic dim;
  dim.densityScale(scale);
  std::valarray<double> v(values, nvalues);
  dim.ntouDensity(&v[0], nvalues);
  
  for (int i=0; i < nvalues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], v[i]);
} // testNtouDensityArray


// End of file 
