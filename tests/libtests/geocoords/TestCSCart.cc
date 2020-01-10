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

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace geocoords {
        class TestCSCart;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestCSCart : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestCSCart);

    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAccessors);
    CPPUNIT_TEST(testPickle);

    CPPUNIT_TEST_SUITE_END();

    // Test constructor
    void testConstructor(void);

    // Test accessors.
    void testAccessors(void);

    // Test pickle() & unpickle()
    void testPickle(void);

}; // class TestCSCart

CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::geocoords::TestCSCart);

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSCart::testConstructor(void) {
    CSCart cs;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking default constructor", 1.0, cs.toMeters());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Verifying Cartesian coordinate system type", CoordSys::CARTESIAN, cs.csType());

    cs.setSpaceDim(2);
    CoordSys* csClone = cs.clone();CPPUNIT_ASSERT(csClone);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking clone", cs.spaceDim(), csClone->spaceDim());
    delete csClone;csClone = NULL;
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors
void
spatialdata::geocoords::TestCSCart::testAccessors(void) {
    const double toMeters = 3.2;
    const int spaceDim = 2;

    CSCart cs;
    cs.toMeters(toMeters);
    cs.setSpaceDim(spaceDim);

    const double tolerance = 1.0e-6;
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Checking toMeters", toMeters, cs.toMeters(), tolerance);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking dimension of coordinate system", spaceDim, cs.spaceDim());
} // testAccessors


// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSCart::testPickle(void) {
    const double toMeters = 5.4;
    const int spaceDim = 2;

    CSCart csA;
    csA.toMeters(toMeters);
    csA.setSpaceDim(spaceDim);

    std::stringstream s;
    csA.pickle(s);

    CSCart csB;
    csB.unpickle(s);

    const double tolerance = 1.0e-6;
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Checking toMeters", toMeters, csB.toMeters(), tolerance);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Checking dimension of coordinate system", spaceDim, csB.spaceDim());
} // testPickle


// End of file
