// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleIOAscii.hh" // Implementation of class methods

#include "spatialdata/spatialdb/SimpleDB.hh" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleIO.hh" // USES SimpleIOAscii
#include "spatialdata/spatialdb/SimpleIOAscii.hh" // USES SimpleIOAscii

#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "spatialdata/spatialdb/SimpleDBData.hh" // USES SimpleDBData

#include <string.h> // USES strcmp()
#include <sstream> // USES std::ostringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleIOAscii );

// ----------------------------------------------------------------------
// Test filename(), write(), read().
void
spatialdata::spatialdb::TestSimpleIOAscii::testIO(void)
{ // testIO
  const double coords[] = { 0.6, 0.1, 0.2,
			    1.0, 1.1, 1.2,
			    4.7, 9.5, 8.7,
			    3.4, 0.7, 9.8,
			    3.4, 9.8, 5.7};
  const double data[] = { 6.6, 3.4,
			  5.5, 6.7,
			  2.3, 4.1,
			  5.7, 2.0,
			  6.3, 6.7};
  const int spaceDim = 3;
  const int numLocs = 5;
  const int numVals = 2;
  const int dataDim = 3;
  const char* names[] = { "One", "Two" };
  const char* units[] = { "m", "m" };

  SimpleDBData dbOut;
  dbOut.allocate(numLocs, numVals, spaceDim, dataDim);
  dbOut.data(data, numLocs, numVals);
  dbOut.coordinates(coords, numLocs, spaceDim);
  dbOut.names(names, numVals);
  dbOut.units(units, numVals);

  geocoords::CSCart csOut;

  const char* filename = "data/spatial.dat";
  SimpleIOAscii dbIO;
  dbIO.filename(filename);
  dbIO.write(dbOut, &csOut);

  SimpleDBData dbIn;
  geocoords::CoordSys* pCSIn = 0;
  dbIO.read(&dbIn, &pCSIn);

  CPPUNIT_ASSERT_EQUAL(numLocs, dbIn.numLocs());
  CPPUNIT_ASSERT_EQUAL(numVals, dbIn.numValues());
  CPPUNIT_ASSERT_EQUAL(dataDim, dbIn.dataDim());
  CPPUNIT_ASSERT_EQUAL(spaceDim, dbIn.spaceDim());
  for (int iVal=0; iVal < numVals; ++iVal) {
    CPPUNIT_ASSERT_EQUAL(std::string(names[iVal]),
			 std::string(dbIn.name(iVal)));
    CPPUNIT_ASSERT_EQUAL(std::string(units[iVal]),
			 std::string(dbIn.units(iVal)));
  } // for

  const double tolerance = 1.0e-06;
  for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
    const double* coordinates = dbIn.coordinates(iLoc);
    for (int iDim=0; iDim < spaceDim; ++iDim, ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(coordinates[iDim]/coords[i], 1.0,
				 tolerance);
  } // for

  for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
    const double* values = dbIn.data(iLoc);
    for (int iVal=0; iVal < numVals; ++iVal, ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(values[iVal]/data[i], 1.0,
				 tolerance);
  } // for

  delete pCSIn; pCSIn = 0;
} // testIO

// ----------------------------------------------------------------------
// Test filename(), read() with spatial database file that contains
// comments.
void
spatialdata::spatialdb::TestSimpleIOAscii::testReadComments(void)
{ // testReadComments
  const double coords[] = { 0.6, 0.1, 0.2,
			    1.0, 1.1, 1.2,
			    4.7, 9.5, 8.7,
			    3.4, 0.7, 9.8,
			    3.4, 9.8, 5.7};
  const double data[] = { 6.6, 3.4,
			  5.5, 6.7,
			  2.3, 4.1,
			  5.7, 2.0,
			  6.3, 6.7};
  const int spaceDim = 3;
  const int numLocs = 5;
  const int numVals = 2;
  const int dataDim = 3;
  const char* names[] = { "One", "Two" };
  const char* units[] = { "m", "m" };

  const char* filename = "data/spatial_comments.dat";
  SimpleIOAscii dbIO;
  dbIO.filename(filename);

  SimpleDBData dbIn;
  geocoords::CoordSys* pCSIn = 0;
  dbIO.read(&dbIn, &pCSIn);

  CPPUNIT_ASSERT_EQUAL(numLocs, dbIn.numLocs());
  CPPUNIT_ASSERT_EQUAL(numVals, dbIn.numValues());
  CPPUNIT_ASSERT_EQUAL(dataDim, dbIn.dataDim());
  CPPUNIT_ASSERT_EQUAL(spaceDim, dbIn.spaceDim());
  for (int iVal=0; iVal < numVals; ++iVal) {
    CPPUNIT_ASSERT_EQUAL(std::string(names[iVal]),
			 std::string(dbIn.name(iVal)));
    CPPUNIT_ASSERT_EQUAL(std::string(units[iVal]),
			 std::string(dbIn.units(iVal)));
  } // for

  const double tolerance = 1.0e-06;
  for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
    const double* coordinates = dbIn.coordinates(iLoc);
    for (int iDim=0; iDim < spaceDim; ++iDim, ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(coordinates[iDim]/coords[i], 1.0,
				 tolerance);
  } // for

  for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
    const double* values = dbIn.data(iLoc);
    for (int iVal=0; iVal < numVals; ++iVal, ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(values[iVal]/data[i], 1.0,
				 tolerance);
  } // for

  delete pCSIn; pCSIn = 0;
} // testReadComments


// End of file 
