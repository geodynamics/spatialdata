// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "AnalyticDB.hh" // Implementation of class methods

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "spatialdata/units/Parser.hh" // USES Parser
#include "spatialdata/geocoords/CSCart.hh" // HASA CoordSys
#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/muparser/muParser.h" // USES mu::parser

#include <vector> // USES std::vector
#include <stdexcept> // USES std::runtime_error

#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::AnalyticDB::AnalyticDB(void) :
    _names(NULL),
    _scales(NULL),
    _expressions(NULL),
    _parsers(NULL),
    _cs(new spatialdata::geocoords::CSCart),
    _converter(new spatialdata::geocoords::Converter),
    _queryValues(NULL),
    _numValues(0),
    _querySize(0) {}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::AnalyticDB::AnalyticDB(const char* label) :
    SpatialDB(label),
    _names(NULL),
    _scales(NULL),
    _expressions(NULL),
    _parsers(NULL),
    _cs(new spatialdata::geocoords::CSCart),
    _converter(new spatialdata::geocoords::Converter),
    _queryValues(NULL),
    _numValues(0),
    _querySize(0) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::AnalyticDB::~AnalyticDB(void) {
    clear();
    delete _cs;_cs = NULL;
    delete _converter;_converter = NULL;
} // destructor


// ----------------------------------------------------------------------
/// Clear database values.
void
spatialdata::spatialdb::AnalyticDB::clear(void) {
    delete[] _names;_names = NULL;
    delete[] _scales;_scales = NULL;
    delete[] _expressions;_expressions = NULL;
    delete[] _parsers;_parsers = NULL;
    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;
    _numValues = 0;
} // destructor


// ----------------------------------------------------------------------
// Set values in database.
void
spatialdata::spatialdb::AnalyticDB::setData(const char* const* names,
                                            const char* const* units,
                                            const char* const* expressions,
                                            const size_t numValues) {
    assert( (0 < numValues && names && units && expressions) ||
            (0 == numValues && !names && !units && !expressions) );

    clear();

    if (0 == numValues) {
        return;
    } // if

    spatialdata::units::Parser parser;

    _numValues = numValues;

    _names = new std::string[_numValues];
    for (size_t i = 0; i < _numValues; ++i) {
        _names[i] = names[i];
    } // for

    _scales = new double[_numValues];
    for (size_t i = 0; i < _numValues; ++i) {
        if (strcasecmp(units[i], "none") != 0) {
            _scales[i] = parser.parse(units[i]);
        } else {
            _scales[i] = 1.0;
        } // if/else
    } // for

    _expressions = new std::string[_numValues];
    _parsers = new mu::Parser[_numValues];
    for (size_t i = 0; i < _numValues; ++i) {
        _expressions[i] = expressions[i];
        _parsers[i].SetArgSep(',');
        _parsers[i].SetDecSep('.');
        // Only allow built-in variables mupSetVarFactory(_parsers, AddVariable, NULL);
        _parsers[i].DefineConst("pi", M_PI);
        _parsers[i].DefineVar("x", &_expVars[0]);
        _parsers[i].DefineVar("y", &_expVars[1]);
        _parsers[i].DefineVar("z", &_expVars[2]);
        _parsers[i].SetExpr(_expressions[i]);
    } // for

    // Default query values is all values.
    _querySize = _numValues;
    delete[] _queryValues;_queryValues = (_querySize > 0) ? new size_t[_querySize] : NULL;
    for (size_t i = 0; i < _querySize; ++i) {
        _queryValues[i] = i;
    } // for

} // setData


// ----------------------------------------------------------------------
// Set filename containing data.
void
spatialdata::spatialdb::AnalyticDB::setCoordSys(const geocoords::CoordSys& cs) {
    delete _cs;_cs = cs.clone();assert(_cs);
} // setCoordSys


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::AnalyticDB::getNamesDBValues(const char*** valueNames,
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
spatialdata::spatialdb::AnalyticDB::setQueryValues(const char* const* names,
                                                   const size_t numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values for query in spatial database " << getDescription()
            << "\n must be positive.\n";
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryValues;_queryValues = new size_t[numVals];assert(_queryValues);
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
spatialdata::spatialdb::AnalyticDB::query(double* vals,
                                          const size_t numVals,
                                          const double* coords,
                                          const size_t numDims,
                                          const spatialdata::geocoords::CoordSys* csQuery) {
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

    // Convert coordinates
    assert(numDims <= 3);
    for (size_t d = 0; d < numDims; ++d) {
        _expVars[d] = coords[d];
    }
    assert(csQuery);
    assert(_cs);
    assert(_converter);
    _converter->convert(_expVars, 1, numDims, _cs, csQuery);

    assert(_queryValues);
    assert(_scales);
    assert(_parsers);
    try {
        for (size_t iVal = 0; iVal < _querySize; ++iVal) {
            const size_t index = _queryValues[iVal];
            vals[iVal] = _scales[index] * _parsers[index].Eval();
        } // for
    } catch (const mu::Parser::exception_type& exception) {
        throw std::runtime_error(exception.GetMsg());
    }

    return 0;
} // query


// End of file
