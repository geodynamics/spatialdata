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

/** @file tests/libtests/TestSimpleIOAscii.h
 *
 * @brief C++ TestSimpleIOAscii object
 *
 * C++ unit testing for SimpleIOAscii.
 */

#if !defined(spatialdata_testsimpleioascii_h)
#define spatialdata_testsimpleioascii_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  class TestSimpleIOAscii;
  class SimpleIOAscii; // USES SimpleIOAscii
}; // spatialdata

/// C++ unit testing for SimpleIO
class spatialdata::TestSimpleIOAscii : public CppUnit::TestFixture
{ // class TestSimpleIOAscii

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleIOAscii );
  CPPUNIT_TEST( testIO );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test Filename(), Read(), Write()
  void testIO(void);

}; // class TestSimpleIOAscii

#endif // spatialdata_testsimpleioascii

// version
// $Id: TestSimpleIOAscii.h,v 1.1 2005/05/25 18:43:06 baagaard Exp $

// End of file 
