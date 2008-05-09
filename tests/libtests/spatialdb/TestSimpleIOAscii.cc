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

#include "TestSimpleIOAscii.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleIO.hh" // USES SimpleIOAscii
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii

#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "spatialdata/spatialdb/SimpleDBTypes.hh" // USES SimpleDBTypes

#include <string.h> // USES strcmp()
#include <sstream> // USES std::ostringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleIOAscii );

// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleIOAscii::testIO(void)
{ // testIO
  const double data[] = { 0.6, 0.1, 0.2,  6.6, 3.4,
			  1.0, 1.1, 1.2,  5.5, 6.7,
			  4.7, 9.5, 8.7,  2.3, 4.1,
			  3.4, 0.7, 9.8,  5.7, 2.0,
			  3.4, 9.8, 5.7,  6.3, 6.7};
  const int spaceDim = 3;
  const int numLocs = 5;
  const int numVals = 2;
  const int dataDim = 3;
  const char* names[] = { "One", "Two" };
  const char* units[] = { "m", "m" };

  SimpleDB::DataStruct dbOut;
  dbOut.data = (double*) data;
  dbOut.valNames = new std::string[numVals];
  for (int iVal=0; iVal < numVals; ++iVal)
    dbOut.valNames[iVal] = names[iVal];
  dbOut.valUnits = new std::string[numVals];
  for (int iVal=0; iVal < numVals; ++iVal)
    dbOut.valUnits[iVal] = units[iVal];
  dbOut.numLocs = numLocs;
  dbOut.numVals = numVals;
  dbOut.dataDim = dataDim;
  dbOut.spaceDim = dataDim;

  geocoords::CSCart csOut;

  const char* filename = "data/spatial.dat";
  SimpleIOAscii dbIO;
  dbIO.filename(filename);
  dbIO.write(dbOut, &csOut);

  SimpleDB::DataStruct dbIn;
  geocoords::CoordSys* pCSIn = 0;
  dbIn.data = 0;
  dbIn.valNames = 0;
  dbIn.valUnits = 0;
  dbIO.read(&dbIn, &pCSIn);

  CPPUNIT_ASSERT(numLocs == dbIn.numLocs);
  CPPUNIT_ASSERT(numVals == dbIn.numVals);
  CPPUNIT_ASSERT(dataDim == dbIn.dataDim);
  CPPUNIT_ASSERT(spaceDim == dbIn.spaceDim);
  for (int iVal=0; iVal < numVals; ++iVal) {
    CPPUNIT_ASSERT(0 == strcmp(names[iVal], dbIn.valNames[iVal].c_str()));
    CPPUNIT_ASSERT(0 == strcmp(units[iVal], dbIn.valUnits[iVal].c_str()));
  } // for
  const int dataSize = numLocs*(spaceDim+numVals);
  const double tolerance = 1.0e-06;
  for (int i=0; i < dataSize; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(dbIn.data[i]/data[i], 1.0, tolerance);

  delete[] dbOut.valNames; dbOut.valNames = 0;
  delete[] dbOut.valUnits; dbOut.valUnits = 0;
  delete[] dbIn.data; dbIn.data = 0;
  delete[] dbIn.valNames; dbIn.valNames = 0;
  delete[] dbIn.valUnits; dbIn.valUnits = 0;
  delete pCSIn; pCSIn = 0;
} // testIO

// ----------------------------------------------------------------------
// Test filename(), read() with spatial database file that contains
// comments.
void
spatialdata::spatialdb::TestSimpleIOAscii::testReadComments(void)
{ // testReadComments
  const double data[] = { 0.6, 0.1, 0.2,  6.6, 3.4,
			  1.0, 1.1, 1.2,  5.5, 6.7,
			  4.7, 9.5, 8.7,  2.3, 4.1,
			  3.4, 0.7, 9.8,  5.7, 2.0,
			  3.4, 9.8, 5.7,  6.3, 6.7};
  const int spaceDim = 3;
  const int numLocs = 5;
  const int numVals = 2;
  const int dataDim = 3;
  const char* names[] = { "One", "Two" };
  const char* units[] = { "m", "m" };

  const char* filename = "data/spatial_comments.dat";
  SimpleIOAscii dbIO;
  dbIO.filename(filename);

  SimpleDB::DataStruct dbIn;
  geocoords::CoordSys* pCSIn = 0;
  dbIn.data = 0;
  dbIn.valNames = 0;
  dbIn.valUnits = 0;
  dbIO.read(&dbIn, &pCSIn);

  CPPUNIT_ASSERT_EQUAL(numLocs, dbIn.numLocs);
  CPPUNIT_ASSERT_EQUAL(numVals, dbIn.numVals);
  CPPUNIT_ASSERT_EQUAL(dataDim, dbIn.dataDim);
  CPPUNIT_ASSERT_EQUAL(spaceDim, dbIn.spaceDim);
  for (int iVal=0; iVal < numVals; ++iVal) {
    CPPUNIT_ASSERT_EQUAL(std::string(names[iVal]),
			 std::string(dbIn.valNames[iVal].c_str()));
    CPPUNIT_ASSERT_EQUAL(std::string(units[iVal]),
			 std::string(dbIn.valUnits[iVal].c_str()));
  } // for
  const int dataSize = numLocs*(spaceDim+numVals);
  const double tolerance = 1.0e-06;
  for (int i=0; i < dataSize; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(dbIn.data[i]/data[i], 1.0, tolerance);

  delete[] dbIn.data; dbIn.data = 0;
  delete[] dbIn.valNames; dbIn.valNames = 0;
  delete[] dbIn.valUnits; dbIn.valUnits = 0;
  delete pCSIn; pCSIn = 0;
} // testReadComments


// End of file 
