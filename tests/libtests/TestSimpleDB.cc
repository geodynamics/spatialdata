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

#include "spatialdata/SpatialDB.h" // USES SimpleDB
#include "spatialdata/SimpleDB.h" // USES SimpleDB

#include "TestSimpleDB.h" // Implementation of class methods

#include "../../lib/SimpleDBTypes.h" // USES SimpleDBTypes
#include "../../lib/SimpleDBQuery.h" // USES SimpleDBQuery

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL

#include "journal/debug.h" // USES journal::debug_t

// ----------------------------------------------------------------------
// Setup test subject
void
spatial::TestSimpleDB::setUp(void)
{ // setUp
  SimpleDB::DataStruct* pData = new SimpleDB::DataStruct;

  const int numCoords = 3;
  const int numLocs = NumLocs();
  const int numVals = NumVals();

  const int dataSize = numLocs*(numCoords+numVals);
  FIREWALL(0 < dataSize);
  pData->Data = new double[dataSize];
  memcpy(pData->Data, Data(), dataSize*sizeof(double));

  pData->ValNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->ValNames[i] = Names()[i];

  pData->NumLocs = numLocs;
  pData->NumVals = numVals;
  pData->Topology = Topology();

  mpDB = new SimpleDB;
  mpDB->mpData = pData;
  mpDB->mpQuery = new SimpleDBQuery(*mpDB);
} // setUp

// ----------------------------------------------------------------------
// Cleanup test subject
void
spatial::TestSimpleDB::tearDown(void)
{ // tearDown
  delete mpDB; mpDB = 0;
} // tearDown

// ----------------------------------------------------------------------
// Test constructor
void
spatial::TestSimpleDB::testConstructorA(void)
{ // testConstructorA
  SimpleDB db;
} // testConstructorA

// ----------------------------------------------------------------------
// Test constructor
void
spatial::TestSimpleDB::testConstructorB(void)
{ // testConstructorB
  const char* label = "database A";
  SimpleDB db(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.Label()));
} // testConstructorB

// ----------------------------------------------------------------------
// Test Label()
void
spatial::TestSimpleDB::testLabel(void)
{ // testLabel
  SimpleDB db;
  const char* label = "database 2";
  db.Label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.Label()));
} // testLabel

// ----------------------------------------------------------------------
// Test Query() using nearest neighbor
void
spatial::TestSimpleDB::testQueryNearest(void)
{ // testQueryNearest
  SimpleDB* pDB = Database();
  FIREWALL(0 != pDB);

  pDB->QueryType(SimpleDB::NEAREST);
  CheckQuery(QueryNearest());
} // testQueryNearest

// ----------------------------------------------------------------------
// Test Query() using linear interpolation
void
spatial::TestSimpleDB::testQueryLinear(void)
{ // testQueryLinear
  FIREWALL(0 != mpDB);

  mpDB->QueryType(SimpleDB::LINEAR);
  CheckQuery(QueryLinear());
} // testQueryLinear

// ----------------------------------------------------------------------
// Check query values.
void
spatial::TestSimpleDB::CheckQuery(const double* queryData) const
{ // CheckQuery
  journal::debug_t debug("TestSimpleDB");

  FIREWALL(0 != queryData);
  FIREWALL(0 != mpDB);

  const int numVals = NumVals();
  
  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = Names()[i];
  mpDB->QueryVals(valNames, numVals);
  
  double* vals = 0;
  const double tolerance = 1.0e-06;
  
  const int numQueries = NumQueries();
  const int locSize = 3+numVals;
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* qCoords = &queryData[iQuery*locSize];
    const double* qVals = &queryData[iQuery*locSize+3];
    mpDB->Query(&vals, qCoords[0], qCoords[1], qCoords[2]);
    for (int iVal=0; iVal < numVals; ++iVal) {
      debug
	<< journal::at(__HERE__)
	<< "iVal: " << iVal
	<< ", vals[" << iVal << "]: " << vals[iVal]
	<< ", qVals[" << numVals-iVal-1 << "]: " << qVals[numVals-iVal-1]
	<< journal::endl;
      CPPUNIT_ASSERT_DOUBLES_EQUAL(vals[iVal]/qVals[numVals-iVal-1], 1.0,
				   tolerance);
    } // for
  } // for
} // CheckQuery

// version
// $Id: TestSimpleDB.cc,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
