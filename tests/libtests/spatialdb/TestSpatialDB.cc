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

  const char* names[] = {"two", "one"};
  const char* units[] = {"m", "m"};
  const int numVals = 2;
  const double queryLoc[] = { 1.0, 2.0, 3.0 };
  const double vals[] = { 6.3, 4.7 };
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
    CPPUNIT_ASSERT_DOUBLES_EQUAL(valsQ[iVal]/vals[numVals-iVal-1],
				 1.0, tolerance);

  delete[] valsQ; valsQ = 0;
  _pDB->close();
} // testDB

// ----------------------------------------------------------------------
// Test SpatialDB w/C query
void
spatialdata::spatialdb::TestSpatialDB::testDB_c(void)
{ // testDB_c
  CPPUNIT_ASSERT(0 != _pDB);

  const char* names[] = {"two", "one"};
  const char* units[] = {"m", "m"};
  const int numVals = 2;
  const double queryLoc[] = { 1.0, 2.0, 3.0 };
  const int spaceDim = 3;
  const double vals[] = { 6.3, 4.7 };
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
    CPPUNIT_ASSERT_DOUBLES_EQUAL(valsQ[iVal]/vals[numVals-iVal-1],
				 1.0, tolerance);

  delete[] valsQ; valsQ = 0;
  _pDB->close();
} // testDB_c

// End of file 
