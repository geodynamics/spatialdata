// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSimpleGridDBCases.hh" // Implementation of class methods

#include "data/SimpleGridDBTestDataVolume3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBVolume3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleGridDBVolume3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleGridDBTestDataVolume3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleGridDBVolume3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleGridDBTestDataVolume3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
