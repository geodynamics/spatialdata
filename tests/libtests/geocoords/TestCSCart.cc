// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <sstream> // USES std::stringstream

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace geocoords {
        class TestCSCart;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestCSCart {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    // Test constructor
    static
    void testConstructor(void);

    // Test accessors.
    static
    void testAccessors(void);

    // Test pickle() & unpickle()
    static
    void testPickle(void);

}; // class TestCSCart

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestCSCart::testConstructor", "[TestCSCart]") {
    spatialdata::geocoords::TestCSCart::testConstructor();
}
TEST_CASE("TestCSCart::testAccessors", "[TestCSCart]") {
    spatialdata::geocoords::TestCSCart::testAccessors();
}
TEST_CASE("TestCSCart::testPickle", "[TestCSCart]") {
    spatialdata::geocoords::TestCSCart::testPickle();
}

// ------------------------------------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSCart::testConstructor(void) {
    CSCart cs;
    CHECK(1.0 == cs.getToMeters());
    CHECK(CoordSys::CARTESIAN == cs.getCSType());

    cs.setSpaceDim(2);
    CoordSys* csClone = cs.clone();assert(csClone);
    CHECK(cs.getSpaceDim() == csClone->getSpaceDim());
    delete csClone;csClone = NULL;
} // testConstructor


// ------------------------------------------------------------------------------------------------
// Test accessors
void
spatialdata::geocoords::TestCSCart::testAccessors(void) {
    const double toMeters = 3.2;
    const size_t spaceDim = 2;

    CSCart cs;
    cs.setToMeters(toMeters);
    cs.setSpaceDim(spaceDim);

    const double tolerance = 1.0e-6;
    CHECK_THAT(cs.getToMeters(), Catch::Matchers::WithinAbs(toMeters, tolerance));
    CHECK(spaceDim == cs.getSpaceDim());
} // testAccessors


// ------------------------------------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSCart::testPickle(void) {
    const double toMeters = 5.4;
    const size_t spaceDim = 2;

    CSCart csA;
    csA.setToMeters(toMeters);
    csA.setSpaceDim(spaceDim);

    std::stringstream s;
    csA.pickle(s);

    CSCart csB;
    csB.unpickle(s);

    const double tolerance = 1.0e-6;
    CHECK_THAT(csB.getToMeters(), Catch::Matchers::WithinAbs(toMeters, tolerance));
    CHECK(spaceDim == csB.getSpaceDim());
} // testPickle


// End of file
