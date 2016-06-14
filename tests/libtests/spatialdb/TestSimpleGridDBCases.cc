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

#include "TestSimpleGridDBCases.hh" // Implementation of class methods

#include "data/SimpleGridDBTestDataLine1D.hh"
#include "data/SimpleGridDBTestDataLine2D.hh"
#include "data/SimpleGridDBTestDataLine3D.hh"
#include "data/SimpleGridDBTestDataArea2D.hh"
#include "data/SimpleGridDBTestDataArea3D.hh"
#include "data/SimpleGridDBTestDataVolume3D.hh"

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBLine1D );
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBLine2D );
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBLine3D );
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBArea2D );
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBArea3D );
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::spatialdb::TestSimpleGridDBVolume3D );

// ----------------------------------------------------------------------
// Setup for 1-D line.
void
spatialdata::spatialdb::TestSimpleGridDBLine1D::setUp(void)
{ // setUp
  _data = new SimpleGridDBTestDataLine1D;
} // setUp

// ----------------------------------------------------------------------
// Setup for 2-D line.
void
spatialdata::spatialdb::TestSimpleGridDBLine2D::setUp(void)
{ // setUp
  _data = new SimpleGridDBTestDataLine2D;
} // setUp

// ----------------------------------------------------------------------
// Setup for 3-D line.
void
spatialdata::spatialdb::TestSimpleGridDBLine3D::setUp(void)
{ // setUp
  _data = new SimpleGridDBTestDataLine3D;
} // setUp

// ----------------------------------------------------------------------
// Setup for 2-D area.
void
spatialdata::spatialdb::TestSimpleGridDBArea2D::setUp(void)
{ // setUp
  _data = new SimpleGridDBTestDataArea2D;
} // setUp

// ----------------------------------------------------------------------
// Setup for 3-D area.
void
spatialdata::spatialdb::TestSimpleGridDBArea3D::setUp(void)
{ // setUp
  _data = new SimpleGridDBTestDataArea3D;
} // setUp

// ----------------------------------------------------------------------
// Setup for 3-D volume.
void
spatialdata::spatialdb::TestSimpleGridDBVolume3D::setUp(void)
{ // setUp
  _data = new SimpleGridDBTestDataVolume3D;
} // setUp


// End of file 
