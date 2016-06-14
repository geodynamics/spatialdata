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

/** @file tests/libtests/geocoords/TestProjector.hh
 *
 * @brief C++ TestProjector object
 *
 * C++ unit testing for TestProjector.
 */

#if !defined(spatialdata_testprojector_hh)
#define spatialdata_testprojector_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace geocoords {
    class TestProjector;
  } // geocoords
} // spatialdata

/// C++ unit testing for Projector
class spatialdata::geocoords::TestProjector : public CppUnit::TestFixture
{ // class TestProjector

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestProjector );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testCopy );
  CPPUNIT_TEST( testProjection );
  CPPUNIT_TEST( testUnits );
  CPPUNIT_TEST( testProjOptions );
  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testProject );
  CPPUNIT_TEST( testInvproject );
  CPPUNIT_TEST( testPickle );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test constructor
  void testConstructor(void);

  /// Test copy constructor
  void testCopy(void);

  /// Test projection()
  void testProjection(void);

  /// Test units()
  void testUnits(void);

  /// Test projOptions()
  void testProjOptions(void);

  /// Test initialize()
  void testInitialize(void);

  /// Test project()
  void testProject(void);

  /// Test invproject()
  void testInvproject(void);

  /// Test pickle() and unpickle()
  void testPickle(void);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  static const double _XY[]; ///< Array of projected locations
  static const double _LONLAT[]; ///< Array of geographic locations
  static const int _NUMLOCS; ///< Number of locations
  static const char* _ELLIPSOID; ///< Name of reference ellipsoid
  static const char* _DATUMHORIZ; ///< Name of horizontal datum
  static const char* _PROJECTION; ///< Name of projection
  static const char* _UNITS; ///< Units in projection
  static const char* _PROJOPTIONS; ///< Options for projection

}; // class TestProjector

#endif // spatialdata_geocoords_testprojector_hh

// version
// $Id$

// End of file 
