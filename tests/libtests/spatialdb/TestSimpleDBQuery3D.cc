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

#include "TestSimpleDBQuery3D.hh" // Implementation of class methods

#include "data/SimpleDBQueryData3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBQuery3D );

// ----------------------------------------------------------------------
// Test queryVals()
void
spatialdata::spatialdb::TestSimpleDBQuery3D::testQueryVals(void)
{ // testQueryVals
  SimpleDBQueryData3D data;
  _testQueryVals(data);
} // testQueryVals

// ----------------------------------------------------------------------
// Test distSquared()
void
spatialdata::spatialdb::TestSimpleDBQuery3D::testDistSquared(void)
{ // testDistSquared
  SimpleDBQueryData3D data;
  _testDistSquared(data);
} // testDistSquared

// ----------------------------------------------------------------------
// Test area()
void 
spatialdata::spatialdb::TestSimpleDBQuery3D::testArea(void)
{ // testArea
  SimpleDBQueryData3D data;
  _testArea(data);
} // testArea

// ----------------------------------------------------------------------
// Test volume()
void
spatialdata::spatialdb::TestSimpleDBQuery3D::testVolume(void)
{ // testVolume
  SimpleDBQueryData3D data;
  _testVolume(data);
} // tetVolume


// End of file 
