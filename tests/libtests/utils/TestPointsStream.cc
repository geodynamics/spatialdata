// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestPointsStream.hh" // Implementation of class methods

#include "spatialdata/utils/PointsStream.hh" // USES PointStream

#include <string.h> // USES strcmp()
#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::utils::TestPointsStream );

// ----------------------------------------------------------------------
#include "data/TestPointsStream.dat"

// ----------------------------------------------------------------------
// Test commentFlag()
void
spatialdata::utils::TestPointsStream::testCommentFlag(void)
{ // testCommentFlag
  const char* flag = "%";
  PointsStream s;
  s.commentFlag(flag);
  CPPUNIT_ASSERT(0 == strcmp(flag, s.commentFlag()));
} // testCommentFlag

// ----------------------------------------------------------------------
// Test fieldWidth()
void
spatialdata::utils::TestPointsStream::testFieldWidth(void)
{ // testFieldWidth
  const int fieldWidth = 18;
  PointsStream s;
  s.fieldWidth(fieldWidth);
  CPPUNIT_ASSERT_EQUAL(fieldWidth, s.fieldWidth());
} // testFieldWidth

// ----------------------------------------------------------------------
// Test precision()
void
spatialdata::utils::TestPointsStream::testPrecision(void)
{ // testPrecision
  const int precision = 3;
  PointsStream s;
  s.precision(precision);
  CPPUNIT_ASSERT_EQUAL(precision, s.precision());
} // testPrecision

// ----------------------------------------------------------------------
// Test write() and read()
void
spatialdata::utils::TestPointsStream::testWriteRead(void)
{ // testWriteRead
  const char* filename = "data/tmp.txt";

  PointsStream s;
  s.filename(filename);
  s.write(_POINTS, _NUMPTS, _NUMDIMS);

  double* points = 0;
  int numPts = 0;
  int numDims = 0;
  s.read(&points, &numPts, &numDims);

  CPPUNIT_ASSERT_EQUAL(_NUMPTS, numPts);
  CPPUNIT_ASSERT_EQUAL(_NUMDIMS, numDims);

  const int size = _NUMPTS * _NUMDIMS;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_EQUAL(_POINTS[i], points[i]);

  delete[] points; points = 0;
} // testWriteRead

// End of file 
