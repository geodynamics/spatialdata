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

#include "TestConverter.hh" // Implementation of class methods

#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include <cmath> // USES cmath()
#include <cstring> // USES memcpy()

// ---------------------------------------------------------------------------------------------------------------------
// Constructor.
spatialdata::geocoords::TestConverter::TestConverter(TestConverter_Data* data) : _data(data) {
    assert(_data);
} // constructor


// ---------------------------------------------------------------------------------------------------------------------
// Destructor.
spatialdata::geocoords::TestConverter::~TestConverter(void) {
    delete _data;_data = NULL;
} // destructor


// ---------------------------------------------------------------------------------------------------------------------
// Test constructor.
void
spatialdata::geocoords::TestConverter::testConstructor(void) {
    Converter converter;

    CHECK(converter._cache);
} // testConstructor


// ---------------------------------------------------------------------------------------------------------------------
// Teset convert().
void
spatialdata::geocoords::TestConverter::testConvert(void) {
    assert(_data);

    const size_t numPoints = _data->numPoints;
    const size_t spaceDim = _data->spaceDim;
    const size_t bufferSize = numPoints * spaceDim;
    double* coords = bufferSize > 0 ? new double[bufferSize] : NULL;
    if (bufferSize > 0) {
        assert(_data->coordsSrc);
        assert(_data->coordsDest);
    } // if
    std::memcpy(coords, _data->coordsSrc, bufferSize*sizeof(double));

    Converter converter;
    converter.convert(coords, numPoints, spaceDim, _data->csDest, _data->csSrc);

    const double tolerance = 1.0e-6;
    for (size_t i = 0; i < bufferSize; ++i) {
        const double toleranceV = std::max(fabs(tolerance*_data->coordsDest[i]), tolerance);
        CHECK_THAT(coords[i], Catch::Matchers::WithinAbs(_data->coordsDest[i], toleranceV));
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
