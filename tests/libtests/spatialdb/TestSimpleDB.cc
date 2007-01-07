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

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB

#include "TestSimpleDB.hh" // Implementation of class methods

#include "data/SimpleDBData.hh" // USES SimpleDBData

#include "spatialdata/spatialdb/SimpleDBTypes.hh" // USES SimpleDBTypes
#include "spatialdata/spatialdb/SimpleDBQuery.hh" // USES SimpleDBQuery

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDB );

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
// Test query() using nearest neighbor
void
spatialdata::spatialdb::TestSimpleDB::_testQueryNearest(
						  const SimpleDBData& data)
{ // _testQueryNearest
  SimpleDB db;
  _setupDB(&db, data);
  db.queryType(SimpleDB::NEAREST);
  _checkQuery(db, data.names, data.queryNearest, 0,
	      data.numQueries, data.spaceDim, data.numVals);
} // _testQueryNearest

// ----------------------------------------------------------------------
// Test query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleDB::_testQueryLinear(
						  const SimpleDBData& data)
{ // _testQueryLinear
  SimpleDB db;
  _setupDB(&db, data);
  db.queryType(SimpleDB::LINEAR);
  _checkQuery(db, data.names, data.queryLinear, data.errFlags,
	      data.numQueries, data.spaceDim, data.numVals);
} // _testQueryLinear

// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleDB::_setupDB(SimpleDB* const db,
					       const SimpleDBData& data)
{ // _setupDB
  SimpleDB::DataStruct* dbData = new SimpleDB::DataStruct;

  const int numLocs = data.numLocs;
  const int spaceDim = data.spaceDim;
  const int numVals = data.numVals;
  const int dataDim = data.dataDim;

  const int size = numLocs * (spaceDim + numVals);
  CPPUNIT_ASSERT(0 < size);
  dbData->data = new double[size];
  memcpy(dbData->data, data.dbData, size*sizeof(double));

  dbData->valNames = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    dbData->valNames[i] = data.names[i];

  dbData->valUnits = new std::string[numVals];
  for (int i=0; i < numVals; ++i)
    dbData->valUnits[i] = data.units[i];

  dbData->numLocs = numLocs;
  dbData->spaceDim = spaceDim;
  dbData->numVals = numVals;
  dbData->dataDim = dataDim;

  db->_data = dbData;
  db->_query = new SimpleDBQuery(*db);
  db->_cs = new spatialdata::geocoords::CSCart();
} // _setupDB

// ----------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(SimpleDB& db,
						  char** const names,
						  const double* queryData,
						  const int* flagsE,
						  const int numQueries,
						  const int spaceDim,
						  const int numVals)
{ // _checkQuery
  CPPUNIT_ASSERT(0 != names);
  CPPUNIT_ASSERT(0 != queryData);
  CPPUNIT_ASSERT(0 != numQueries);
  CPPUNIT_ASSERT(0 != spaceDim);
  CPPUNIT_ASSERT(0 != numVals);

  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = names[i];
  db.queryVals(valNames, numVals);
  
  double* vals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int locSize = spaceDim + numVals;
  spatialdata::geocoords::CSCart csCart;
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* coords = &queryData[iQuery*locSize];
    const double* valsE = &queryData[iQuery*locSize+spaceDim];
    const int err = db.query(vals, numVals, coords, spaceDim, &csCart);
    if (0 != flagsE)
      CPPUNIT_ASSERT(err == flagsE[iQuery]);
    else
      CPPUNIT_ASSERT(0 == err);
    for (int iVal=0; iVal < numVals; ++iVal)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[iVal]/valsE[numVals-iVal-1],
				   tolerance);
  } // for
  delete[] vals; vals = 0;
} // _checkQuery

#if 0
// ----------------------------------------------------------------------
// Setup test subject
void
spatialdata::spatialdb::TestSimpleDB::setUp(void)
{ // setUp
  SimpleDB::DataStruct* pData = new SimpleDB::DataStruct;

  const int numLocs = _numLocs();
  const int spaceDim = _spaceDim();
  const int numVals = _numVals();
  const int dataDim = _dataDim();

  const int dataSize = numLocs*(spaceDim+numVals);
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
  pData->spaceDim = spaceDim;
  pData->numVals = numVals;
  pData->dataDim = _dataDim;

  _pDB = new SimpleDB;
  _pDB->_pData = pData;
  _pDB->_pQuery = new SimpleDBQuery(*_pDB);
  _pDB->_pCS = new spatialdata::geocoords::CSCart();
} // setUp

// ----------------------------------------------------------------------
// Check query values.
void
spatialdata::spatialdb::TestSimpleDB::_checkQuery(const double* queryData,
						  const int* queryErrFlags) const
{ // _checkQuery
  CPPUNIT_ASSERT(0 != queryData);
  CPPUNIT_ASSERT(0 != _pDB);

  const int numVals = _numVals();
  const int spaceDim = _spaceDim();
  
  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = _names()[i];
  _pDB->queryVals(valNames, numVals);
  
  double* vals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int numQueries = _numQueries();
  const int locSize = spaceDim+numVals;
  spatialdata::geocoords::CSCart csCart;
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* qCoords = &queryData[iQuery*locSize];
    const double* qVals = &queryData[iQuery*locSize+spaceDim];
    const int err = _pDB->query(vals, numVals, qCoords, spaceDim, &csCart);
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
#endif


// End of file 
