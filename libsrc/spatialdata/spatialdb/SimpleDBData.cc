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

#include "SimpleDBData.hh" // Implementation of class methods

#include <cstring> // USES memcpy()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream

// ----------------------------------------------------------------------
// Default constructor
spatialdata::spatialdb::SimpleDBData::SimpleDBData(void) :
    _data(NULL),
    _coordinates(NULL),
    _names(NULL),
    _units(NULL),
    _numLocs(0),
    _numValues(0),
    _dataDim(0),
    _spaceDim(0) {}


// ----------------------------------------------------------------------
// Default destructor
spatialdata::spatialdb::SimpleDBData::~SimpleDBData(void) {
    delete[] _data;_data = 0;
    delete[] _coordinates;_coordinates = 0;
    delete[] _names;_names = 0;
    delete[] _units;_units = 0;
    _numLocs = 0;
    _numValues = 0;
    _dataDim = 0;
    _spaceDim = 0;
} // destructor


// ----------------------------------------------------------------------
// Allocate data structues.
void
spatialdata::spatialdb::SimpleDBData::allocate(const size_t numLocs,
                                               const size_t numValues,
                                               const size_t spaceDim,
                                               const size_t dataDim) {
    delete[] _data;_data = 0;
    delete[] _coordinates;_coordinates = 0;
    delete[] _names;_names = 0;
    delete[] _units;_units = 0;

    if (numLocs <= 0) {
        std::ostringstream msg;
        msg << "Number of locations (" << numLocs << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    if (numValues <= 0) {
        std::ostringstream msg;
        msg << "Number of values (" << numValues << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    if (spaceDim <= 0) {
        std::ostringstream msg;
        msg << "Number of spatial dimensions (" << spaceDim << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    if (( dataDim < 0) || ( dataDim > 3) ) {
        std::ostringstream msg;
        msg << "Spatial dimension of data (" << dataDim << ") must be in the range [0,3].";
        throw std::out_of_range(msg.str());
    } // if

    size_t size = numLocs*numValues;
    _data = (size > 0) ? new double[size] : NULL;

    size = numLocs*spaceDim;
    _coordinates = (size > 0) ? new double[size] : NULL;

    size = numValues;
    _names = (size > 0) ? new std::string[size] : NULL;
    _units = (size > 0) ? new std::string[size] : NULL;

    _numLocs = numLocs;
    _numValues = numValues;
    _spaceDim = spaceDim;
    _dataDim = dataDim;
} // allocate


// ----------------------------------------------------------------------
// Set data values.
void
spatialdata::spatialdb::SimpleDBData::setData(const double* values,
                                              const size_t numLocs,
                                              const size_t numValues) {
    assert(values);
    assert(numLocs == _numLocs);
    assert(numValues == _numValues);

    memcpy(_data, values, numLocs*numValues*sizeof(double));
} // data


// ----------------------------------------------------------------------
// Set coordinates of locations.
void
spatialdata::spatialdb::SimpleDBData::setCoordinates(const double* values,
                                                     const size_t numLocs,
                                                     const size_t spaceDim) {
    assert(values);
    assert(numLocs == _numLocs);
    assert(spaceDim == _spaceDim);

    memcpy(_coordinates, values, numLocs*spaceDim*sizeof(double));
} // coordinates


// ----------------------------------------------------------------------
// Set names of values.
void
spatialdata::spatialdb::SimpleDBData::setNames(const char* const* values,
                                               const size_t numValues) {
    assert(values);
    assert(numValues == _numValues);

    for (size_t i = 0; i < numValues; ++i) {
        _names[i] = values[i];
    } // for
} // names


// ----------------------------------------------------------------------
// Set units of values.
void
spatialdata::spatialdb::SimpleDBData::setUnits(const char* const* values,
                                               const size_t numValues) {
    assert(values);
    assert(numValues == _numValues);

    for (size_t i = 0; i < numValues; ++i) {
        _units[i] = values[i];
    } // for
} // units


// End of file
