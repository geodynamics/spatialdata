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

#include "TestSimpleDBArea3D.hh" // Implementation of class methods

#include "data/SimpleDBDataArea3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBArea3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleDBArea3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleDBDataArea3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleDBArea3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleDBDataArea3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
