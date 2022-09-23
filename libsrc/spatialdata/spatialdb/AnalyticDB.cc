// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "AnalyticDB.hh" // Implementation of class methods

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "spatialdata/units/Parser.hh" // USES Parser
#include "spatialdata/geocoords/CSCart.hh" // HASA CoordSys
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <vector> // USES std::vector
#include <stdexcept> // USES std::runtime_error

#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::AnalyticDB::AnalyticDB(void) :
    _names(NULL),
    _expressions(NULL),
    _hParser(NULL),
    _cs(new spatialdata::geocoords::CSCart),
    _converter(new spatialdata::geocoords::Converter),
    _queryValues(NULL),
    _querySize(0) {}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::AnalyticDB::AnalyticDB(const char* label) :
    SpatialDB(label),
    _names(NULL),
    _expressions(NULL),
    _hParser(NULL),
    _cs(new spatialdata::geocoords::CSCart),
    _converter(new spatialdata::geocoords::Converter),
    _queryValues(NULL),
    _querySize(0) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::AnalyticDB::~AnalyticDB(void) {
    delete[] _names;_names = NULL;
    delete[] _expressions;_expressions = NULL;
    if (_hParser) {for (size_t i = 0; i < _numExpressions; ++i) mupRelease(_hParser[i]);}
    delete[] _hParser;_hParser = NULL;
    delete _cs;_cs = NULL;
    delete _converter;_converter = NULL;
    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;
} // destructor


// ----------------------------------------------------------------------
// Set values in database.
void
spatialdata::spatialdb::AnalyticDB::setData(const char* const* names,
                                            const char* const* units,
                                            const char* const* expressions,
                                            const size_t numExpressions) {
    assert( (0 < numExpressions && names && units && expressions) ||
            (0 == numExpressions && !names && !units && !expressions) );

    // clear out old data
    delete[] _names;_names = NULL;
    delete[] _expressions;_expressions = NULL;
    if (_hParser) for (size_t i = 0; i < _numExpressions; ++i) mupRelease(_hParser[i]);
    delete[] _hParser;_hParser = NULL;
    _numExpressions = numExpressions;

    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;

    spatialdata::units::Parser parser;

    if (_numExpressions > 0) {
        _names = new std::string[_numExpressions];
        for (size_t i = 0; i < _numExpressions; ++i) {
            _names[i] = names[i];
        } // for

        std::vector<double> scales(_numExpressions);
        for (size_t i = 0; i < _numExpressions; ++i) {
            if (strcasecmp(units[i], "none") != 0) {
                scales[i] = parser.parse(units[i]);
            } else {
                scales[i] = 1.0;
            } // if/else
        } // for

        _expressions = new std::string[_numExpressions];
        _hParser     = new muParserHandle_t[_numExpressions];
        for (size_t i = 0; i < _numExpressions; ++i) {
            _expressions[i] = expressions[i];
            _hParser[i] = mupCreate(muBASETYPE_FLOAT);
            mupSetArgSep(_hParser[i], ',');
          	mupSetDecSep(_hParser[i], '.');
            // Only allow built-in variables mupSetVarFactory(_hParser, AddVariable, NULL);
            mupDefineConst(_hParser[i], "pi", M_PI);
          	//mupDefineStrConst(_hParser, "version", PETSC_VERSION_GIT);
          	mupDefineVar(_hParser[i], "x", &_varVals[0]);
          	mupDefineVar(_hParser[i], "y", &_varVals[1]);
            mupDefineVar(_hParser[i], "z", &_varVals[2]);
            mupSetExpr(_hParser[i], _expressions[i].c_str());
        } // for

        // Default query values is all values.
        _querySize = _numExpressions;
        delete[] _queryValues;_queryValues = (_querySize > 0) ? new size_t[_querySize] : NULL;
        for (size_t i = 0; i < _querySize; ++i) {
            _queryValues[i] = i;
        } // for
    } // if
} // setData


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::AnalyticDB::getNamesDBValues(const char*** valueNames,
                                                     size_t* numValues) const {
    if (valueNames) {
        *valueNames = (_numExpressions > 0) ? new const char*[_numExpressions] : NULL;
        for (size_t i = 0; i < _numExpressions; ++i) {
            (*valueNames)[i] = _names[i].c_str();
        } // for
    }
    if (numValues) {
        *numValues = _numExpressions;
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
    delete[] _queryValues;_queryValues = new size_t[numVals];
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        size_t iName = 0;
        while (iName < _numExpressions) {
            if (0 == strcasecmp(names[iVal], _names[iName].c_str())) {
                break;
            }
            ++iName;
        } // while
        if (iName >= _numExpressions) {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << getDescription() << "'. Available values are:";
            for (size_t iName = 0; iName < _numExpressions; ++iName) {
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

    // Convert coordinates
    assert(numDims <= 3);
    for (int d = 0; d < numDims; ++d) _varVals[d] = coords[d];
    assert(_converter);
    _converter->convert(_varVals, 1, numDims, _cs, pCSQuery);

    for (size_t iVal = 0; iVal < _querySize; ++iVal) {
        vals[iVal] = mupEval(_hParser[_queryValues[iVal]]);
    } // for

    return 0;
} // query


// End of file
