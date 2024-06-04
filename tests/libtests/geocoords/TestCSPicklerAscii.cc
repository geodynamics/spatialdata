// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPickleAscii

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeoLocal.hh" // USES CSGeoLocal

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <sstream> // USES std::stringstream

// ------------------------------------------------------------------------------------------------
/// Namespace for spatialdata package
namespace spatialdata {
    namespace geocoords {
        class TestCSPicklerAscii;
    } // geocoords
} // spatialdata

class spatialdata::geocoords::TestCSPicklerAscii {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test pickle() & unpickle() for CSCart
    static
    void testPickleCSCart(void);

    /// Test pickle() & unpickle() for CSGeo
    static
    void testPickleCSGeo(void);

    /// Test pickle() & unpickle() for CSGeoLocal
    static
    void testPickleCSGeoLocal(void);

}; // class TestCSPickleAscii

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestCSPicklerAscii::testPickleCSCart", "[TestCSPicklerAscii]") {
    spatialdata::geocoords::TestCSPicklerAscii::testPickleCSCart();
}
TEST_CASE("TestCSPicklerAscii::testPickleCSGeo", "[TestCSPicklerAscii]") {
    spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeo();
}
TEST_CASE("TestCSPicklerAscii::testPickleCSGeoLocal", "[TestCSPicklerAscii]") {
    spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeoLocal();
}

// ------------------------------------------------------------------------------------------------
// Test pickle() and unpickle() for CSCart
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSCart(void) {
    CSCart cs;

    std::stringstream s;
    s << "coord-sys = ";
    CSPicklerAscii::pickle(s, &cs);

    CoordSys* csP = NULL;
    CSPicklerAscii::unpickle(s, &csP);

    CHECK(dynamic_cast<CSCart*>(csP));

    delete csP;csP = NULL;
} // testPickleCSCart


// ------------------------------------------------------------------------------------------------
// Test pickle() and unpickle() for CSGeo
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeo(void) {
    CSGeo cs;

    std::stringstream s;
    s << "coord-sys = ";
    CSPicklerAscii::pickle(s, &cs);

    CoordSys* csP = NULL;
    CSPicklerAscii::unpickle(s, &csP);

    CHECK(dynamic_cast<CSGeo*>(csP));

    delete csP;csP = NULL;
} // testPickleCSGeo


// ------------------------------------------------------------------------------------------------
// Test pickle() and unpickle() for CSGeoLocal
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeoLocal(void) {
    CSGeoLocal cs;

    std::stringstream s;
    s << "coord-sys = ";
    CSPicklerAscii::pickle(s, &cs);

    CoordSys* csP = NULL;
    CSPicklerAscii::unpickle(s, &csP);

    CHECK(dynamic_cast<CSGeoLocal*>(csP));

    delete csP;csP = NULL;
} // testPickleCSGeoLocal


// End of file
