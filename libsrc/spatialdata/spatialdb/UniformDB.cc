// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

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
    _queryValues(NULL),
    _numValues(0),
    _querySize(0) {}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::UniformDB::UniformDB(const char* label) :
    SpatialDB(label),
    _names(NULL),
    _values(NULL),
    _queryValues(NULL),
    _numValues(0),
    _querySize(0) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::UniformDB::~UniformDB(void) {
    delete[] _names;_names = NULL;
    delete[] _values;_values = NULL;
    delete[] _queryValues;_queryValues = NULL;
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

    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;

    spatialdata::units::Parser parser;

    if (numValues > 0) {
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

        // Default query values is all values.
        _querySize = _numValues;
        delete[] _queryValues;_queryValues = (_querySize > 0) ? new size_t[_querySize] : NULL;
        for (size_t i = 0; i < _querySize; ++i) {
            _queryValues[i] = i;
        } // for
    } // if
} // setData


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::UniformDB::getNamesDBValues(const char*** valueNames,
                                                    size_t* numValues) const {
    if (valueNames) {
        *valueNames = (_numValues > 0) ? new const char*[_numValues] : NULL;
        for (size_t i = 0; i < _numValues; ++i) {
            (*valueNames)[i] = _names[i].c_str();
        } // for
    }
    if (numValues) {
        *numValues = _numValues;
    } // if
} // getNamesDBValues


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::UniformDB::setQueryValues(const char* const* names,
                                                  const size_t numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values for query in spatial database " << getDescription()
            << "\n must be positive.\n";
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryValues;_queryValues = new size_t[numVals];
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
                << getDescription() << "'. Available values are:";
            for (size_t iName = 0; iName < _numValues; ++iName) {
                msg << "\n  " << _names[iName];
                msg << "\n";
                throw std::out_of_range(msg.str());
            } // for
        } // if
        _queryValues[iVal] = iName;
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
        msg << "Values to be returned by spatial database " << getDescription() << "\n"
            << "have not been set. Please call setQueryValues() before query().\n";
        throw std::logic_error(msg.str());
    } // if
    else if (numVals != _querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getDescription() << "\n"
            << "(" << _querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::invalid_argument(msg.str());
    } // if

    for (size_t iVal = 0; iVal < _querySize; ++iVal) {
        vals[iVal] = _values[_queryValues[iVal]];
    } // for

    return 0;
} // query


// End of file
