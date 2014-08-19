// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestUniformDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/UniformDB.hh" // USES UniformDB

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include <string.h> // USES strcmp()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestUniformDB );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestUniformDB::testConstructorA(void)
{ // testConstructorA
  UniformDB db;
} // testConstructorA

// ----------------------------------------------------------------------
// Test constructor w/label.
void
spatialdata::spatialdb::TestUniformDB::testConstructorB(void)
{ // testConstructorB
  const char* label = "database A";
  UniformDB db(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testConstructorB

// ----------------------------------------------------------------------
// Test Label().
void
spatialdata::spatialdb::TestUniformDB::testLabel(void)
{ // testLabel
  UniformDB db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test setData().
void
spatialdata::spatialdb::TestUniformDB::testSetData(void)
{ // testSetData
  UniformDB db;

  const int numValues = 3;
  const char* names[numValues] = { "one", "two", "three" };
  const char* units[numValues] = { "m", "km", "cm" };
  const double values[numValues] = { 1.1, 2.2, 3.3 };
  const double valuesE[numValues] = { 1.1, 2.2e+3, 3.3e-2 };

  db.setData(names, units, values, numValues);

  CPPUNIT_ASSERT_EQUAL(numValues, db._numValues);
  for (int i=0; i < numValues; ++i)
    CPPUNIT_ASSERT_EQUAL(std::string(names[i]), db._names[i]);

  for (int i=0; i < numValues; ++i)
    CPPUNIT_ASSERT_EQUAL(valuesE[i], db._values[i]);
} // testSetData

// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestUniformDB::testQueryVals(void)
{ // testQueryVals
  UniformDB db;

  const int numValues = 3;
  const char* names[numValues] = { "one", "two", "three" };
  const char* units[numValues] = { "none", "none", "none" };
  const double values[numValues] = { 1.1, 2.2, 3.3 };

  const int querySize = 2;
  const char* queryNames[querySize] = { "three", "two" };
  const int queryVals[querySize] = { 2, 1 };

  db.setData(names, units, values, numValues);
  db.queryVals(queryNames, querySize);

  CPPUNIT_ASSERT_EQUAL(querySize, db._querySize);
  for (int i=0; i < querySize; ++i)
    CPPUNIT_ASSERT_EQUAL(queryVals[i], db._queryVals[i]);
} // testQueryVals

// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestUniformDB::testQuery(void)
{ // testQuery
  UniformDB db;

  const int numValues = 3;
  const char* names[numValues] = { "one", "two", "three" };
  const char* units[numValues] = { "none", "none", "none" };
  const double values[numValues] = { 1.1, 2.2, 3.3 };

  const int querySize = 2;
  const char* queryNames[querySize] = { "three", "two" };
  const int queryVals[querySize] = { 2, 1 };

  db.setData(names, units, values, numValues);
  db.queryVals(queryNames, querySize);

  const int spaceDim = 2;
  spatialdata::geocoords::CSCart cs;
  cs.setSpaceDim(spaceDim);
  const double coords[spaceDim] = { 2.3, 5.6 };
  double data[querySize];

  db.query(data, querySize, coords, spaceDim, &cs);

  for (int i=0; i < querySize; ++i) {
    const double valE = values[queryVals[i]];
    CPPUNIT_ASSERT_EQUAL(valE, data[i]);
  } // for
} // testQuery


// End of file 
