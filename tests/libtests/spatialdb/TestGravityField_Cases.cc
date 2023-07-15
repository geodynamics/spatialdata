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

#include "TestGravityField.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include "catch2/catch_test_macros.hpp"

#include <cmath> // USES sqrt()

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestGravityField_Cases;
    } // spatialdb
} // spatialdata

class spatialdata::spatialdb::TestGravityField_Cases {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    // Factories
    static
    TestGravityField_Data* Cart2D(void);

    static
    TestGravityField_Data* Cart3D(void);

    static
    TestGravityField_Data* Geo(void);

    static
    TestGravityField_Data* GeoProj(void);

    static
    TestGravityField_Data* Geocentric(void);

}; // class TestGravity

// ------------------------------------------------------------------------------------------------
// Static test cases
TEST_CASE("TestGravityField::testConstructor", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField::testConstructor();
}
TEST_CASE("TestGravityField::testAccessors", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField::testAccessors();
}
TEST_CASE("TestGravityField::testGetNamesDBValues", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField::testGetNamesDBValues();
}
TEST_CASE("TestGravityField::testQueryVals", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField::testQueryVals();
}

// Data test cases
TEST_CASE("TestGravityField::Cart2D::testQuery", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField(spatialdata::spatialdb::TestGravityField_Cases::Cart2D()).testQuery();
}
TEST_CASE("TestGravityField::Cart3D::testQuery", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField(spatialdata::spatialdb::TestGravityField_Cases::Cart3D()).testQuery();
}
TEST_CASE("TestGravityField::Geo::testQuery", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField(spatialdata::spatialdb::TestGravityField_Cases::Geo()).testQuery();
}
TEST_CASE("TestGravityField::GeoProj::testQuery", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField(spatialdata::spatialdb::TestGravityField_Cases::GeoProj()).testQuery();
}
TEST_CASE("TestGravityField::Geocentric::testQuery", "[TestGravityField]") {
    spatialdata::spatialdb::TestGravityField(spatialdata::spatialdb::TestGravityField_Cases::Geocentric()).testQuery();
}

// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestGravityField_Data*
spatialdata::spatialdb::TestGravityField_Cases::Cart2D(void) {
    TestGravityField_Data* data = new TestGravityField_Data;assert(data);

    data->cs = new spatialdata::geocoords::CSCart();assert(data->cs);
    data->cs->setSpaceDim(2);

    data->gravityAcc = 2.0;
    static const double gravityDir[2] = { +0.6, -0.8 };
    data->gravityDir = gravityDir;

    data->numPoints = 1;
    data->querySize = 2;

    static const double coordinates[2] = { 2.5, 6.3 };
    data->coordinates = coordinates;

    static const double gravity[2] = { +1.2, -1.6 };
    data->gravity = gravity;

    return data;
} // Cart2D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestGravityField_Data*
spatialdata::spatialdb::TestGravityField_Cases::Cart3D(void) {
    TestGravityField_Data* data = new TestGravityField_Data;assert(data);

    data->cs = new spatialdata::geocoords::CSCart();assert(data->cs);
    data->cs->setSpaceDim(3);

    data->gravityAcc = 2.0;

    static const double gravityDir[3] = { +0.3, +0.4, -0.5 };
    data->gravityDir = gravityDir;

    data->numPoints = 1;
    data->querySize = 3;

    static const double coordinates[3] = { 2.5, 6.3, -2.4 };
    data->coordinates = coordinates;

    static const double gravity[3] = {
        +0.6 / sqrt(0.5),
        +0.8 / sqrt(0.5),
        -1.0 / sqrt(0.5),
    };
    data->gravity = gravity;

    return data;
} // Cart3D


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestGravityField_Data*
spatialdata::spatialdb::TestGravityField_Cases::Geo(void) {
    TestGravityField_Data* data = new TestGravityField_Data;assert(data);

    spatialdata::geocoords::CSGeo* cs = new spatialdata::geocoords::CSGeo();assert(cs);
    cs->setString("EPSG:4326"); // WGS84
    cs->setSpaceDim(3);
    data->cs = cs;

    data->gravityAcc = 2.0;

    static const double gravityDir[3] = { 0.0, 0.0, -1.0 };
    data->gravityDir = gravityDir;

    data->numPoints = 1;
    data->querySize = 3;

    static const double coordinates[3] = { 2.5, 6.3, -2.4 };
    data->coordinates = coordinates;

    static const double gravity[3] = { 0.0, 0.0, -2.0 };
    data->gravity = gravity;

    return data;
} // Geo


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestGravityField_Data*
spatialdata::spatialdb::TestGravityField_Cases::GeoProj(void) {
    TestGravityField_Data* data = new TestGravityField_Data;assert(data);

    spatialdata::geocoords::CSGeo* cs = new spatialdata::geocoords::CSGeo();assert(cs);
    cs->setString("EPSG:3310"); // California AEA
    cs->setSpaceDim(3);
    data->cs = cs;

    data->gravityAcc = 2.0;

    static const double gravityDir[3] = { 0.0, 0.0, -1.0 };
    data->gravityDir = gravityDir;

    data->numPoints = 1;
    data->querySize = 3;

    static const double coordinates[3] = { 2.5, 6.3, -2.4 };
    data->coordinates = coordinates;

    static const double gravity[3] = { 0.0, 0.0, -2.0 };
    data->gravity = gravity;

    return data;
} // GeoProj


// ------------------------------------------------------------------------------------------------
spatialdata::spatialdb::TestGravityField_Data*
spatialdata::spatialdb::TestGravityField_Cases::Geocentric(void) {
    TestGravityField_Data* data = new TestGravityField_Data;assert(data);

    spatialdata::geocoords::CSGeo* cs = new spatialdata::geocoords::CSGeo();assert(cs);
    cs->setString("EPSG:4978"); // ECEF geocentric
    cs->setSpaceDim(3);
    data->cs = cs;

    const double gacc = 2.0;
    data->gravityAcc = gacc;

    data->numPoints = 5;
    data->querySize = 3;

    static const double coordinates[5*3] = {
        0.0, 0.0, 6356752.31, // (lon=0.0, lat=90.0)
        6378137.00, 0.0, 0.0, // (lon=0.0, lat=0.0)
        0.0, -6378137.00, 0.0, // (lon=-90.0, lat=0.0)
        -2684785.48, -4296554.90, 3861564.10, // (lon=-122.0, lat=37.5)
        -2680581.35, -4289826.89, 3855476.48, // (lon=-122.0, lat=37.5, elev=-10km)
    };
    data->coordinates = coordinates;

    static const double gravity[5*3] = {
        0.0, 0.0, -gacc,
        -gacc, 0.0, 0.0,
        0.0, gacc, 0.0,
        +0.4204132183640867*gacc, +0.6728017898133232*gacc, -0.6087614290087207*gacc,
        +0.4204132183640867*gacc, +0.6728017898133232*gacc, -0.6087614290087207*gacc,
    };
    data->gravity = gravity;

    return data;
} // Geocentric


// End of file
