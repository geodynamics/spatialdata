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

#include "UserFunctionDB.hh" // Implementation of class methods

#include <strings.h> // USES strcasecmp()
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::UserFunctionDB::UserFunctionDB(void) :
  _queryFunctions(NULL),
  _querySize(0),
  _spaceDim(0),
  _cs(NULL)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::UserFunctionDB::~UserFunctionDB(void)
{ // destructor
  delete[] _queryFunctions; _queryFunctions = NULL;
  _querySize = 0;
  _spaceDim = 0;

  delete _cs; _cs = NULL;
} // destructor

// ----------------------------------------------------------------------
// Add function/value to database.
void
spatialdata::spatialdb::UserFunctionDB::addValue(const char* name,
						 queryfn_type fn,
						 const char* units)
{ // addValue
  // :TODO: ADD STUFF HERE
} // addValue
 
// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::UserFunctionDB::open(void)
{ // open
  delete[] _queryFunctions; _queryFunctions = NULL;
} // open

// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::UserFunctionDB::close(void)
{ // close
  delete[] _queryFunctions; _queryFunctions = NULL;
} // close

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::UserFunctionDB::queryVals(const char* const* names,
						 const int numVals)
{ // queryVals
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(names && 0 < numVals);
  
  _querySize = numVals;
  delete[] _queryVals; _queryVals = numVals > 0 ? new UserData[numVals] : NULL;
  for (int iVal=0; iVal < numVals; ++iVal) {
    // :TODO: ADD STUFF HERE
    } // while
    if (iName >= numNames) {
      std::ostringstream msg;
      msg
	<< "Could not find value '" << names[iVal] << "' in spatial database '"
	<< label() << "'. Available values are:";
      for (int iName=0; iName < numNames; ++iName)
	msg << "\n  " << _names[iName];
      msg << "\n";
      throw std::runtime_error(msg.str());
    } // if
    // :TODO: ADD STUFF HERE
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
  } else if (numDims != cs->spaceDim()) {
    std::ostringstream msg;
    msg
      << "Spatial dimension (" << numDims
      << ") does not match spatial dimension of spatial database (" << cs->spaceDim() << ").";
    throw std::runtime_error(msg.str());
  } // if

  // Convert coordinates
  assert(numDims <= 3);
  memcpy(_xyz, coords, numDims*sizeof(double));
  spatialdata::geocoords::Converter::convert(_xyz, 1, numDims, _cs, csQuery);

  int queryFlag = 0;
  const int spaceDim = cs->spaceDim();

  for (int iVal=0; iVal < querySize; ++iVal) {
    vals[iVal] = _data[indexData+_queryVals[iVal]];
#if 0 // DEBUGGING
    std::cout << "val["<<iVal<<"]: " << vals[iVal]
	      << ", indexData: " << indexData
	      << ", index0: " << index0
	      << ", index1: " << index1
	      << ", index2: " << index2
	      << std::endl;
#endif
    } // for
    
  return queryFlag;
} // query


// ----------------------------------------------------------------------
// Set filename containing data.
void
spatialdata::spatialdb::UserFunctionDB::coordsys(const geocoords::CoordSys& cs)
{ // coordsys
  delete _cs; _cs = cs.clone();
  _cs->initialize();
} // coordsys
 
// ----------------------------------------------------------------------
// Check compatibility of spatial database parameters.
void
spatialdata::spatialdb::UserFunctionDB::_checkCompatibility(void) const
{ // _checkCompatibility
  // :TODO: ADD STUFF HERE
} // _checkCompatibility


// End of file
