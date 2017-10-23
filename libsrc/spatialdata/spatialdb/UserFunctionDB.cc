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

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/units/Parser.hh" // USES Parser

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::UserFunctionDB::UserFunctionDB(void) :
    _queryFunctions(NULL),
    _cs(NULL),
    _querySize(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::UserFunctionDB::~UserFunctionDB(void) {
    delete[] _queryFunctions; _queryFunctions = NULL;
    _querySize = 0;

    delete _cs; _cs = NULL;
} // destructor

// ----------------------------------------------------------------------
// Add function/value to database.
void
spatialdata::spatialdb::UserFunctionDB::addValue(const char* name,
						 queryfn_type fn,
						 const char* units) {
    // Verify user function for value does not already exist.
    const function_map::iterator& iter = _functions.find(name);
    if (iter != _functions.end()) {
	std::ostringstream msg;
	msg << "Cannot add user function for value " << name << " to spatial database " << label() << ". User function for value already exists.";
	throw std::runtime_error(msg.str());
    } // if

    if (!fn) {
	std::ostringstream msg;
	msg << "Cannot add NULL user function for value " << name << " to spatial database " << label() << ".";
	throw std::runtime_error(msg.str());
    } // if

    // Add user function.
    UserData data;
    data.fn = fn;
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
    for (function_map::iterator iter=_functions.begin(); iter != _functions.end(); ++iter) {
	if (none != iter->second.units) {
	    iter->second.scale = parser.parse(iter->second.units.c_str());
	} else {
	    iter->second.scale = 1.0;
	} // if/else
    } // for

    _checkCompatibility();
} // open

// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::UserFunctionDB::close(void) {
    delete[] _queryFunctions; _queryFunctions = NULL;
} // close

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::UserFunctionDB::queryVals(const char* const* names,
						 const int numVals) {
    if (0 == numVals) {
	std::ostringstream msg;
	msg
	    << "Number of values for query in spatial database " << label()
	    << "\n must be positive.\n";
	throw std::runtime_error(msg.str());
    } // if
    assert(names && 0 < numVals);
    
    _querySize = numVals;
    delete[] _queryFunctions; _queryFunctions = numVals > 0 ? new UserData*[numVals] : NULL;
    for (int iVal=0; iVal < numVals; ++iVal) {
	const function_map::iterator iter = _functions.find(names[iVal]);
	if (_functions.end() == iter) {
	    std::ostringstream msg;
	    msg
		<< "Could not find value '" << names[iVal] << "' in spatial database '"
		<< label() << "'. Available values are:";
	    for (function_map::iterator viter = _functions.begin(); viter != _functions.end(); ++viter) {
		msg << "\n  " << viter->first;
	    } // for
	    msg << "\n";
	    throw std::runtime_error(msg.str());
	} // if
	
	_queryFunctions[iVal] = &iter->second;
    } // for
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::UserFunctionDB::query(double* vals,
					    const int numVals,
					    const double* coords,
					    const int numDims,
					    const spatialdata::geocoords::CoordSys* csQuery)
{ // query
    const int querySize = _querySize;
    
    assert(_cs);
  
    if (0 == querySize) {
	std::ostringstream msg;
	msg
	    << "Values to be returned by spatial database " << label() << "\n"
	    << "have not been set. Please call queryVals() before query().\n";
	throw std::runtime_error(msg.str());
    } else if (numVals != querySize) {
	std::ostringstream msg;
	msg
	    << "Number of values to be returned by spatial database "
	    << label() << "\n"
	    << "(" << querySize << ") does not match size of array provided ("
	    << numVals << ").\n";
	throw std::runtime_error(msg.str());
    } else if (numDims != _cs->spaceDim()) {
	std::ostringstream msg;
	msg
	    << "Spatial dimension (" << numDims
	    << ") does not match spatial dimension of spatial database (" << _cs->spaceDim() << ").";
	throw std::runtime_error(msg.str());
    } // if

    // Convert coordinates
    assert(numDims <= 3);
    double xyz[3];
    memcpy(xyz, coords, numDims*sizeof(double));
    spatialdata::geocoords::Converter::convert(xyz, 1, numDims, _cs, csQuery);

    int queryFlag = 0;
    for (int iVal=0; iVal < querySize; ++iVal) {
	queryFlag = _queryFunctions[iVal]->fn(&vals[iVal], xyz, numDims);
	if (!queryFlag) { break; }
    } // for
    
    return queryFlag;
} // query


// ----------------------------------------------------------------------
// Set filename containing data.
void
spatialdata::spatialdb::UserFunctionDB::coordsys(const geocoords::CoordSys& cs)
{ // coordsys
    delete _cs; _cs = cs.clone(); assert(_cs);
    _cs->initialize();
} // coordsys
 
// ----------------------------------------------------------------------
// Check compatibility of spatial database parameters.
void
spatialdata::spatialdb::UserFunctionDB::_checkCompatibility(void) const
{ // _checkCompatibility
    // Verify that we can call all user functions for given spatial dimension.

    if (!_cs) {
	std::ostringstream msg;
	msg << "Coordinate system has not been set for spatial database " << label() << ".";
	throw std::runtime_error(msg.str());
    } // if
    
    double coords[3] = { 0.0, 0.0, 0.0 };
    const int spaceDim = _cs->spaceDim();
    assert(0 < spaceDim && spaceDim <= 3);

    double value;
    for (function_map::const_iterator iter = _functions.begin(); iter != _functions.end(); ++iter) {
	const int flag = iter->second.fn(&value, coords, spaceDim);
	if (flag) {
	    std::ostringstream msg;
	    msg << "Error encountered in verifying compatibility for user function " << iter->second.fn << " for value '" << iter->first << "' in spatial database " << label() << ".";
	    throw std::runtime_error(msg.str());
	} // if
    } // for
} // _checkCompatibility


// End of file
