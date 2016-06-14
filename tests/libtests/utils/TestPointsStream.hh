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

/** @file tests/libtests/utils/TestPointsStream.hh
 *
 * @brief C++ TestPointsStream object
 *
 * C++ unit testing for PointsStream.
 */

#if !defined(spatialdata_testpointsstream_hh)
#define spatialdata_testpointsstream_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace utils {
    class TestPointsStream;
  } // utils
} // spatialdata

/// C++ unit testing for PointsStream
class spatialdata::utils::TestPointsStream : public CppUnit::TestFixture
{ // class TestPointsStream

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestPointsStream );
  CPPUNIT_TEST( testCommentFlag );
  CPPUNIT_TEST( testFieldWidth );
  CPPUNIT_TEST( testPrecision );
  CPPUNIT_TEST( testWriteRead );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test commentFlag()
  void testCommentFlag(void);

  /// Test fieldWidth()
  void testFieldWidth(void);

  /// Test precision()
  void testPrecision(void);

  /// Test write()/read()
  void testWriteRead(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _POINTS[]; ///< Array of points
  static const int _NUMPTS; ///< Number of points
  static const int _NUMDIMS; ///< Number of dimensions

}; // class TestPointsStream

#endif // spatialdata_utils_testconverter_hh

// End of file 
