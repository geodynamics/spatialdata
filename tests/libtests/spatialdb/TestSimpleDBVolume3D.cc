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

#include "TestSimpleDBVolume3D.hh" // Implementation of class methods

#include "data/SimpleDBDataVolume3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBVolume3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleDBVolume3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleDBDataVolume3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleDBVolume3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleDBDataVolume3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
