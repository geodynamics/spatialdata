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

/** @file tests/libtests/geocoords/TestGeoid.h
 *
 * @brief C++ TestGeoid object
 *
 * C++ unit testing for TestGeoid.
 */

#if !defined(spatialdata_geocoords_testgeoid_hh)
#define spatialdata_geocoords_testgeoid_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
  class TestGeoid;
  } // geocoords
} // spatialdata

/// C++ unit testing for Geoid
class spatialdata::geocoords::TestGeoid : public CppUnit::TestFixture
{ // class TestGeoid

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestGeoid );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testElevation );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test elevation()
  void testElevation(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _LONLAT[]; ///< Array of geographic locations
  static const double _GEOIDHT[]; ///< Array of geoid heights
  static const int _NUMLOCS; ///< Number of locations

}; // class TestGeoid

#endif // spatialdata_geocoords_testgeoid_hh

// version
// $Id$

// End of file 
