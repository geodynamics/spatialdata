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

#include "TestCompositeDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/CompositeDB.hh" // USES CompositeDB

#include "spatialdata/spatialdb/UniformDB.hh" // USES CompositeDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include <string.h> // USES strcmp()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestCompositeDB );

// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestCompositeDB::testConstructorA(void)
{ // testConstructorA
  CompositeDB db;
} // testConstructorA

// ----------------------------------------------------------------------
// Test constructor w/label.
void
spatialdata::spatialdb::TestCompositeDB::testConstructorB(void)
{ // testConstructorB
  const char* label = "database A";
  CompositeDB db(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testConstructorB

// ----------------------------------------------------------------------
// Test Label().
void
spatialdata::spatialdb::TestCompositeDB::testLabel(void)
{ // testLabel
  CompositeDB db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test dbA().
void
spatialdata::spatialdb::TestCompositeDB::testDBA(void)
{ // testDBA
  CompositeDB db;

  UniformDB dbU;
  const int numValuesU = 3;
  const char* namesU[] = { "one", "two", "three" };
  const char* unitsU[] = { "none", "none", "none" };
  const double valuesU[] = { 1.1, 2.2, 3.3 };
  dbU.setData(namesU, unitsU, valuesU, numValuesU);

  const int numNamesA = 2;
  const char* namesA[] = { "three", "one" };
  db.dbA(&dbU, namesA, numNamesA);

  CPPUNIT_ASSERT(0 != db._dbA);
  CPPUNIT_ASSERT(0 != db._infoA);
  CPPUNIT_ASSERT(0 == db._infoA->query_buffer);
  CPPUNIT_ASSERT(0 == db._infoA->query_indices);
  CPPUNIT_ASSERT(0 == db._infoA->query_size);
  CPPUNIT_ASSERT(numNamesA == db._infoA->num_names);
  for (int i=0; i < numNamesA; ++i)
    CPPUNIT_ASSERT_EQUAL(std::string(namesA[i]),
			 db._infoA->names_values[i]);

  CPPUNIT_ASSERT(0 == db._dbB);
  CPPUNIT_ASSERT(0 == db._infoB);
} // testDBA

// ----------------------------------------------------------------------
// Test dbB().
void
spatialdata::spatialdb::TestCompositeDB::testDBB(void)
{ // testDBB
  CompositeDB db;

  UniformDB dbU;
  const int numValuesU = 3;
  const char* namesU[] = { "one", "two", "three" };
  const char* unitsU[] = { "none", "none", "none" };
  const double valuesU[] = { 1.1, 2.2, 3.3 };
  dbU.setData(namesU, unitsU, valuesU, numValuesU);

  const int numNamesB = 2;
  const char* namesB[] = { "three", "one" };
  db.dbB(&dbU, namesB, numNamesB);

  CPPUNIT_ASSERT(0 != db._dbB);
  CPPUNIT_ASSERT(0 != db._infoB);
  CPPUNIT_ASSERT(0 == db._infoB->query_buffer);
  CPPUNIT_ASSERT(0 == db._infoB->query_indices);
  CPPUNIT_ASSERT(0 == db._infoB->query_size);
  CPPUNIT_ASSERT(numNamesB == db._infoB->num_names);
  for (int i=0; i < numNamesB; ++i)
    CPPUNIT_ASSERT_EQUAL(std::string(namesB[i]),
			 db._infoB->names_values[i]);

  CPPUNIT_ASSERT(0 == db._dbA);
  CPPUNIT_ASSERT(0 == db._infoA);
} // testDBB

// ----------------------------------------------------------------------
// Test queryVals().
void
spatialdata::spatialdb::TestCompositeDB::testQueryVals(void)
{ // testQueryVals
  CompositeDB db;

  UniformDB dbA;
  { // initialize db A
    const int numValuesA = 3;
    const char* namesA[] = { "one", "two", "three" };
    const char* unitsA[] = { "none", "none", "none" };
    const double valuesA[] = { 1.1, 2.2, 3.3 };
    dbA.setData(namesA, unitsA, valuesA, numValuesA);
  } // initialize db A
    
  const int numNamesA = 2;
  const char* namesA[] = { "three", "one" };
  db.dbA(&dbA, namesA, numNamesA);

  UniformDB dbB;
  { // initialize db B
    const int numValuesB = 2;
    const char* namesB[] = { "four", "five" };
    const char* unitsB[] = { "none", "none" };
    const double valuesB[] = { 4.4, 5.5 };
    dbB.setData(namesB, unitsB, valuesB, numValuesB);
  } // initialize db B

  const int numNamesB = 1;
  const char* namesB[] = { "five" };
  db.dbB(&dbB, namesB, numNamesB);

  const int querySize = 3;
  const char* queryVals[] = { "one", "five", "three" };
  
  db.open();
  db.queryVals(queryVals, querySize);
  db.close();

  const int qsizeA = 2;
  const int qindicesA[] = { 0, 2 };
  CPPUNIT_ASSERT(0 != db._dbA);
  CPPUNIT_ASSERT(0 != db._infoA);
  CPPUNIT_ASSERT(qsizeA == db._infoA->query_size);
  CPPUNIT_ASSERT(0 != db._infoA->query_buffer);
  CPPUNIT_ASSERT(0 != db._infoA->query_indices);
  for (int i=0; i < qsizeA; ++i)
    CPPUNIT_ASSERT_EQUAL(qindicesA[i], db._infoA->query_indices[i]);

  const int qsizeB = 1;
  const int qindicesB[] = { 1 };
  CPPUNIT_ASSERT(0 != db._dbB);
  CPPUNIT_ASSERT(0 != db._infoB);
  CPPUNIT_ASSERT(qsizeB == db._infoB->query_size);
  CPPUNIT_ASSERT(0 != db._infoB->query_buffer);
  CPPUNIT_ASSERT(0 != db._infoB->query_indices);
  for (int i=0; i < qsizeB; ++i)
    CPPUNIT_ASSERT_EQUAL(qindicesB[i], db._infoB->query_indices[i]);
} // testQueryVals

// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestCompositeDB::testQuery(void)
{ // testQuery
  CompositeDB db;

  UniformDB dbA;
  { // initialize db A
    const int numValuesA = 3;
    const char* namesA[] = { "one", "two", "three" };
    const char* unitsA[] = { "none", "none", "none" };
    const double valuesA[] = { 1.1, 2.2, 3.3 };
    dbA.setData(namesA, unitsA, valuesA, numValuesA);
  } // initialize db A

  const int numNamesA = 2;
  const char* namesA[] = { "three", "one" };
  db.dbA(&dbA, namesA, numNamesA);

  UniformDB dbB;
  { // initialize db B
    const int numValuesB = 2;
    const char* namesB[] = { "four", "five" };
    const char* unitsB[] = { "none", "none" };
    const double valuesB[] = { 4.4, 5.5 };
    dbB.setData(namesB, unitsB, valuesB, numValuesB);
  } // initialize db B

  const int numNamesB = 1;
  const char* namesB[] = { "five" };
  db.dbB(&dbB, namesB, numNamesB);

  const int querySize = 2;
  const char* queryVals[] = { "five", "one" };
  
  const int spaceDim = 2;
  spatialdata::geocoords::CSCart cs;
  cs.setSpaceDim(spaceDim);
  const double coords[] = { 2.3, 5.6 };
  double data[querySize];
  const double valsE[] = { 5.5, 1.1 };

  db.open();
  db.queryVals(queryVals, querySize);
  db.query(data, querySize, coords, spaceDim, &cs);
  db.close();

  for (int i=0; i < querySize; ++i)
    CPPUNIT_ASSERT_EQUAL(valsE[i], data[i]);
} // testQuery


// End of file 
