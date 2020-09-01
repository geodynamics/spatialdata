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

#include "spatialdata/spatialdb/UserFunctionDB.hh" // Implementation of class methods

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/units/Parser.hh" // USES Parser

#include <string> // USES std::string
#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringstream
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace spatialdb {
        class UserFunctionDB::QueryFn1D : public UserFunctionDB::QueryFn {
public:

            QueryFn1D(UserFunctionDB::userfn1D_type fn) : _fn(fn) {}


            int query(double* value,
                      const double* coords,
                      const size_t dim) {
                if (!value || !coords || ( 1 != dim) ) { return 1; }
                *value = _fn(coords[0]);
                return 0;
            }

private:

            UserFunctionDB::userfn1D_type _fn;
        };

        class UserFunctionDB::QueryFn2D : public UserFunctionDB::QueryFn {
public:

            QueryFn2D(UserFunctionDB::userfn2D_type fn) : _fn(fn) {}


            int query(double* value,
                      const double* coords,
                      const size_t dim) {
                if (!value || !coords || ( 2 != dim) ) { return 1; }
                *value = _fn(coords[0], coords[1]);
                return 0;
            }

private:

            UserFunctionDB::userfn2D_type _fn;
        };

        class UserFunctionDB::QueryFn3D : public UserFunctionDB::QueryFn {
public:

            QueryFn3D(UserFunctionDB::userfn3D_type fn) : _fn(fn) {}


            int query(double* value,
                      const double* coords,
                      const size_t dim) {
                if (!value || !coords || ( 3 != dim) ) { return 1; }
                *value = _fn(coords[0], coords[1], coords[2]);
                return 0;
            }

private:

            UserFunctionDB::userfn3D_type _fn;
        };

    } // namespace spatialdb
} // namespace spatialdata

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::UserFunctionDB::UserFunctionDB(void) :
    _queryFunctions(NULL),
    _cs(NULL),
    _converter(new spatialdata::geocoords::Converter),
    _querySize(0) {}


// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::UserFunctionDB::~UserFunctionDB(void) {
    delete[] _queryFunctions;_queryFunctions = NULL;
    _querySize = 0;

    for (function_map::iterator iter = _functions.begin(); iter != _functions.end(); ++iter) {
        delete iter->second.fn;iter->second.fn = NULL;
    } // for

    delete _cs;_cs = NULL;
    delete _converter;_converter = NULL;
} // destructor


// ----------------------------------------------------------------------
// Add function/value to database in 1-D.
void
spatialdata::spatialdb::UserFunctionDB::addValue(const char* name,
                                                 userfn1D_type fn,
                                                 const char* units) {
    _checkAdd(name, (void*)fn, units);

    UserData data;
    data.fn = new QueryFn1D(fn);
    data.units = units;
    data.scale = 0.0;
    _functions[name] = data;
} // addValue


// ----------------------------------------------------------------------
// Add function/value to database in 2-D.
void
spatialdata::spatialdb::UserFunctionDB::addValue(const char* name,
                                                 userfn2D_type fn,
                                                 const char* units) {
    _checkAdd(name, (void*)fn, units);

    UserData data;
    data.fn = new QueryFn2D(fn);
    data.units = units;
    data.scale = 0.0;
    _functions[name] = data;
} // addValue


// ----------------------------------------------------------------------
// Add function/value to database in 3-D.
void
spatialdata::spatialdb::UserFunctionDB::addValue(const char* name,
                                                 userfn3D_type fn,
                                                 const char* units) {
    _checkAdd(name, (void*)fn, units);

    UserData data;
    data.fn = new QueryFn3D(fn);
    data.units = units;
    data.scale = 0.0;
    _functions[name] = data;
} // addValue


// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::UserFunctionDB::open(void) {
    // Compute conversion to SI units.
    spatialdata::units::Parser parser;

    const std::string& none = "none";
    for (function_map::iterator iter = _functions.begin(); iter != _functions.end(); ++iter) {
        if (strcasecmp(none.c_str(),  iter->second.units.c_str()) != 0) {
            iter->second.scale = parser.parse(iter->second.units.c_str());
        } else {
            iter->second.scale = 1.0;
        } // if/else
    } // for

    _checkCompatibility();

    // Default query values is all values.
    _querySize = _functions.size();
    delete[] _queryFunctions;_queryFunctions = (_querySize > 0) ? new UserData*[_querySize] : NULL;
    size_t index = 0;
    for (function_map::iterator iter = _functions.begin(); iter != _functions.end(); ++iter, ++index) {
        _queryFunctions[index] = &iter->second;
    } // for
} // open


// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::UserFunctionDB::close(void) {
    delete[] _queryFunctions;_queryFunctions = NULL;
} // close


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::UserFunctionDB::getNamesDBValues(const char*** valueNames,
                                                         size_t* numValues) const {
    const size_t dbNumValues = _functions.size();
    if (valueNames) {
        *valueNames = (dbNumValues > 0) ? new const char*[dbNumValues] : NULL;
        size_t i = 0;
        for (function_map::const_iterator iter = _functions.begin(); iter != _functions.end(); ++iter, ++i) {
            (*valueNames)[i] = iter->first.c_str();
        } // for
    } // if
    if (numValues) {
        *numValues = dbNumValues;
    } // if
} // getNamesDBValues


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::UserFunctionDB::setQueryValues(const char* const* names,
                                                       const size_t numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values for query in spatial database " << getLabel()
            << "\n must be positive.\n";
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryFunctions;_queryFunctions = numVals > 0 ? new UserData*[numVals] : NULL;
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        const function_map::iterator iter = _functions.find(names[iVal]);
        if (_functions.end() == iter) {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << getLabel() << "'. Available values are:";
            for (function_map::iterator viter = _functions.begin(); viter != _functions.end(); ++viter) {
                msg << "\n  " << viter->first;
            } // for
            msg << "\n";
            throw std::out_of_range(msg.str());
        } // if

        _queryFunctions[iVal] = &iter->second;
    } // for
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::UserFunctionDB::query(double* vals,
                                              const size_t numVals,
                                              const double* coords,
                                              const size_t numDims,
                                              const spatialdata::geocoords::CoordSys* csQuery) {
    const size_t querySize = _querySize;

    assert(_cs);

    if (0 == querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << getLabel()
            << " have not been set. Please call setQueryValues() before query().\n";
        throw std::logic_error(msg.str());
    } else if (numVals != querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getLabel() << " (" << querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::invalid_argument(msg.str());
    } else if (numDims != _cs->getSpaceDim()) {
        std::ostringstream msg;
        msg << "Spatial dimension (" << numDims
            << ") does not match spatial dimension of spatial database (" << _cs->getSpaceDim() << ").";
        throw std::invalid_argument(msg.str());
    } // if

    // Convert coordinates
    assert(numDims <= 3);
    double xyz[3];
    memcpy(xyz, coords, numDims*sizeof(double));
    assert(_converter);
    _converter->convert(xyz, 1, numDims, _cs, csQuery);

    int queryFlag = 0;
    for (size_t iVal = 0; iVal < querySize; ++iVal) {
        assert(_queryFunctions[iVal]->fn);
        queryFlag = _queryFunctions[iVal]->fn->query(&vals[iVal], xyz, numDims);
        if (queryFlag) { break; }
        vals[iVal] *= _queryFunctions[iVal]->scale; // Convert to SI units.
    } // for

    return queryFlag;
} // query


// ----------------------------------------------------------------------
// Set filename containing data.
void
spatialdata::spatialdb::UserFunctionDB::setCoordSys(const geocoords::CoordSys& cs) {
    delete _cs;_cs = cs.clone();assert(_cs);
} // setCoordSys


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::UserFunctionDB::_checkAdd(const char* name,
                                                  void* fn,
                                                  const char* units) const {
    if (!name) {
        std::ostringstream msg;
        msg << "NULL name passed to addValue() for spatial database " << getLabel() << ".";
        throw std::logic_error(msg.str());
    } // if

    if (!units) {
        std::ostringstream msg;
        msg << "NULL units passed to addValue() for spatial database " << getLabel() << ".";
        throw std::logic_error(msg.str());
    } // if

    // Verify user function for value does not already exist.
    const function_map::const_iterator& iter = _functions.find(name);
    if (iter != _functions.end()) {
        std::ostringstream msg;
        msg << "Cannot add user function for value " << name << " to spatial database " << getLabel()
            << ". User function for value already exists.";
        throw std::logic_error(msg.str());
    } // if

    if (!fn) {
        std::ostringstream msg;
        msg << "Cannot add NULL user function for value " << name << " to spatial database " << getLabel() << ".";
        throw std::invalid_argument(msg.str());
    } // if
} // _checkAdd


// ----------------------------------------------------------------------
// Check compatibility of spatial database parameters.
void
spatialdata::spatialdb::UserFunctionDB::_checkCompatibility(void) const {
    // Verify that we can call all user functions for given spatial dimension.

    if (!_cs) {
        std::ostringstream msg;
        msg << "Coordinate system has not been set for spatial database " << getLabel() << ".";
        throw std::logic_error(msg.str());
    } // if

    double coords[3] = { 0.0, 0.0, 0.0 };
    const int spaceDim = _cs->getSpaceDim();
    assert(0 < spaceDim && spaceDim <= 3);

    double value;
    for (function_map::const_iterator iter = _functions.begin(); iter != _functions.end(); ++iter) {
        assert(iter->second.fn);
        const int flag = iter->second.fn->query(&value, coords, spaceDim);
        if (flag) {
            std::ostringstream msg;
            msg << "Error encountered in verifying compatibility for user function " << typeid(iter->second.fn).name()
                << " for value '" << iter->first << "' in spatial database " << getLabel() << ".";
            throw std::runtime_error(msg.str());
        } // if
    } // for
} // _checkCompatibility


// End of file
