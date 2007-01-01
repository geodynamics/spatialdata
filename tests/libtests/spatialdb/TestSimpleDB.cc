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

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB

#include "TestSimpleDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDBTypes.hh" // USES SimpleDBTypes
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery

#include "spatialdata/geocoords/CoordSys.hh" // USE CSCart
#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

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
  CPPUNIT_ASSERT(0 < dataSize);
  pData->data = new double[dataSize];
  memcpy(pData->data, _data(), dataSize*sizeof(double));

  pData->valNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valNames[i] = _names()[i];

  pData->valUnits = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    pData->valUnits[i] = _units()[i];

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
  CPPUNIT_ASSERT(0 != pDB);

  pDB->queryType(SimpleDB::NEAREST);
  _checkQuery(_queryNearest(), 0);
} // testQueryNearest

// ----------------------------------------------------------------------
// Test Query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleDB::testQueryLinear(void)
{ // testQueryLinear
  CPPUNIT_ASSERT(0 != _pDB);

  _pDB->queryType(SimpleDB::LINEAR);
  _checkQuery(_queryLinear(), _errFlags());
} // testQueryLinear

// ----------------------------------------------------------------------
// Check query values.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(const double* queryData,
						  const int* queryErrFlags) const
{ // _checkQuery
  CPPUNIT_ASSERT(0 != queryData);
  CPPUNIT_ASSERT(0 != _pDB);

  const int numVals = _numVals();
  
  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = _names()[i];
  _pDB->queryVals(valNames, numVals);
  
  double* vals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int numQueries = _numQueries();
  const int locSize = 3+numVals;
  spatialdata::geocoords::CSCart csCart;
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* qCoords = &queryData[iQuery*locSize];
    const double* qVals = &queryData[iQuery*locSize+3];
    const int err = _pDB->query(vals, numVals, 
				qCoords[0], qCoords[1], qCoords[2], &csCart);
    if (0 != queryErrFlags)
      CPPUNIT_ASSERT(err == queryErrFlags[iQuery]);
    else
      CPPUNIT_ASSERT(0 == err);
    for (int iVal=0; iVal < numVals; ++iVal)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[iVal]/qVals[numVals-iVal-1],
				   tolerance);
  } // for
  delete[] vals; vals = 0;
} // CheckQuery

// version
// $Id$

// End of file 
