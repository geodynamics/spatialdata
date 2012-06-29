// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleGridDB.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleGridDB.hh" // USES SimpleGridDB

#include "data/SimpleGridDBTestData.hh" // USES SimpleGridDBTestData

#include "spatialdata/geocoords/CSCart.hh" // USE CSCart

#include <string.h> // USES strcmp() and memcpy()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDB );

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::spatialdb::TestSimpleGridDB::testConstructor(void)
{ // testConstructor
  SimpleGridDB db;
} // testConstructor

// ----------------------------------------------------------------------
// Test label()
void
spatialdata::spatialdb::TestSimpleGridDB::testLabel(void)
{ // testLabel
  SimpleGridDB db;
  const char* label = "database 2";
  db.label(label);
  CPPUNIT_ASSERT(0 == strcmp(label, db.label()));
} // testLabel

// ----------------------------------------------------------------------
// Test filename()
void
spatialdata::spatialdb::TestSimpleGridDB::testFilename(void)
{ // testFilename
  SimpleGridDB db;
  const std::string& filename = "mydb.spatialdb";
  db.filename(filename.c_str());
  CPPUNIT_ASSERT_EQUAL(filename, db._filename);
} // testFilename

// ----------------------------------------------------------------------
// Test queryType()
void
spatialdata::spatialdb::TestSimpleGridDB::testQueryType(void)
{ // testQueryType
  SimpleGridDB db;

  // Test default (nearest)
  CPPUNIT_ASSERT_EQUAL(SimpleGridDB::NEAREST, db._queryType);

  db.queryType(SimpleGridDB::LINEAR);
  CPPUNIT_ASSERT_EQUAL(SimpleGridDB::LINEAR, db._queryType);
  
  db.queryType(SimpleGridDB::NEAREST);
  CPPUNIT_ASSERT_EQUAL(SimpleGridDB::NEAREST, db._queryType);
} // testQueryType

// ----------------------------------------------------------------------
// Test _search()
void
spatialdata::spatialdb::TestSimpleGridDB::testSearch(void)
{ // testSearch
  const int numX = 5;
  const double x[numX] = {
    -3.0, -1.0, 0.0, 5.0, 8.0,
  };
  const double tolerance = 1.0e-6;

  SimpleGridDB db;
  
  db.queryType(SimpleGridDB::NEAREST);

  // Test data and expected results
  const double xA = -20.0;
  const double indexA = 0.0;

  const double xB = -1.0;
  const double indexB = 1.0;

  const double xC = +3.0;
  const double indexC = 2.6;
  
  const double xD = -20.0;
  const double indexD = 0.0;

  double index = db._search(xA, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexA, index, tolerance);

  index = db._search(xB, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexB, index, tolerance);

  index = db._search(xC, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexC, index, tolerance);

  index = db._search(xD, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexD, index, tolerance);

  db.queryType(SimpleGridDB::LINEAR);

  // Test data and expected results
  const double xE = -20.0;
  const double indexE = -1.0;

  const double xF = -1.0;
  const double indexF = 1.0;

  const double xG = +3.0;
  const double indexG = 2.6;
  
  const double xH = -20.0;
  const double indexH = -1.0;

  index = db._search(xE, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexE, index, tolerance);

  index = db._search(xF, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexF, index, tolerance);

  index = db._search(xG, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexG, index, tolerance);

  index = db._search(xH, x, numX);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(indexH, index, tolerance);
} // testSearch

// ----------------------------------------------------------------------
// Test _dataIndex()
void
spatialdata::spatialdb::TestSimpleGridDB::testDataIndex(void)
{ // testDataIndex
  SimpleGridDB db;
  db._numX = 4;
  db._numY = 3;
  db._numZ = 5;
  db._numValues = 10;

  CPPUNIT_ASSERT_EQUAL(0, db._dataIndex(0, 0, 0));
  CPPUNIT_ASSERT_EQUAL(10, db._dataIndex(0, 0, 1));

  CPPUNIT_ASSERT_EQUAL(50, db._dataIndex(0, 1, 0));
  CPPUNIT_ASSERT_EQUAL(50+40, db._dataIndex(0, 1, 4));

  CPPUNIT_ASSERT_EQUAL(150, db._dataIndex(1, 0, 0));
  CPPUNIT_ASSERT_EQUAL(2*150+1*50+30, db._dataIndex(2, 1, 3));
} // testDataIndex

// ----------------------------------------------------------------------
// Test query() using nearest neighbor
void
spatialdata::spatialdb::TestSimpleGridDB::_testQueryNearest(const SimpleGridDBTestData& data)
{ // _testQueryNearest
  SimpleGridDB db;
  _setupDB(&db, data);
  db.queryType(SimpleGridDB::NEAREST);
  _checkQuery(db, data.names, data.queryNearest, 0,
	      data.numQueries, data.spaceDim, data.numVals);
} // _testQueryNearest

// ----------------------------------------------------------------------
// Test query() using linear interpolation
void
spatialdata::spatialdb::TestSimpleGridDB::_testQueryLinear(const SimpleGridDBTestData& data)
{ // _testQueryLinear
  SimpleGridDB db;
  _setupDB(&db, data);
  db.queryType(SimpleGridDB::LINEAR);
  _checkQuery(db, data.names, data.queryLinear, data.errFlags,
	      data.numQueries, data.spaceDim, data.numVals);
} // _testQueryLinear

// ----------------------------------------------------------------------
// Populate database with data.
void
spatialdata::spatialdb::TestSimpleGridDB::_setupDB(SimpleGridDB* const db,
						    const SimpleGridDBTestData& data)
{ // _setupDB
  CPPUNIT_ASSERT(db);
  CPPUNIT_ASSERT(data.numVals > 0);

  delete[] db->_x; db->_x = 0;
  delete[] db->_y; db->_y = 0;
  delete[] db->_z; db->_z = 0;
  delete[] db->_data; db->_data = 0;
  delete[] db->_names; db->_names = 0;
  delete[] db->_units; db->_units = 0;

  db->label("GeoProjGrid test database");
  db->_numValues = data.numVals;
  db->_spaceDim = data.spaceDim;
  db->_dataDim = data.dataDim;
  db->_numX = data.numX;
  db->_numY = data.numY;
  db->_numZ = data.numZ;

  int numLocs = 1;
  if (data.numX > 1) {
    numLocs *= data.numX;
    db->_x = new double[data.numX];
    for (int i=0; i < data.numX; ++i) {
      db->_x[i] = data.dbX[i];
    } // for
  } // if
  if (data.numY > 1) {
    numLocs *= data.numY;
    db->_y = new double[data.numY];
    for (int i=0; i < data.numY; ++i) {
      db->_y[i] = data.dbY[i];
    } // for
  } // if
  if (data.numZ > 1) {
    numLocs *= data.numZ;
    db->_z = new double[data.numZ];
    for (int i=0; i < data.numZ; ++i) {
      db->_z[i] = data.dbZ[i];
    } // for
  } // if

  db->_data = (numLocs > 0) ? new double[numLocs*data.numVals] : 0;
  for (int i=0; i < numLocs*data.numVals; ++i) {
    db->_data[i] = data.dbData[i];
  } // for

  db->_names = (data.numVals > 0) ? new std::string[data.numVals] : 0;
  for (int i=0; i < data.numVals; ++i) {
    db->_names[i] = data.names[i];
  } // for

  db->_units = (data.numVals > 0) ? new std::string[data.numVals] : 0;
  for (int i=0; i < data.numVals; ++i) {
    db->_units[i] = data.units[i];
  } // for

  db->_cs = new spatialdata::geocoords::CSCart();
  db->_cs->setSpaceDim(data.spaceDim);
} // _setupDB

// ----------------------------------------------------------------------
// Test query method by doing query and checking values returned.
void
spatialdata::spatialdb::TestSimpleGridDB::_checkQuery(SimpleGridDB& db,
						       char** const names,
						       const double* queryData,
						       const int* flagsE,
						       const int numQueries,
						       const int spaceDim,
						       const int numVals)
{ // _checkQuery
  CPPUNIT_ASSERT(names);
  CPPUNIT_ASSERT(queryData);
  CPPUNIT_ASSERT(numQueries);
  CPPUNIT_ASSERT(spaceDim);
  CPPUNIT_ASSERT(numVals);

  // reverse order of vals in queries
  const char* valNames[numVals];
  for (int i=0; i < numVals; ++i)
    valNames[numVals-i-1] = names[i];
  db.queryVals(valNames, numVals);
  
  double* vals = (0 < numVals) ? new double[numVals] : 0;
  const double tolerance = 1.0e-06;
  
  const int locSize = spaceDim + numVals;
  spatialdata::geocoords::CSCart csCart;
  csCart.setSpaceDim(spaceDim);
  for (int iQuery=0; iQuery < numQueries; ++iQuery) {
    const double* coords = &queryData[iQuery*locSize];
    const double* valsE = &queryData[iQuery*locSize+spaceDim];
    const int err = db.query(vals, numVals, coords, spaceDim, &csCart);
    if (0 != flagsE)
      CPPUNIT_ASSERT(err == flagsE[iQuery]);
    else {
      CPPUNIT_ASSERT(0 == err);
      for (int iVal=0; iVal < numVals; ++iVal) {
	if (valsE[numVals-iVal-1] > tolerance) {
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[iVal]/valsE[numVals-iVal-1],
				       tolerance);
	} else {
	  CPPUNIT_ASSERT_DOUBLES_EQUAL(valsE[numVals-iVal-1], vals[iVal],
				       tolerance);
	} // if/else
      } // for
    } // if/else
  } // for
  delete[] vals; vals = 0;
} // _checkQuery


// End of file 
