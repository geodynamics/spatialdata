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
#include "SimpleDB.hh" // Implementation of class methods

#include "SimpleIO.hh" // USES SimpleIO
#include "SimpleDBData.hh" // USES SimpleDBData
#include "SimpleDBQuery.hh" // USES SimpleDBQuery

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

#include <sstream> // USES std::ostringsgream
#include <cassert> // USES assert()
#include <stdexcept> // USES std::runtime_error
#include "Exception.hh" // USES OutOfBounds

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::SimpleDB::SimpleDB(void) :
    _data(NULL),
    _iohandler(NULL),
    _query(NULL),
    _cs(NULL)
{}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::SimpleDB::SimpleDB(const char* label) :
    SpatialDB(label),
    _data(NULL),
    _iohandler(NULL),
    _query(NULL),
    _cs(NULL)
{}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SimpleDB::~SimpleDB(void) {
    delete _data;_data = NULL;
    delete _iohandler;_iohandler = NULL;
    delete _query;_query = NULL;
    delete _cs;_cs = NULL;
} // destructor


// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::SimpleDB::setQueryType(const SimpleDB::QueryEnum queryType) {
    if (!_query) {
        _query = new SimpleDBQuery(*this);
    } // if
    assert(_query);
    _query->setQueryType(queryType);
} // setQueryType


// ----------------------------------------------------------------------
// Set the I/O handler.
void
spatialdata::spatialdb::SimpleDB::setIOHandler(const SimpleIO* iohandler) {
    delete _iohandler;_iohandler = iohandler ? iohandler->clone() : NULL;
} // setIOHandler


// ----------------------------------------------------------------------
/// Open the database and prepare for querying.
void
spatialdata::spatialdb::SimpleDB::open(void) {
    assert(_iohandler);

    // Read data
    if (!_data) {
        _data = new SimpleDBData;
        _iohandler->read(_data, &_cs);
    } // if

    // Create query object
    if (!_query) {
        _query = new SimpleDBQuery(*this);
    } // if

    // Set default query values to all values in database
    const size_t numValues = _data->getNumValues();
    const char** queryValues = (numValues > 0) ? new const char*[numValues] : NULL;
    for (size_t i = 0; i < numValues; ++i) {
        queryValues[i] = _data->getName(i);
    } // for
    _query->setQueryValues(queryValues, numValues);
    delete[] queryValues;queryValues = NULL;
} // open


// ----------------------------------------------------------------------
/// Close the database.
void
spatialdata::spatialdb::SimpleDB::close(void) {
    delete _data;_data = 0;

    if (_query) {
        _query->deallocate();
    } // if
} // close


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::SimpleDB::getNamesDBValues(const char*** valueNames,
                                                   size_t* numValues) const {
    const size_t dataNumValues = (_data) ? _data->getNumValues() : 0;
    if (valueNames) {
        *valueNames = (dataNumValues > 0) ? new const char*[dataNumValues] : NULL;
        for (size_t i = 0; i < dataNumValues; ++i) {
            (*valueNames)[i] = _data->getName(i);
        } // for
    }
    if (numValues) {
        *numValues = dataNumValues;
    } // if
} // getNamesDBValues


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleDB::setQueryValues(const char* const* names,
                                                 const size_t numVals) {
    if (!_query) {
        std::ostringstream msg;
        msg << "Spatial database " << getLabel() << " has not been opened.\n"
            << "Please call Open() before calling QueryVals().";
        throw std::logic_error(msg.str());
    } // if
    _query->setQueryValues(names, numVals);
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SimpleDB::query(double* vals,
                                        const size_t numVals,
                                        const double* coords,
                                        const size_t numDims,
                                        const spatialdata::geocoords::CoordSys* pCSQuery) {
    try {
        if (!_query) {
            std::ostringstream msg;
            msg << "Spatial database " << getLabel() << " has not been opened.\n"
                << "Please call open() before calling query().";
            throw std::logic_error(msg.str());
        } // if
        else if (!_data) {
            std::ostringstream msg;
            msg << "Spatial database " << getLabel() << " does not contain any data.\n"
                << "Database query aborted.";
            throw std::domain_error(msg.str());
        } // if
        _query->query(vals, numVals, coords, numDims, pCSQuery);
    } catch (const OutOfBounds& err) {
        std::fill(vals, vals+numVals, 0);
        return 1;
    } catch (const std::exception& err) {
        throw;
    } catch (...) {
        throw std::runtime_error("Unknown error in SpatialDB query");
    } // catch
    return 0;
} // query


// End of file
