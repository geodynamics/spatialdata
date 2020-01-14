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

#include "UniformDB.hh" // Implementation of class methods

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "spatialdata/units/Parser.hh" // USES Parser

#include <vector> // USES std::vector
#include <stdexcept> // USES std::runtime_error

#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::UniformDB::UniformDB(void) :
    _names(NULL),
    _values(NULL),
    _queryVals(NULL),
    _numValues(0),
    _querySize(0)
{}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::UniformDB::UniformDB(const char* label) :
    SpatialDB(label),
    _names(NULL),
    _values(NULL),
    _queryVals(NULL),
    _numValues(0),
    _querySize(0)
{}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::UniformDB::~UniformDB(void) { // destructor
    delete[] _names;_names = NULL;
    delete[] _values;_values = NULL;
    delete[] _queryVals;_queryVals = NULL;
    _numValues = 0;
    _querySize = 0;
} // destructor


// ----------------------------------------------------------------------
// Set values in database.
void
spatialdata::spatialdb::UniformDB::setData(const char* const* names,
                                           const char* const* units,
                                           const double* values,
                                           const size_t numValues) {
    assert( (0 < numValues && names && units && values) ||
            (0 == numValues && !names && !units && !values) );

    // clear out old data
    delete[] _names;_names = NULL;
    delete[] _values;_values = NULL;
    _numValues = numValues;

    spatialdata::units::Parser parser;

    if (0 < numValues) {
        _names = new std::string[numValues];
        for (size_t i = 0; i < numValues; ++i) {
            _names[i] = names[i];
        } // for

        std::vector<double> scales(numValues);
        for (size_t i = 0; i < numValues; ++i) {
            if (strcasecmp(units[i], "none") != 0) {
                scales[i] = parser.parse(units[i]);
            } else {
                scales[i] = 1.0;
            } // if/else
        } // for

        _values = new double[numValues];
        for (size_t i = 0; i < numValues; ++i) {
            _values[i] = values[i]*scales[i];
        } // for
    } // if
} // setData


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::UniformDB::queryVals(const char* const* names,
                                             const size_t numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg
            << "Number of values for query in spatial database " << label()
            << "\n must be positive.\n";
        throw std::runtime_error(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryVals;_queryVals = new size_t[numVals];
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        size_t iName = 0;
        while (iName < _numValues) {
            if (0 == strcasecmp(names[iVal], _names[iName].c_str())) {
                break;
            }
            ++iName;
        } // while
        if (iName >= _numValues) {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << label() << "'. Available values are:";
            for (size_t iName = 0; iName < _numValues; ++iName) {
                msg << "\n  " << _names[iName];
                msg << "\n";
                throw std::runtime_error(msg.str());
            } // for
        } // if
        _queryVals[iVal] = iName;
    } // for
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::UniformDB::query(double* vals,
                                         const size_t numVals,
                                         const double* coords,
                                         const size_t numDims,
                                         const spatialdata::geocoords::CoordSys* pCSQuery) {
    if (0 == _querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << label() << "\n"
            << "have not been set. Please call queryVals() before query().\n";
        throw std::runtime_error(msg.str());
    } // if
    else if (numVals != _querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << label() << "\n"
            << "(" << _querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::runtime_error(msg.str());
    } // if

    for (size_t iVal = 0; iVal < _querySize; ++iVal) {
        vals[iVal] = _values[_queryVals[iVal]];
    } // for

    return 0;
} // query


// End of file
