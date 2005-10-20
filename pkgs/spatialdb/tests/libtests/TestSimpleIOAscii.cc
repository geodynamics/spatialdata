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

#include "TestSimpleIOAscii.h" // Implementation of class methods

#include "spatialdata/spatialdb/SpatialDB.h" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleDB.h" // USES SimpleDB
#include "spatialdata/spatialdb/SimpleIO.h" // USES SimpleIOAscii
#include "spatialdata/spatialdb/SimpleIOAscii.h" // USES SimpleIOAscii

#include "../../lib/SimpleDBTypes.h" // USES SimpleDBTypes

#include <sstream> // USES std::ostringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleIOAscii );

// ----------------------------------------------------------------------
// Test Filename(), Write(), Read()
void
spatialdata::spatialdb::TestSimpleIOAscii::testIO(void)
{ // testIO
  const double data[] = { 0.6, 0.1, 0.2,  6.6, 3.4,
			  1.0, 1.1, 1.2,  5.5, 6.7,
			  4.7, 9.5, 8.7,  2.3, 4.1,
			  3.4, 0.7, 9.8,  5.7, 2.0,
			  3.4, 9.8, 5.7,  6.3, 6.7};
  const int numCoords = 3;
  const int numLocs = 5;
  const int numVals = 2;
  const char* names[] = { "One", "Two" };
  const SimpleDB::TopoEnum topology = SimpleDB::VOLUME;

  SimpleDB::DataStruct dbOut;
  dbOut.Data = (double*) data;
  dbOut.ValNames = new std::string[numVals];
  for (int iVal=0; iVal < numVals; ++iVal)
    dbOut.ValNames[iVal] = names[iVal];
  dbOut.NumLocs = numLocs;
  dbOut.NumVals = numVals;
  dbOut.Topology = topology;

  const char* filename = "data/spatial.dat";
  SimpleIOAscii dbIO;
  dbIO.Filename(filename);
  dbIO.Write(dbOut);

  SimpleDB::DataStruct dbIn;
  dbIn.Data = 0;
  dbIn.ValNames = 0;
  dbIO.Read(&dbIn);

  CPPUNIT_ASSERT(numLocs == dbIn.NumLocs);
  CPPUNIT_ASSERT(numVals == dbIn.NumVals);
  CPPUNIT_ASSERT(topology == dbIn.Topology);
  for (int iVal=0; iVal < numVals; ++iVal)
    CPPUNIT_ASSERT(0 == strcmp(names[iVal], dbIn.ValNames[iVal].c_str()));
  const int dataSize = numLocs*(numCoords+numVals);
  const double tolerance = 1.0e-06;
  for (int i=0; i < dataSize; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(dbIn.Data[i]/data[i], 1.0, tolerance);

  delete[] dbOut.ValNames;
  delete[] dbIn.Data;
  delete[] dbIn.ValNames;

  std::ostringstream command;
  command << "rm " << filename;
  system(command.str().c_str());
} // testIO

// version
// $Id: TestSimpleIOAscii.cc,v 1.1 2005/05/25 18:43:06 baagaard Exp $

// End of file 
