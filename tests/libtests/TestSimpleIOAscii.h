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

#if !defined(_spatial_testsimpleioascii_h)
#define _spatial_testsimpleioascii_h

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatial package
namespace spatial {
  class TestSimpleIOAscii;
  class SimpleIOAscii; // USES SimpleIOAscii
}; // spatial

/// C++ unit testing for SimpleIO
class spatial::TestSimpleIOAscii : public CppUnit::TestFixture
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

#endif // _spatial_testsimpleioascii

// version
// $Id: TestSimpleIOAscii.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
