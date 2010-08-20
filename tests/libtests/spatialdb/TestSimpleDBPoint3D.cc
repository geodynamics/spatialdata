// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleDBPoint3D.hh" // Implementation of class methods

#include "data/SimpleDBTestDataPoint3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBPoint3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleDBPoint3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleDBTestDataPoint3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleDBPoint3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleDBTestDataPoint3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
