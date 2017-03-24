// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/geocoords/TestCSCart.hh
 *
 * @brief C++ TestCSCart object
 *
 * C++ unit testing for CSCart.
 */

#if !defined(spatialdata_geocoords_testcscart_hh)
#define spatialdata_geocoords_testcscart_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestCSCart;
  } // geocoords
} // spatialdata

/// C++ unit testing for CSCart
class spatialdata::geocoords::TestCSCart : public CppUnit::TestFixture
{ // class TestCSCart

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestCSCart );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testToMeters );
  CPPUNIT_TEST( testSpaceDim );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testPickle );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test toMeters()
  void testToMeters(void);

  /// Test spaceDim()
  void testSpaceDim(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test pickle() & unpickle()
  void testPickle(void);

}; // class TestCSCart

#endif // spatialdata_geocoords_testcscart_hh

// version
// $Id$

// End of file 
