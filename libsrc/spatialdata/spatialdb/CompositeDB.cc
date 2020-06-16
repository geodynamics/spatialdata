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

#include "CompositeDB.hh" // Implementation of class methods

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <cassert> // USES assert()

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

    delete _infoA;_infoA = NULL;
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
    delete _infoA;_infoA = new DBInfo;
    _dbA = db;

    // Set data
    if (numNames > 0) {
        _infoA->names_values = new std::string[numNames];
        _infoA->num_names = numNames;
        for (size_t i = 0; i < numNames; ++i) {
            _infoA->names_values[i] = names[i];
        } // for
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
    delete _infoB;_infoB = new DBInfo;
    _dbB = db;

    // Set data
    if (numNames > 0) {
        _infoB->names_values = new std::string[numNames];
        _infoB->num_names = numNames;
        for (size_t i = 0; i < numNames; ++i) {
            _infoB->names_values[i] = names[i];
        } // for
    } // if
} // setDBB


// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::CompositeDB::open(void) {
    if (!_dbA) {
        throw std::logic_error("Cannot open database A. Database was not set.");
    }
    if (!_dbB) {
        throw std::logic_error("Cannot open database B. Database was not set.");
    }

    _dbA->open();
    _dbB->open();
} // open


// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::CompositeDB::close(void) {
    if (!_dbA) {
        throw std::logic_error("Cannot close database A. Database was not set.");
    } // if
    _dbA->close();

    if (!_dbB) {
        throw std::logic_error("Cannot close database B. Database was not set.");
    } // if
    _dbB->close();
} // close


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::CompositeDB::getNamesDBValues(const char*** valueNames,
                                                      size_t* numValues) const {
    const size_t numValuesA = _infoA->num_names;
    const size_t numValuesB = _infoB->num_names;
    const size_t numValuesAB = numValuesA + numValuesB;

    if (valueNames) {
        *valueNames = (numValuesAB > 0) ? new const char*[numValuesAB] : NULL;
        size_t iAB = 0;
        for (size_t iA = 0; iA < numValuesA; ++iA, ++iAB) {
            (*valueNames)[iAB] = _infoA->names_values[iA].c_str();
        } // for
        for (size_t iB = 0; iB < numValuesB; ++iB, ++iAB) {
            (*valueNames)[iAB] = _infoB->names_values[iB].c_str();
        } // for
    } // if
    if (numValues) {
        *numValues = numValuesAB;
    } // if
} // getNamesDBValues


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
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _infoA->query_size = 0;
    _infoB->query_size = 0;
    const size_t numNamesA = _infoA->num_names;
    const size_t numNamesB = _infoB->num_names;
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
            msg << "Value " << names[iVal] << " not found in either database A or database B.";
            throw std::domain_error(msg.str());
        } else if (foundA && foundB) {
            std::ostringstream msg;
            msg << "Value " << names[iVal] << " found in both database A or database B.";
            throw std::domain_error(msg.str());
        } // if/else
    } // for
    assert(_infoA->query_size + _infoB->query_size == numVals);

    // Setup query values for A
    const size_t qsizeA = _infoA->query_size;
    char** queryValsA = (qsizeA > 0) ? new char*[qsizeA] : NULL;
    delete[] _infoA->query_indices;
    _infoA->query_indices = (qsizeA > 0) ? new size_t[qsizeA] : NULL;
    delete[] _infoA->query_buffer;
    _infoA->query_buffer = (qsizeA > 0) ? new double[qsizeA] : NULL;

    // Setup query values for B
    const size_t qsizeB = _infoB->query_size;
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
        throw std::logic_error(msg.str());
    } // if
    else if (numVals != querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getLabel()
            << "(" << querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::logic_error(msg.str());
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
