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

#include "TestConverter.hh" // Implementation of class methods

#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

#include <cmath> // USES cmath()
#include <cstring> // USES memcpy()

// ---------------------------------------------------------------------------------------------------------------------
// Setup testing data.
void
spatialdata::geocoords::TestConverter::setUp(void) {
    _data = new TestConverter_Data;CPPUNIT_ASSERT(_data);
} // setUp


// ---------------------------------------------------------------------------------------------------------------------
// Tear down testing data.
void
spatialdata::geocoords::TestConverter::tearDown(void) {
    delete _data;_data = NULL;
} // tearDown


// ---------------------------------------------------------------------------------------------------------------------
// Test constructor.
void
spatialdata::geocoords::TestConverter::testConstructor(void) {
    Converter converter;

    CPPUNIT_ASSERT(converter._cache);
} // testConstructor


// ---------------------------------------------------------------------------------------------------------------------
// Teset convert().
void
spatialdata::geocoords::TestConverter::testConvert(void) {
    CPPUNIT_ASSERT(_data);

    const size_t numPoints = _data->numPoints;
    const size_t spaceDim = _data->spaceDim;
    const size_t bufferSize = numPoints * spaceDim;
    double* coords = bufferSize > 0 ? new double[bufferSize] : NULL;
    if (bufferSize > 0) {
        CPPUNIT_ASSERT(_data->coordsSrc);
        CPPUNIT_ASSERT(_data->coordsDest);
    } // if
    std::memcpy(coords, _data->coordsSrc, bufferSize*sizeof(double));

    Converter converter;
    converter.convert(coords, numPoints, spaceDim, _data->csDest, _data->csSrc);

    for (size_t i = 0; i < bufferSize; ++i) {
        const double tolerance = 1.0e-6;
        if (fabs(_data->coordsDest[i]) > tolerance) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in relative value.", 1.0, coords[i] / _data->coordsDest[i], tolerance);
        } else {
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("Mismatch in absolute value.", _data->coordsDest[i], coords[i], tolerance);
        } // if/else
    } // for

    delete[] coords;coords = NULL;
} // testConvert


// ---------------------------------------------------------------------------------------------------------------------
// Constructor
spatialdata::geocoords::TestConverter_Data::TestConverter_Data(void) :
    numPoints(0),
    spaceDim(0),
    coordsSrc(NULL),
    coordsDest(NULL),
    csSrc(NULL),
    csDest(NULL) {}


// ---------------------------------------------------------------------------------------------------------------------
// Destructor

spatialdata::geocoords::TestConverter_Data::~TestConverter_Data(void) {} // destructor
