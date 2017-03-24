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

#include "TestSimpleDBData.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include <string.h> // USES strcmp()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBData );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestSimpleDBData::testConstructor(void)
{ // testConstructor
  SimpleDBData data;
} // testConstructor

// ----------------------------------------------------------------------
// Test allocate(), numLocs(), numValues(), spaceDim().
void
spatialdata::spatialdb::TestSimpleDBData::testAllocate(void)
{ // testAllocate
  const int numLocs = 4;
  const int numValues = 5;
  const int spaceDim = 3;
  const int dataDim = 1;

  SimpleDBData data;
  data.allocate(numLocs, numValues, spaceDim, dataDim);

  CPPUNIT_ASSERT_EQUAL(numLocs, data.numLocs());
  CPPUNIT_ASSERT_EQUAL(numValues, data.numValues());
  CPPUNIT_ASSERT_EQUAL(spaceDim, data.spaceDim());
  CPPUNIT_ASSERT_EQUAL(dataDim, data.dataDim());
  CPPUNIT_ASSERT(0 != data._data);
  CPPUNIT_ASSERT(0 != data._coordinates);
  CPPUNIT_ASSERT(0 != data._names);
  CPPUNIT_ASSERT(0 != data._units);
} // testAllocate

// ----------------------------------------------------------------------
// Test data()
void
spatialdata::spatialdb::TestSimpleDBData::testData(void)
{ // testData
  const int numLocs = 4;
  const int numValues = 2;
  const int spaceDim = 3;
  const int dataDim = 1;

  const double valuesE[] = {
    0.11, 0.21,
    0.12, 0.22,
    0.13, 0.23,
    0.14, 0.24,
  };

  SimpleDBData data;
  data.allocate(numLocs, numValues, spaceDim, dataDim);
  data.data(valuesE, numLocs, numValues);

  for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
    const double* values = data.data(iLoc);
    CPPUNIT_ASSERT(0 != values);
    for (int iVal=0; iVal < numValues; ++iVal)
      CPPUNIT_ASSERT_EQUAL(valuesE[i++], values[iVal]);
  } // for
} // testData

// ----------------------------------------------------------------------
// Test coordinates()
void
spatialdata::spatialdb::TestSimpleDBData::testCoordinates(void)
{ // testCoordinates
  const int numLocs = 4;
  const int numValues = 2;
  const int spaceDim = 3;
  const int dataDim = 1;

  const double coordsE[] = {
    1.1, 2.1, 3.1,
    1.2, 2.2, 3.2,
    1.3, 2.3, 3.3,
    1.4, 2.4, 3.4,
  };

  SimpleDBData data;
  data.allocate(numLocs, numValues, spaceDim, dataDim);
  data.coordinates(coordsE, numLocs, spaceDim);

  for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
    const double* coords = data.coordinates(iLoc);
    CPPUNIT_ASSERT(0 != coords);
    for (int iDim=0; iDim < spaceDim; ++iDim)
      CPPUNIT_ASSERT_EQUAL(coordsE[i++], coords[iDim]);
  } // for
} // testCoordinates

// ----------------------------------------------------------------------
// Test names()
void
spatialdata::spatialdb::TestSimpleDBData::testNames(void)
{ // testNames
  const int numLocs = 4;
  const int numValues = 2;
  const int spaceDim = 3;
  const int dataDim = 1;

  const char* namesE[] = {
    "one", "two",
  };

  SimpleDBData data;
  data.allocate(numLocs, numValues, spaceDim, dataDim);
  data.names(namesE, numValues);

  for (int i=0; i < numValues; ++i)
    CPPUNIT_ASSERT_EQUAL(std::string(namesE[i]),
			 std::string(data.name(i)));
} // testNames

// ----------------------------------------------------------------------
// Test units()
void
spatialdata::spatialdb::TestSimpleDBData::testUnits(void)
{ // testUnits
  const int numLocs = 4;
  const int numValues = 2;
  const int spaceDim = 3;
  const int dataDim = 1;

  const char* unitsE[] = {
    "m", "m/s",
  };

  SimpleDBData data;
  data.allocate(numLocs, numValues, spaceDim, dataDim);
  data.units(unitsE, numValues);

  for (int i=0; i < numValues; ++i)
    CPPUNIT_ASSERT_EQUAL(std::string(unitsE[i]),
			 std::string(data.units(i)));
} // testUnits


// End of file 
