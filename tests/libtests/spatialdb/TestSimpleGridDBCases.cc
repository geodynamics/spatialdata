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
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleGridDBLine1D::testQueryLinear(void)
{ // testQueryLinear
  SimpleGridDBTestDataLine1D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleGridDBLine1D::testQueryNearest(void)
{ // testQueryNearest
  SimpleGridDBTestDataLine1D data;

  _testQueryNearest(data);
} // testQueryNearest


// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleGridDBLine2D::testQueryLinear(void)
{ // testQueryLinear
  SimpleGridDBTestDataLine2D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleGridDBLine2D::testQueryNearest(void)
{ // testQueryNearest
  SimpleGridDBTestDataLine2D data;

  _testQueryNearest(data);
} // testQueryNearest


// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleGridDBLine3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleGridDBTestDataLine3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleGridDBLine3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleGridDBTestDataLine3D data;

  _testQueryNearest(data);
} // testQueryNearest


// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleGridDBArea2D::testQueryLinear(void)
{ // testQueryLinear
  SimpleGridDBTestDataArea2D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleGridDBArea2D::testQueryNearest(void)
{ // testQueryNearest
  SimpleGridDBTestDataArea2D data;

  _testQueryNearest(data);
} // testQueryNearest


// ----------------------------------------------------------------------
// Test queryLinear()
void
spatialdata::spatialdb::TestSimpleGridDBArea3D::testQueryLinear(void)
{ // testQueryLinear
  SimpleGridDBTestDataArea3D data;

  _testQueryLinear(data);
} // testQueryLinear

// ----------------------------------------------------------------------
// Test queryNearest()
void
spatialdata::spatialdb::TestSimpleGridDBArea3D::testQueryNearest(void)
{ // testQueryNearest
  SimpleGridDBTestDataArea3D data;

  _testQueryNearest(data);
} // testQueryNearest


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
