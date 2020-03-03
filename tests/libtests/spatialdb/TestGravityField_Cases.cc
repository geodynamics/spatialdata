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

#include "TestGravityField.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo

#include <cmath> // USES sqrt()

// ---------------------------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class TestGravityField_Cart2D;
        class TestGravityField_Cart3D;
        class TestGravityField_Geo;
        class TestGravityField_GeoProj;
        class TestGravityField_Geocentric;
    } // spatialdb
} // spatialdata

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField_Cart2D : public TestGravityField {
    CPPUNIT_TEST_SUB_SUITE(TestGravityField_Cart2D, TestGravityField);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestGravityField::setUp();

        delete _data;_data = new TestGravityField_Data;CPPUNIT_ASSERT(_data);
        _data->cs = new spatialdata::geocoords::CSCart();CPPUNIT_ASSERT(_data->cs);
        _data->cs->setSpaceDim(2);

        _data->gravityAcc = 2.0;
        static const double gravityDir[2] = { +0.6, -0.8 };
        _data->gravityDir = gravityDir;

        _data->numPoints = 1;
        _data->querySize = 2;

        static const double coordinates[2] = { 2.5, 6.3 };
        _data->coordinates = coordinates;

        static const double gravity[2] = { +1.2, -1.6 };
        _data->gravity = gravity;
    } // Setup

}; // TestGravityField_Cart2D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestGravityField_Cart2D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField_Cart3D : public TestGravityField {
    CPPUNIT_TEST_SUB_SUITE(TestGravityField_Cart3D, TestGravityField);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestGravityField::setUp();

        delete _data;_data = new TestGravityField_Data;CPPUNIT_ASSERT(_data);
        _data->cs = new spatialdata::geocoords::CSCart();CPPUNIT_ASSERT(_data->cs);
        _data->cs->setSpaceDim(3);

        _data->gravityAcc = 2.0;

        static const double gravityDir[3] = { +0.3, +0.4, -0.5 };
        _data->gravityDir = gravityDir;

        _data->numPoints = 1;
        _data->querySize = 3;

        static const double coordinates[3] = { 2.5, 6.3, -2.4 };
        _data->coordinates = coordinates;

        static const double gravity[3] = {
            +0.6 / sqrt(0.5),
            +0.8 / sqrt(0.5),
            -1.0 / sqrt(0.5),
        };
        _data->gravity = gravity;
    } // Setup

}; // TestGravityField_Cart3D
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestGravityField_Cart3D);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField_Geo : public TestGravityField {
    CPPUNIT_TEST_SUB_SUITE(TestGravityField_Geo, TestGravityField);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestGravityField::setUp();

        delete _data;_data = new TestGravityField_Data;CPPUNIT_ASSERT(_data);
        spatialdata::geocoords::CSGeo* cs = new spatialdata::geocoords::CSGeo();CPPUNIT_ASSERT(cs);
        cs->setString("EPSG:4326"); // WGS84
        cs->setSpaceDim(3);
        _data->cs = cs;

        _data->gravityAcc = 2.0;

        static const double gravityDir[3] = { 0.0, 0.0, -1.0 };
        _data->gravityDir = gravityDir;

        _data->numPoints = 1;
        _data->querySize = 3;

        static const double coordinates[3] = { 2.5, 6.3, -2.4 };
        _data->coordinates = coordinates;

        static const double gravity[3] = { 0.0, 0.0, -2.0 };
        _data->gravity = gravity;
    } // Setup

}; // TestGravityField_Geo
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestGravityField_Geo);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField_GeoProj : public TestGravityField {
    CPPUNIT_TEST_SUB_SUITE(TestGravityField_GeoProj, TestGravityField);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestGravityField::setUp();

        delete _data;_data = new TestGravityField_Data;CPPUNIT_ASSERT(_data);
        spatialdata::geocoords::CSGeo* cs = new spatialdata::geocoords::CSGeo();CPPUNIT_ASSERT(cs);
        cs->setString("EPSG:3310"); // California AEA
        cs->setSpaceDim(3);
        _data->cs = cs;

        _data->gravityAcc = 2.0;

        static const double gravityDir[3] = { 0.0, 0.0, -1.0 };
        _data->gravityDir = gravityDir;

        _data->numPoints = 1;
        _data->querySize = 3;

        static const double coordinates[3] = { 2.5, 6.3, -2.4 };
        _data->coordinates = coordinates;

        static const double gravity[3] = { 0.0, 0.0, -2.0 };
        _data->gravity = gravity;
    } // Setup

}; // TestGravityField_GeoProj
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestGravityField_GeoProj);

// ---------------------------------------------------------------------------------------------------------------------
class spatialdata::spatialdb::TestGravityField_Geocentric : public TestGravityField {
    CPPUNIT_TEST_SUB_SUITE(TestGravityField_Geocentric, TestGravityField);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestGravityField::setUp();

        delete _data;_data = new TestGravityField_Data;CPPUNIT_ASSERT(_data);
        spatialdata::geocoords::CSGeo* cs = new spatialdata::geocoords::CSGeo();CPPUNIT_ASSERT(cs);
        cs->setString("EPSG:4978"); // ECEF geocentric
        cs->setSpaceDim(3);
        _data->cs = cs;

        const double gacc = 2.0;
        _data->gravityAcc = gacc;

        _data->numPoints = 5;
        _data->querySize = 3;

        static const double coordinates[5*3] = {
            0.0, 0.0, 6356752.31, // (lon=0.0, lat=90.0)
            6378137.00, 0.0, 0.0, // (lon=0.0, lat=0.0)
            0.0, -6378137.00, 0.0, // (lon=-90.0, lat=0.0)
            -2684785.48, -4296554.90, 3861564.10, // (lon=-122.0, lat=37.5)
            -2680581.35, -4289826.89, 3855476.48, // (lon=-122.0, lat=37.5, elev=-10km)
        };
        _data->coordinates = coordinates;

        static const double gravity[5*3] = {
            0.0, 0.0, -gacc,
            -gacc, 0.0, 0.0,
            0.0, gacc, 0.0,
            +0.4204132183640867*gacc, +0.6728017898133232*gacc, -0.6087614290087207*gacc,
            +0.4204132183640867*gacc, +0.6728017898133232*gacc, -0.6087614290087207*gacc,
        };
        _data->gravity = gravity;
    } // Setup

}; // TestGravityField_Geocentric
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::spatialdb::TestGravityField_Geocentric);

// End of file
