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

#include "TestSpatialDB.hh" // implementation of class methods

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB

#include "spatialdata/spatialdb/SimpleIO.hh" // USES SimpleIOAscii
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii

#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

extern "C" {
#include "testcquery.h"
}

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSpatialDB );

// ----------------------------------------------------------------------
// Setup test subject
void
spatialdata::spatialdb::TestSpatialDB::setUp(void)
{ // setUp
  SimpleDB* pDB = new SimpleDB;

  const char* filename = "data/spatialdb.dat";
  SimpleIOAscii iohandler;
  iohandler.filename(filename);
  pDB->ioHandler(&iohandler);

  _pDB = pDB;
  _pDB->open();

  pDB->queryType(SimpleDB::NEAREST);
} // setUp

// ----------------------------------------------------------------------
// Cleanup test subject
void
spatialdata::spatialdb::TestSpatialDB::tearDown(void)
{ // tearDown
  delete _pDB; _pDB = 0;
} // tearDown

// ----------------------------------------------------------------------
// Test SpatialDB
void
spatialdata::spatialdb::TestSpatialDB::testDB(void)
{ // testDB
  CPPUNIT_ASSERT(0 != _pDB);

  const char* names[] = {"two", "one", "four", "three"};
  const char* units[] = {"km", "m", "None", "MPa"};
  const int numVals = 4;
  const double queryLoc[] = { 0.6, 0.1, 0.2 };
  const double vals[] = { 6.3e+3, 4.7, 0.8, 1.2e+6 };
  const int errFlags[] = { 0 };
  const int spaceDim = 3;

  _pDB->queryVals(names, numVals);

  double* valsQ = (0 < numVals) ? new double[numVals] : 0;
  spatialdata::geocoords::CSCart csCart;
  csCart.initialize();
  const int err = _pDB->query(valsQ, numVals, queryLoc, spaceDim,
			      &csCart);
  CPPUNIT_ASSERT(err == errFlags[0]);

  const double tolerance = 1.0e-06;
  for (int iVal=0; iVal < numVals; ++iVal)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(valsQ[iVal]/vals[iVal],
				 1.0, tolerance);

  delete[] valsQ; valsQ = 0;
  _pDB->close();
} // testDB

// ----------------------------------------------------------------------
// Test SpatialDB queries w/multiple points.
void
spatialdata::spatialdb::TestSpatialDB::testDBmulti(void)
{ // testDBmulti
  CPPUNIT_ASSERT(0 != _pDB);

  const int numVals = 4;
  const int numLocs = 2;
  const int spaceDim = 3;
  const char* names[numVals] = {"two", "one", "four", "three"};
  const char* units[numVals] = {"km", "m", "None", "MPa"};
  const double queryLocs[numLocs*spaceDim] = { 
    0.6, 0.1, 0.2,
    0.1, 0.6, 0.3,
  };
  const double vals[numLocs*numVals] = { 
    6.3e+3, 4.7, 0.8, 1.2e+6,
    3.6e+3, 7.4, 8.0, 2.1e+6,
  };
  const int errFlags[numLocs] = { 0, 0 };

  _pDB->queryVals(names, numVals);

  int size = numLocs * numVals;
  double* valsQ = (0 < size) ? new double[size] : 0;
  size = numLocs;
  int* errQ = (0 < size) ? new int[size] : 0;
  		  
  spatialdata::geocoords::CSCart csCart;
  csCart.initialize();

  _pDB->multiquery(valsQ, numLocs, numVals, 
		   errQ, numLocs,
		   queryLocs, numLocs, spaceDim, &csCart);

  const double tolerance = 1.0e-06;
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    CPPUNIT_ASSERT_EQUAL(errFlags[iLoc], errQ[iLoc]);
    for (int iVal=0, index=0; iVal < numVals; ++iVal, index++)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, valsQ[index]/vals[index],
				   tolerance);
  } // for

  delete[] valsQ; valsQ = 0;
  delete[] errQ; errQ = 0;

  _pDB->close();
} // testDBmulti

// ----------------------------------------------------------------------
// Test SpatialDB w/C query
void
spatialdata::spatialdb::TestSpatialDB::testDB_c(void)
{ // testDB_c
  CPPUNIT_ASSERT(0 != _pDB);

  const char* names[] = {"two", "one"};
  const char* units[] = {"km", "m"};
  const int numVals = 2;
  const double queryLoc[] = { 0.6, 0.1, 0.2 };
  const int spaceDim = 3;
  const double vals[] = { 6.3e+3, 4.7 };
  const int errFlags[] = { 0 };

  _pDB->queryVals(names, numVals);

  double* valsQ = (0 < numVals) ? new double[numVals] : 0;
  spatialdata::geocoords::CSCart csCart;
  csCart.initialize();
  
  const int err = testcquery((void*) _pDB, valsQ, numVals, 
			     queryLoc, spaceDim,
			     (void*) &csCart);
  CPPUNIT_ASSERT(err == errFlags[0]);

  const double tolerance = 1.0e-06;
  for (int iVal=0; iVal < numVals; ++iVal)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(valsQ[iVal]/vals[iVal],
				 1.0, tolerance);

  delete[] valsQ; valsQ = 0;
  _pDB->close();
} // testDB_c

// End of file 
