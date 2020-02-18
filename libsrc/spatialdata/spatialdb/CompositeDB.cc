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

#include "SpatialDB.hh" // ISA SpatialDB object
#include "CompositeDB.hh" // Implementation of class methods

#include <stdexcept> // USES std::runtime_error

#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <cassert> // USES assert()

#include <iostream> // TEMPORARY

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::CompositeDB::CompositeDB(void) :
    _dbA(NULL),
    _dbB(NULL),
    _infoA(NULL),
    _infoB(NULL) {}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::CompositeDB::CompositeDB(const char* label) :
    SpatialDB(label),
    _dbA(NULL),
    _dbB(NULL),
    _infoA(NULL),
    _infoB(NULL) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::CompositeDB::~CompositeDB(void) {
    // Don't manage memory for dbA and dbB

    if (!_infoA) {
        delete[] _infoA->query_buffer;_infoA->query_buffer = NULL;
        delete[] _infoA->query_indices;_infoA->query_indices = NULL;
        delete[] _infoA->names_values;_infoA->names_values = NULL;
    } // if
    delete _infoA;_infoA = NULL;

    if (!_infoB) {
        delete[] _infoB->query_buffer;_infoB->query_buffer = NULL;
        delete[] _infoB->query_indices;_infoB->query_indices = NULL;
        delete[] _infoB->names_values;_infoB->names_values = NULL;
    } // if
    delete _infoB;_infoB = NULL;
} // destructor


// ----------------------------------------------------------------------
// Set database A.
void
spatialdata::spatialdb::CompositeDB::setDBA(SpatialDB* db,
                                            const char* const* names,
                                            const size_t numNames) {
    assert(db);
    assert(names);
    assert(numNames > 0);

    // Clear out old data
    if (_infoA) {
        delete[] _infoA->query_buffer;_infoA->query_buffer = NULL;
        delete[] _infoA->query_indices;_infoA->query_indices = NULL;
        delete[] _infoA->names_values;_infoA->names_values = NULL;
    } else {
        _infoA = new dbinfo;
    }

    _dbA = db;

    // Initialize data
    _infoA->query_buffer = NULL;
    _infoA->query_indices = NULL;
    _infoA->names_values = NULL;
    _infoA->query_size = 0;
    _infoA->num_names = 0;

    // Set data
    if (numNames > 0) {
        _infoA->names_values = new std::string[numNames];
        _infoA->num_names = numNames;
        for (size_t i = 0; i < numNames; ++i) {
            _infoA->names_values[i] = names[i];
        }
    } // if
} // setDBA


// ----------------------------------------------------------------------
// Set database B.
void
spatialdata::spatialdb::CompositeDB::setDBB(SpatialDB* db,
                                            const char* const* names,
                                            const size_t numNames) {
    assert(db);
    assert(names);
    assert(numNames > 0);

    // Clear out old data
    if (_infoB) {
        delete[] _infoB->query_buffer;_infoB->query_buffer = NULL;
        delete[] _infoB->query_indices;_infoB->query_indices = NULL;
        delete[] _infoB->names_values;_infoB->names_values = NULL;
    } else {
        _infoB = new dbinfo;
    }

    _dbB = db;

    // Initialize data
    _infoB->query_buffer = NULL;
    _infoB->query_indices = NULL;
    _infoB->names_values = NULL;
    _infoB->query_size = 0;
    _infoB->num_names = 0;

    // Set data
    if (numNames > 0) {
        _infoB->names_values = new std::string[numNames];
        _infoB->num_names = numNames;
        for (size_t i = 0; i < numNames; ++i) {
            _infoB->names_values[i] = names[i];
        }
    } // if
} // setDBB


// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::CompositeDB::open(void) {
    if (!_dbA) {
        throw std::runtime_error("Cannot open database A. Database was not set.");
    }
    if (!_dbB) {
        throw std::runtime_error("Cannot open database B. Database was not set.");
    }

    _dbA->open();
    _dbB->open();
} // open


// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::CompositeDB::close(void) {
    if (!_dbA) {
        throw std::runtime_error("Cannot close database A. Database was not set.");
    }
    if (!_dbB) {
        throw std::runtime_error("Cannot close database B. Database was not set.");
    }

    _dbA->close();
    _dbB->close();
} // close


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::CompositeDB::setQueryValues(const char* const* names,
                                                    const size_t numVals) {
    assert(_dbA);
    assert(_infoA);
    assert(_dbB);
    assert(_infoB);

    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values for query in spatial database " << getLabel()
            << " must be positive.\n";
        throw std::runtime_error(msg.str());
    } // if
    assert(names && 0 < numVals);

    _infoA->query_size = 0;
    _infoB->query_size = 0;
    const int numNamesA = _infoA->num_names;
    const int numNamesB = _infoB->num_names;
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        bool foundA = false;
        bool foundB = false;

        // Search database A names for name
        size_t iName = 0;
        while (iName < numNamesA) {
            if (0 == strcasecmp(names[iVal], _infoA->names_values[iName].c_str())) {
                foundA = true;
                ++_infoA->query_size;
                break;
            } // if
            ++iName;
        } // while

        // Search database B names for name
        iName = 0;
        while (iName < numNamesB) {
            if (0 == strcasecmp(names[iVal], _infoB->names_values[iName].c_str())) {
                foundB = true;
                ++_infoB->query_size;
                break;
            } // if
            ++iName;
        } // while

        if (!foundA && !foundB) {
            std::ostringstream msg;
            msg << "Value " << names[iVal]
                << " not found in either database A or database B.";
            throw std::runtime_error(msg.str());
        } else if (foundA && foundB) {
            std::ostringstream msg;
            msg << "Value " << names[iVal]
                << " found in both database A or database B.";
            throw std::runtime_error(msg.str());
        } // if/else
    } // for
    assert(_infoA->query_size + _infoB->query_size == numVals);

    // Setup query values for A
    const int qsizeA = _infoA->query_size;
    char** queryValsA = (qsizeA > 0) ? new char*[qsizeA] : NULL;
    delete[] _infoA->query_indices;
    _infoA->query_indices = (qsizeA > 0) ? new size_t[qsizeA] : NULL;
    delete[] _infoA->query_buffer;
    _infoA->query_buffer = (qsizeA > 0) ? new double[qsizeA] : NULL;

    // Setup query values for B
    const int qsizeB = _infoB->query_size;
    char** queryValsB = (qsizeB > 0) ? new char*[qsizeB] : NULL;
    delete[] _infoB->query_indices;
    _infoB->query_indices = (qsizeB > 0) ? new size_t[qsizeB] : NULL;
    delete[] _infoB->query_buffer;
    _infoB->query_buffer = (qsizeB > 0) ? new double[qsizeB] : NULL;

    for (size_t iVal = 0, indexA = 0, indexB = 0; iVal < numVals; ++iVal) {
        size_t iName = 0;
        // Search database A names
        while (iName < numNamesA) {
            if (0 == strcasecmp(names[iVal], _infoA->names_values[iName].c_str())) {
                assert(indexA < qsizeA);
                _infoA->query_indices[indexA] = iVal;
                queryValsA[indexA] = const_cast<char*>(_infoA->names_values[iName].c_str());
                ++indexA;
                break;
            } // if
            ++iName;
        } // while

        // Search database B names
        iName = 0;
        while (iName < numNamesB) {
            if (0 == strcasecmp(names[iVal], _infoB->names_values[iName].c_str())) {
                assert(indexB < qsizeB);
                _infoB->query_indices[indexB] = iVal;
                queryValsB[indexB] = const_cast<char*>(_infoB->names_values[iName].c_str());
                ++indexB;
                break;
            } // if
            ++iName;
        } // while
    } // for
    if (qsizeA > 0) {
        _dbA->setQueryValues(const_cast<const char**>(queryValsA), qsizeA);
    } // if
    if (qsizeB > 0) {
        _dbB->setQueryValues(const_cast<const char**>(queryValsB), qsizeB);
    } // if

    delete[] queryValsA;queryValsA = NULL;
    delete[] queryValsB;queryValsB = NULL;
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::CompositeDB::query(double* vals,
                                           const size_t numVals,
                                           const double* coords,
                                           const size_t numDims,
                                           const spatialdata::geocoords::CoordSys* pCSQuery) {
    assert(_dbA);
    assert(_infoA);
    assert(_dbB);
    assert(_infoB);

    const size_t qsizeA = _infoA->query_size;
    const size_t qsizeB = _infoB->query_size;
    const size_t querySize = qsizeA + qsizeB;
    if (0 == querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << getLabel()
            << " have not been set. Please call setQueryValues() before query().\n";
        throw std::runtime_error(msg.str());
    } // if
    else if (numVals != querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getLabel()
            << "(" << querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::runtime_error(msg.str());
    } // if

    // Query database A
    if (qsizeA > 0) {
        _dbA->query(_infoA->query_buffer, qsizeA, coords, numDims, pCSQuery);
        for (size_t i = 0; i < qsizeA; ++i) {
            vals[_infoA->query_indices[i]] = _infoA->query_buffer[i];
        } // for
    } // if

    // Query database B
    if (qsizeB > 0) {
        _dbB->query(_infoB->query_buffer, qsizeB, coords, numDims, pCSQuery);
        for (size_t i = 0; i < qsizeB; ++i) {
            vals[_infoB->query_indices[i]] = _infoB->query_buffer[i];
        } // for
    } // if

    return 0;
} // query


// End of file
