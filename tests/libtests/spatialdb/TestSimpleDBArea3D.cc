// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleDBArea3D.hh" // Implementation of class methods

#include "data/SimpleDBTestDataArea3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleDBArea3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleDBArea3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleDBTestDataArea3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleDBArea3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleDBTestDataArea3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
