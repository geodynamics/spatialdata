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

#include "TestSimpleDBLine3D.hh" // Implementation of class methods

#include "data/SimpleDBDataLine3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBLine3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleDBLine3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleDBDataLine3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleDBLine3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleDBDataLine3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
