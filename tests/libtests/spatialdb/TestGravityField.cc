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

#include "spatialdata/spatialdb/GravityField.hh" // USES GravityField

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

#include <math.h> // USES sqrt()

// ----------------------------------------------------------------------
// Setup test data.
void
spatialdata::spatialdb::TestGravityField::setUp(void) {
    _data = NULL;
} // setUp


// ----------------------------------------------------------------------
// Destroy test data.
void
spatialdata::spatialdb::TestGravityField::tearDown(void) {
    delete _data;_data = NULL;
} // tearDown


// ----------------------------------------------------------------------
// Test constructor.
void
spatialdata::spatialdb::TestGravityField::testConstructor(void) {
    GravityField db;

    const size_t numValues = 3;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default query size.", size_t(numValues), db._querySize);
    for (size_t i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in default query values.", i, db._queryValues[i]);
    } // for
} // testConstructor


// ----------------------------------------------------------------------
// Test accessors.
void
spatialdata::spatialdb::TestGravityField::testAccessors(void) {
    GravityField db;

    const double tolerance = 1.0e-06;

    const std::string label("database 2");
    db.setLabel(label.c_str());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in database label.", label, std::string(db.getLabel()));

    const double gravityDirDefault[3] = { 0.0, 0.0, -1.0 };
    for (size_t i = 0; i < 3; ++i) {
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in default gravity direction.", gravityDirDefault[i], db._gravityDir[i],
                                             tolerance);
    } // for

    const double gravityDirUser[3] = { 1.1, 2.2, 3.3 };
    const double gravityMag = 1.1 * sqrt(1.0 + 4.0 + 9.0);
    db.setGravityDir(gravityDirUser[0], gravityDirUser[1], gravityDirUser[2]);
    for (size_t i = 0; i < 3; ++i) {
        const double gravityDirE = gravityDirUser[i] / gravityMag;
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in default gravity direction.", gravityDirE, db._gravityDir[i],
                                             tolerance);
    } // for

    const double gravityAccDefault = 9.80665;
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in default gravitational acceleration.",
                                         gravityAccDefault, db._acceleration, tolerance);

    const double gravityAccUser = 4.5;
    db.setGravityAcc(gravityAccUser);
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in default gravitational acceleration.",
                                         gravityAccUser, db._acceleration, tolerance);
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
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in number of values.", numValuesE, numValues);

    for (size_t i = 0; i < numValues; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in names of values.",
                                     std::string(valueNamesE[i]), std::string(valueNames[i]));
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

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query size.", querySize, db._querySize);
    for (size_t i = 0; i < querySize; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in query indices.", queryVals[i], db._queryValues[i]);
    } // for
} // testQueryVals


// ----------------------------------------------------------------------
// Test query().
void
spatialdata::spatialdb::TestGravityField::testQuery(void) {
    CPPUNIT_ASSERT(_data);

    GravityField db;

    const size_t spaceDim = _data->cs->getSpaceDim();
    if (_data->gravityDir) {
        db.setGravityDir(_data->gravityDir[0], _data->gravityDir[1], spaceDim > 2 ? _data->gravityDir[2] : 0.0);
    } // if
    db.setGravityAcc(_data->gravityAcc);

    db.open();
    const size_t querySize = _data->querySize;
    CPPUNIT_ASSERT(_data->cs);
    db.setQueryValues(_data->queryNames, querySize);

    double* gravity = (querySize > 0) ? new double[querySize] : NULL;
    for (size_t iPt = 0; iPt < _data->numPoints; ++iPt) {
        const int err = db.query(gravity, querySize, &_data->coordinates[iPt*spaceDim], spaceDim, _data->cs);
        CPPUNIT_ASSERT_MESSAGE("Expected return value of 0 for query.", !err);
        const double tolerance = 1.0e-06;
        for (size_t iDim = 0; iDim < querySize; ++iDim) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in gravity field value.",
                                                 _data->gravity[iPt*querySize+iDim], gravity[iDim], tolerance);
        } // for
    } // for
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
