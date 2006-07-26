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

#include "TestPointsStream.hh" // Implementation of class methods

#include "spatialdata/utils/PointsStream.hh" // USES PointStream

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
// Test read()
void
spatialdata::utils::TestPointsStream::testRead(void)
{ // testRead
  std::stringstream buffer;

  //buffer << "# This is a comment\n";
  const int size = _NUMPTS * _NUMDIMS;
  for (int i=0; i < size; ++i)
    buffer << "  " << _POINTS[i];
  buffer << "\n";

  PointsStream s;
  s.input(&buffer);
  double* points = 0;
  int numPts = 0;
  int numDims = 0;
  s.read(&points, &numPts, &numDims);

  CPPUNIT_ASSERT_EQUAL(_NUMPTS, numPts);
  CPPUNIT_ASSERT_EQUAL(_NUMDIMS, numDims);
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_EQUAL(_POINTS[i], points[i]);
} // testRead

// ----------------------------------------------------------------------
// Test write()
void
spatialdata::utils::TestPointsStream::testWrite(void)
{ // testWrite
  std::stringstream buffer;

  PointsStream s;
  s.output(&buffer);
  s.write(_POINTS, _NUMPTS, _NUMDIMS);

  const int size = _NUMPTS * _NUMDIMS;
  for (int i=0; i < size; ++i) {
    double value;
    buffer >> value;
    CPPUNIT_ASSERT_EQUAL(_POINTS[i], value);
  } // for
} // testWrite

// End of file 
