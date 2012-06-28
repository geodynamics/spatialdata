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

#include "TestGeoProjGridDBVolume3D.hh" // Implementation of class methods

#include "data/GeoProjGridDBTestDataVolume3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestGeoProjGridDBVolume3D );

// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestGeoProjGridDBVolume3D::testQueryLinear(void)
{ // testQueryLinear
  GeoProjGridDBTestDataVolume3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestGeoProjGridDBVolume3D::testQueryNearest(void)
{ // testQueryNearest
  GeoProjGridDBTestDataVolume3D data;

  _testQueryNearest(data);
} // testQueryNearest


// End of file 
