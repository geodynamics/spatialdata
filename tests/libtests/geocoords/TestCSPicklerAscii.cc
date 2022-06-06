// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPickleAscii

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
/// Namespace for spatialdata package
namespace spatialdata {
    namespace geocoords {
        class TestCSPicklerAscii;
    } // geocoords
} // spatialdata

/// C++ unit testing for CSCart
class spatialdata::geocoords::TestCSPicklerAscii : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestCSPicklerAscii);
    CPPUNIT_TEST(testPickleCSCart);
    CPPUNIT_TEST(testPickleCSGeo);
    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test pickle() & unpickle() for CSCart
    void testPickleCSCart(void);

    /// Test pickle() & unpickle() for CSGeo
    void testPickleCSGeo(void);

}; // class TestCSPickleAscii

CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::geocoords::TestCSPicklerAscii);

// ----------------------------------------------------------------------
// Test pickle() and unpickle() for CSCart
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSCart(void) {
    CSCart cs;

    std::stringstream s;
    s << "coord-sys = ";
    CSPicklerAscii::pickle(s, &cs);

    CoordSys* csP = NULL;
    CSPicklerAscii::unpickle(s, &csP);

    CPPUNIT_ASSERT(dynamic_cast<CSCart*>(csP));

    delete csP;csP = NULL;
} // testPickleCSCart


// ----------------------------------------------------------------------
// Test pickle() and unpickle() for CSGeo
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeo(void) {
    CSGeo cs;

    std::stringstream s;
    s << "coord-sys = ";
    CSPicklerAscii::pickle(s, &cs);

    CoordSys* csP = NULL;
    CSPicklerAscii::unpickle(s, &csP);

    CPPUNIT_ASSERT(dynamic_cast<CSGeo*>(csP));

    delete csP;csP = NULL;
} // testPickleCSGeo


// End of file
