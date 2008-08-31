// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "SpatialDB.hh" // ISA SpatialDB object
#include "CompositeDB.hh" // Implementation of class methods

#include <stdexcept> // USES std::runtime_error

#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

#include <iostream> // TEMPORARY

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::CompositeDB::CompositeDB(void) :
  _dbA(0),
  _dbB(0),
  _infoA(0),
  _infoB(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::CompositeDB::CompositeDB(const char* label) :
  SpatialDB(label),
  _dbA(0),
  _dbB(0),
  _infoA(0),
  _infoB(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::CompositeDB::~CompositeDB(void)
{ // destructor
  // Don't manage memory for dbA and dbB

  if (0 != _infoA) {
    delete[] _infoA->query_buffer; _infoA->query_buffer = 0;
    delete[] _infoA->query_indices; _infoA->query_indices = 0;
    delete[] _infoA->names_values; _infoA->names_values = 0;
  } // if
  delete _infoA; _infoA = 0;

  if (0 != _infoB) {
    delete[] _infoB->query_buffer; _infoB->query_buffer = 0;
    delete[] _infoB->query_indices; _infoB->query_indices = 0;
    delete[] _infoB->names_values; _infoB->names_values = 0;
  } // if
  delete _infoB; _infoB = 0;
} // destructor

// ----------------------------------------------------------------------
// Set database A.
void
spatialdata::spatialdb::CompositeDB::dbA(SpatialDB* db,
					 const char** names,
					 const int numNames)
{ // dbA
  assert(0 != db);
  assert(names != 0);
  assert(numNames > 0);

  // Clear out old data
  if (0 != _infoA) {
    delete[] _infoA->query_buffer; _infoA->query_buffer = 0;
    delete[] _infoA->query_indices; _infoA->query_indices = 0;
    delete[] _infoA->names_values; _infoA->names_values = 0;
  } else
    _infoA = new dbinfo;

  _dbA = db;

  // Initialize data
  _infoA->query_buffer = 0;
  _infoA->query_indices = 0;
  _infoA->names_values = 0;
  _infoA->query_size = 0;
  _infoA->num_names = 0;
  
  // Set data
  if (numNames > 0) {
    _infoA->names_values = new std::string[numNames];
    _infoA->num_names = numNames;
    for (int i=0; i < numNames; ++i)
      _infoA->names_values[i] = names[i];
  } // if
} // dbA

// ----------------------------------------------------------------------
// Set database B.
void
spatialdata::spatialdb::CompositeDB::dbB(SpatialDB* db,
					 const char** names,
					 const int numNames)
{ // dbB
  assert(0 != db);
  assert(names != 0);
  assert(numNames > 0);

  // Clear out old data
  if (0 != _infoB) {
    delete[] _infoB->query_buffer; _infoB->query_buffer = 0;
    delete[] _infoB->query_indices; _infoB->query_indices = 0;
    delete[] _infoB->names_values; _infoB->names_values = 0;
  } else
    _infoB = new dbinfo;

  _dbB = db;

  // Initialize data
  _infoB->query_buffer = 0;
  _infoB->query_indices = 0;
  _infoB->names_values = 0;
  _infoB->query_size = 0;
  _infoB->num_names = 0;
  
  // Set data
  if (numNames > 0) {
    _infoB->names_values = new std::string[numNames];
    _infoB->num_names = numNames;
    for (int i=0; i < numNames; ++i)
      _infoB->names_values[i] = names[i];
  } // if
} // dbB

// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::CompositeDB::open(void)
{ // open
  if (0 == _dbA)
    throw std::runtime_error("Cannot open database A. Database was not set.");
  if (0 == _dbB)
    throw std::runtime_error("Cannot open database B. Database was not set.");

  _dbA->open();
  _dbB->open();
} // open

// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::CompositeDB::close(void)
{ // close
  if (0 == _dbA)
    throw std::runtime_error("Cannot close database A. Database was not set.");
  if (0 == _dbB)
    throw std::runtime_error("Cannot close database B. Database was not set.");

  _dbA->close();
  _dbB->close();
} // close

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::CompositeDB::queryVals(const char** names,
					       const int numVals)
{ // queryVals
  assert(0 != _dbA);
  assert(0 != _infoA);
  assert(0 != _dbB);
  assert(0 != _infoB);

  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(0 != names && 0 < numVals);
  
  _infoA->query_size = 0;
  _infoB->query_size = 0;
  const int numNamesA = _infoA->num_names;
  const int numNamesB = _infoB->num_names;
  for (int iVal=0; iVal < numVals; ++iVal) {
    bool foundA = false;
    bool foundB = false;

    // Search database A names for name
    int iName = 0;
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
      msg
	<< "Value " << names[iVal]
	<< " not found in either database A or database B.";
      throw std::runtime_error(msg.str());
    } else if (foundA && foundB) {
      std::ostringstream msg;
      msg
	<< "Value " << names[iVal]
	<< " found in both database A or database B.";
      throw std::runtime_error(msg.str());
    } // if/else
  } // for
  assert(_infoA->query_size + _infoB->query_size == numVals);

  // Setup query values for A
  const int qsizeA = _infoA->query_size;
  char** queryValsA = (qsizeA > 0) ? new char*[qsizeA] : 0;
  delete[] _infoA->query_indices;
  _infoA->query_indices = (qsizeA > 0) ? new int[qsizeA] : 0;
  delete[] _infoA->query_buffer;
  _infoA->query_buffer = (qsizeA > 0) ? new double[qsizeA] : 0;

  // Setup query values for B
  const int qsizeB = _infoB->query_size;
  char** queryValsB = (qsizeB > 0) ? new char*[qsizeB] : 0;
  delete[] _infoB->query_indices;
  _infoB->query_indices = (qsizeB > 0) ? new int[qsizeB] : 0;
  delete[] _infoB->query_buffer;
  _infoB->query_buffer = (qsizeB > 0) ? new double[qsizeB] : 0;

  for (int iVal=0, indexA=0, indexB=0; iVal < numVals; ++iVal) {
    int iName = 0;
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
  _dbA->queryVals(const_cast<const char**>(queryValsA), qsizeA);
  _dbB->queryVals(const_cast<const char**>(queryValsB), qsizeB);

  delete[] queryValsA; queryValsA = 0;
  delete[] queryValsB; queryValsB = 0;
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::CompositeDB::query(
			      double* vals,
			      const int numVals,
			      const double* coords,
			      const int numDims,
			      const spatialdata::geocoords::CoordSys* pCSQuery)
{ // query
  assert(0 != _dbA);
  assert(0 != _infoA);
  assert(0 != _dbB);
  assert(0 != _infoB);

  const int qsizeA = _infoA->query_size;
  const int qsizeB = _infoB->query_size;
  const int querySize = qsizeA + qsizeB;
  if (0 == querySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << label() << "\n"
      << "have not been set. Please call queryVals() before query().\n";
    throw std::runtime_error(msg.str());
  } // if
  else if (numVals != querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << label() << "\n"
      << "(" << querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } // if

  // Query database A
  _dbA->query(_infoA->query_buffer, qsizeA, coords, numDims, pCSQuery);
  for (int i=0; i < qsizeA; ++i)
    vals[_infoA->query_indices[i]] = _infoA->query_buffer[i];

  // Query database B
  _dbB->query(_infoB->query_buffer, qsizeB, coords, numDims, pCSQuery);
  for (int i=0; i < qsizeB; ++i)
    vals[_infoB->query_indices[i]] = _infoB->query_buffer[i];

  return 0;
} // query


// End of file 
