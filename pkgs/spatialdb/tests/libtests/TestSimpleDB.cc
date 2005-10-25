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

#include "spatialdata/spatialdb/SpatialDB.h" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.h" // USES SimpleDB

#include "TestSimpleDB.h" // Implementation of class methods

#include "../../lib/SimpleDBTypes.h" // USES SimpleDBTypes
#include "../../lib/SimpleDBQuery.h" // USES SimpleDBQuery

#include "spatialdata/geocoords/CoordSys.h" // USE CSCart
#include "spatialdata/geocoords/CSCart.h" // USE CSCart

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
// Setup test subject
void
spatialdata::spatialdb::TestSimpleDB::setUp(void)
{ // setUp
  SimpleDB::DataStruct* pData = new SimpleDB::DataStruct;

  const int numCoords = 3;
  const int numLocs = _numLocs();
  const int numVals = _numVals();

  const int dataSize = numLocs*(numCoords+numVals);
  FIREWALL(0 < dataSize);
  pData->data = new double[dataSize];
  memcpy(pData->data, _data(), dataSize*sizeof(double));

  pData->valNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valNames[i] = _names()[i];

  pData->numLocs = numLocs;
  pData->numVals = numVals;
  pData->topology = _topology();

  _pDB = new SimpleDB;
  _pDB->_pData = pData;
  _pDB->_pQuery = new SimpleDBQuery(*_pDB);
  _pDB->_pCS = new spatialdata::geocoords::CSCart();
} // setUp

// ----------------------------------------------------------------------
// Cleanup test subject
void
spatialdata::spatialdb::TestSimpleDB::tearDown(void)
{ // tearDown
  delete _pDB; _pDB = 0;
} // tearDown

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleDB::testConstructorA(void)
{ // testConstructorA
  SimpleDB db;
} // testConstructorA

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleDB::testConstructorB(void)
{ // testConstructorB
  const char* label = "database A";
  SimpleDB db(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testConstructorB

// ----------------------------------------------------------------------
// Test Label()
void
spatialdata::spatialdb::TestSimpleDB::testLabel(void)
{ // testLabel
  SimpleDB db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test Query() using nearest neighbor
void
spatialdata::spatialdb::TestSimpleDB::testQueryNearest(void)
{ // testQueryNearest
  SimpleDB* pDB = _database();
  FIREWALL(0 != pDB);

  pDB->queryType(SimpleDB::NEAREST);
  _checkQuery(_queryNearest());
} // testQueryNearest

// ----------------------------------------------------------------------
// Test Query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleDB::testQueryLinear(void)
{ // testQueryLinear
  FIREWALL(0 != _pDB);

  _pDB->queryType(SimpleDB::LINEAR);
  _checkQuery(_queryLinear());
} // testQueryLinear

// ----------------------------------------------------------------------
// Check query values.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(const double* queryData) const
{ // _checkQuery
  FIREWALL(0 != queryData);
  FIREWALL(0 != _pDB);

  const int numVals = _numVals();
  
  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = _names()[i];
  _pDB->queryVals(valNames, numVals);
  
  double* pVals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int numQueries = _numQueries();
  const int locSize = 3+numVals;
  spatialdata::geocoords::CSCart csCart;
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* qCoords = &queryData[iQuery*locSize];
    const double* qVals = &queryData[iQuery*locSize+3];
    _pDB->query(&pVals, numVals, qCoords[0], qCoords[1], qCoords[2], &csCart);
    for (int iVal=0; iVal < numVals; ++iVal)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(pVals[iVal]/qVals[numVals-iVal-1], 1.0,
				   tolerance);
  } // for
  delete[] pVals; pVals = 0;
} // CheckQuery

// version
// $Id: TestSimpleDB.cc,v 1.1 2005/05/25 18:43:04 baagaard Exp $

// End of file 
