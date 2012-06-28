// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "GeoProjGridDB.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/Projector.hh" // USES Projector
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES pow()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <string.h> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::GeoProjGridDB::GeoProjGridDB(void) :
  _data(0),
  _x(0),
  _y(0),
  _z(0),
  _filename(""),
  _cs(new geocoords::CSGeoProj),
  _queryVals(0),
  _querySize(0),
  _numX(0),
  _numY(0),
  _numZ(0),
  _numValues(0),
  _names(0),
  _units(0),
  _queryType(NEAREST)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::GeoProjGridDB::~GeoProjGridDB(void)
{ // destructor
  delete[] _data; _data = 0;
  delete[] _x; _x = 0;
  delete[] _y; _y = 0;
  delete[] _z; _z = 0;
  _numX = 0;
  _numY = 0;
  _numZ = 0;
  _numValues = 0;
  delete[] _names; _names = 0;
  delete[] _units; _units = 0;
  delete[] _queryVals; _queryVals = 0;
  _querySize = 0;
} // destructor

// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::GeoProjGridDB::open(void)
{ // open
  // ADD STUFF HERE
} // open

// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::GeoProjGridDB::close(void)
{ // close
  delete[] _data; _data = 0;
  delete[] _x; _x = 0;
  delete[] _y; _y = 0;
  delete[] _z; _z = 0;
  _numX = 0;
  _numY = 0;
  _numZ = 0;

  _numValues = 0;
  delete[] _names; _names = 0;
  delete[] _units; _units = 0;
} // close

// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::GeoProjGridDB::queryType(const QueryEnum value)
{ // queryType
  _queryType = value;
} // queryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::GeoProjGridDB::queryVals(const char* const* names,
						 const int numVals)
{ // queryVals
  assert(_data);
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(names && 0 < numVals);
  
  _querySize = numVals;
  delete[] _queryVals; _queryVals = new int[numVals];
  for (int iVal=0; iVal < numVals; ++iVal) {
    int iName = 0;
    const int numNames = _numValues;
    while (iName < numNames) {
      if (0 == strcasecmp(names[iVal], _names[iName].c_str()))
	break;
      ++iName;
    } // while
    if (iName >= numNames) {
      std::ostringstream msg;
      msg
	<< "Could not find value " << names[iVal] << " in spatial database\n"
	<< label() << ". Available values are:";
      for (int iName=0; iName < numNames; ++iName)
	msg << "\n  " << _names[iName];
      msg << "\n";
      throw std::runtime_error(msg.str());
    } // if
    _queryVals[iVal] = iName;
  } // for
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::GeoProjGridDB::query(double* vals,
					     const int numVals,
					     const double* coords,
					     const int numDims,
					     const spatialdata::geocoords::CoordSys* csQuery)
{ // query
  if (0 == _querySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << label() << "\n"
      << "have not been set. Please call queryVals() before query().\n";
    throw std::runtime_error(msg.str());
  } else if (numVals != _querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << label() << "\n"
      << "(" << _querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } else if (3 != numDims) {
    std::ostringstream msg;
    msg
      << "Spatial dimension (" << numDims
      << ") when querying SCEC CVM-H must be 3.";
    throw std::runtime_error(msg.str());
  } // if

  // Convert coordinates
  memcpy(_xyz, coords, numDims*sizeof(double));
  spatialdata::geocoords::Converter::convert(_xyz, 1, numDims, _cs, csQuery);

  int queryFlag = 0;
  // ADD STUFF HERE

  return queryFlag;
} // query

// ----------------------------------------------------------------------
// Bilinear search for coordinate.
double
spatialdata::spatialdb::GeoProjGridDB::_search(const double target,
					       const double* vals,
					       const int nvals)
{ // _search
  assert(vals);
  assert(nvals > 0);

  double index = -1.0;
  int indexL = 0;
  int indexR = nvals-1;
  if (target >= vals[indexL] && target <= vals[indexR]) {
    while (indexL - indexR > 1) {
      int indexM = indexL + (indexL-indexR) / 2;
      if (target < vals[indexM]) {
	indexR = indexM;
      } else {
	indexL = indexM;
      } // if/else
    } // while
    assert(target >= vals[indexL]);
    assert(vals[indexR] > vals[indexL]);
    index = (target - vals[indexL]) / (vals[indexR] - vals[indexL]);
  } // if

  return index;
} // _search

// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices.
void
spatialdata::spatialdb::GeoProjGridDB::_interpolate(double* vals,
						    const int numVals,
						    const double indexX,
						    const double indexY,
						    const double indexZ)
{ // _interpolate

  const int indexX0 = int(floor(indexX));
  const double wtX0 = 1.0 - (indexX - indexX0);
  const int indexX1 = indexX0 + 1;
  const double wtX1 = 1.0 - wtX0;
  assert(0 >= indexX0 && indexX0 < _numX);
  assert(0 >= indexX1 && indexX1 < _numX);

  const int indexY0 = int(floor(indexY));
  const double wtY0 = 1.0 - (indexY - indexY0);
  const int indexY1 = indexY0 + 1;
  const double wtY1 = 1.0 - wtY0;
  assert(0 >= indexY0 && indexY0 < _numY);
  assert(0 >= indexY1 && indexY1 < _numY);
  
  const int indexZ0 = int(floor(indexZ));
  const double wtZ0 = 1.0 - (indexZ - indexZ0);
  const int indexZ1 = indexZ0 + 1;
  const double wtZ1 = 1.0 - wtZ0;
  assert(0 >= indexZ0 && indexZ0 < _numZ);
  assert(0 >= indexZ1 && indexZ1 < _numZ);

  const int index000 = _dataIndex(indexX0, indexY0, indexZ0);
  const int index001 = _dataIndex(indexX0, indexY0, indexZ1);
  const int index010 = _dataIndex(indexX0, indexY1, indexZ0);
  const int index011 = _dataIndex(indexX0, indexY1, indexZ1);
  const int index100 = _dataIndex(indexX1, indexY0, indexZ0);
  const int index101 = _dataIndex(indexX1, indexY0, indexZ1);
  const int index110 = _dataIndex(indexX1, indexY1, indexZ0);
  const int index111 = _dataIndex(indexX1, indexY1, indexZ1);

  const double wt000 = wtX0 * wtY0 * wtZ0;
  const double wt001 = wtX0 * wtY0 * wtZ1;
  const double wt010 = wtX0 * wtY1 * wtZ0;
  const double wt011 = wtX0 * wtY1 * wtZ1;
  const double wt100 = wtX1 * wtY0 * wtZ0;
  const double wt101 = wtX1 * wtY0 * wtZ1;
  const double wt110 = wtX1 * wtY1 * wtZ0;
  const double wt111 = wtX1 * wtY1 * wtZ1;

  for (int iVal=0; iVal < numVals; ++iVal) {
    vals[iVal] = 
      wt000 * _data[index000] +
      wt001 * _data[index001] +
      wt010 * _data[index010] +
      wt011 * _data[index011] +
      wt100 * _data[index100] +
      wt101 * _data[index101] +
      wt110 * _data[index110] +
      wt111 * _data[index111];
  } // for
} // _interpolate


// End of file
