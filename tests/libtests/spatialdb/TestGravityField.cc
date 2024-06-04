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

#include "TestGravityField.hh" // Implementation of class methods

#include "spatialdata/spatialdb/GravityField.hh" // USES GravityField

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES fabs()

// ----------------------------------------------------------------------
// Constructor.
spatialdata::spatialdb::TestGravityField::TestGravityField(TestGravityField_Data* data) :
    _data(data) {
    assert(_data);
} // constructor


// ----------------------------------------------------------------------
// Destructor.
spatialdata::spatialdb::TestGravityField::~TestGravityField(void) {
    delete _data;_data = NULL;
} // tearDown


// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestGravityField::testConstructor(void) {
    GravityField db;

    const size_t numValues = 3;
    REQUIRE(numValues == db._querySize);
    for (size_t i = 0; i < numValues; ++i) {
        CHECK(i == db._queryValues[i]);
    } // for
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestGravityField::testAccessors(void) {
    GravityField db;

    const double tolerance = 1.0e-06;

    const std::string description("database 2");
    db.setDescription(description.c_str());
    CHECK(description == std::string(db.getDescription()));

    const double gravityDirDefault[3] = { 0.0, 0.0, -1.0 };
    for (size_t i = 0; i < 3; ++i) {
        CHECK_THAT(db._gravityDir[i], Catch::Matchers::WithinAbs(gravityDirDefault[i], tolerance));
    } // for

    const double gravityDirUser[3] = { 1.1, 2.2, 3.3 };
    const double gravityMag = 1.1 * sqrt(1.0 + 4.0 + 9.0);
    db.setGravityDir(gravityDirUser[0], gravityDirUser[1], gravityDirUser[2]);
    for (size_t i = 0; i < 3; ++i) {
        const double gravityDirE = gravityDirUser[i] / gravityMag;
        CHECK_THAT(db._gravityDir[i], Catch::Matchers::WithinAbs(gravityDirE, tolerance));
    } // for

    const double gravityAccDefault = 9.80665;
    CHECK_THAT(db._acceleration, Catch::Matchers::WithinAbs(gravityAccDefault, tolerance));

    const double gravityAccUser = 4.5;
    db.setGravityAcc(gravityAccUser);
    CHECK_THAT(db._acceleration, Catch::Matchers::WithinAbs(gravityAccUser, tolerance));
} // testAccessors


// ----------------------------------------------------------------------
// Test getNamesDBValues().
void
spatialdata::spatialdb::TestGravityField::testGetNamesDBValues(void) {
    GravityField db;

    const size_t numValuesE = 3;
    const char* valueNamesE[numValuesE] = { "gravity_field_x", "gravity_field_y", "gravity_field_z" };

    const char** valueNames = NULL;
    size_t numValues = 0;
    db.getNamesDBValues(&valueNames, &numValues);
    REQUIRE(numValuesE == numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CHECK(std::string(valueNamesE[i]) == std::string(valueNames[i]));
    } // for
    delete[] valueNames;valueNames = NULL;
    numValues = 0;
} // testGetDBValues


// ----------------------------------------------------------------------
// Test setQueryValues().
void
spatialdata::spatialdb::TestGravityField::testQueryVals(void) {
    GravityField db;

    const size_t querySize = 2;
    const char* queryNames[2] = { "gravity_field_z", "gravity_field_y" };
    const size_t queryVals[2] = { 2, 1 };

    db.setQueryValues(queryNames, querySize);

    REQUIRE(querySize == db._querySize);
    for (size_t i = 0; i < querySize; ++i) {
        CHECK(queryVals[i] == db._queryValues[i]);
    } // for
} // testQueryVals


// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestGravityField::testQuery(void) {
    assert(_data);

    GravityField db;

    const size_t spaceDim = _data->cs->getSpaceDim();
    if (_data->gravityDir) {
        db.setGravityDir(_data->gravityDir[0], _data->gravityDir[1], spaceDim > 2 ? _data->gravityDir[2] : 0.0);
    } // if
    db.setGravityAcc(_data->gravityAcc);

    db.open();
    const size_t querySize = _data->querySize;
    assert(_data->cs);
    db.setQueryValues(_data->queryNames, querySize);

    double* gravity = (querySize > 0) ? new double[querySize] : NULL;
    for (size_t iPt = 0; iPt < _data->numPoints; ++iPt) {
        const int err = db.query(gravity, querySize, &_data->coordinates[iPt*spaceDim], spaceDim, _data->cs);
        REQUIRE(!err);
        const double tolerance = 1.0e-06;
        for (size_t iDim = 0; iDim < querySize; ++iDim) {
            const double valueE = _data->gravity[iPt*querySize+iDim];
            CHECK_THAT(gravity[iDim], Catch::Matchers::WithinAbs(valueE, tolerance));
        } // for
    } // for
    delete[] gravity;gravity = NULL;
    db.close();
} // testQuery


// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::TestGravityField_Data::TestGravityField_Data(void) :
    cs(NULL),
    gravityAcc(9.80665),
    gravityDir(NULL),
    querySize(0),
    numPoints(0),
    coordinates(NULL),
    gravity(NULL) {
    queryNames[0] = "gravity_field_x";
    queryNames[1] = "gravity_field_y";
    queryNames[2] = "gravity_field_z";
} // constructor


// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::TestGravityField_Data::~TestGravityField_Data(void) {
    delete cs;cs = NULL;
    gravityDir = NULL;
    coordinates = NULL;
    gravity = NULL;
} // destructor


// End of file
