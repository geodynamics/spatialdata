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

#include "SimpleDBData.hh" // Implementation of class methods

#include <cstring> // USES memcpy()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream

// ----------------------------------------------------------------------
// Default constructor
spatialdata::spatialdb::SimpleDBData::SimpleDBData(void) :
  _data(0),
  _coordinates(0),
  _names(0),
  _units(0),
  _numLocs(0),
  _numValues(0),
  _dataDim(0),
  _spaceDim(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::spatialdb::SimpleDBData::~SimpleDBData(void)
{ // destructor
  delete[] _data; _data = 0;
  delete[] _coordinates; _coordinates = 0;
  delete[] _names; _names = 0;
  delete[] _units; _units = 0;
  _numLocs = 0;
  _numValues = 0;
  _dataDim = 0;
  _spaceDim = 0;
} // destructor

// ----------------------------------------------------------------------
// Allocate data structues.
void
spatialdata::spatialdb::SimpleDBData::allocate(const int numLocs,
					       const int numValues,
					       const int spaceDim,
					       const int dataDim)
{ // allocate
  delete[] _data; _data = 0;
  delete[] _coordinates; _coordinates = 0;
  delete[] _names; _names = 0;
  delete[] _units; _units = 0;

  if (numLocs <= 0) {
    std::ostringstream msg;
    msg << "Number of locations (" << numLocs
	<< ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  if (numValues <= 0) {
    std::ostringstream msg;
    msg << "Number of values (" << numValues
	<< ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  if (spaceDim <= 0) {
    std::ostringstream msg;
    msg << "Number of spatial dimensions (" << spaceDim
	<< ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  if (dataDim < 0 || dataDim > 3) {
    std::ostringstream msg;
    msg << "Spatial dimension of data (" << dataDim
	<< ") must be in the range [0,3].";
    throw std::runtime_error(msg.str());
  } // if


  int size = numLocs*numValues;
  _data = (size > 0) ? new double[size] : 0;

  size = numLocs*spaceDim;
  _coordinates = (size > 0) ? new double[size] : 0;

  size = numValues;
  _names = (size > 0) ? new std::string[size] : 0;
  _units = (size > 0) ? new std::string[size] : 0; 

  _numLocs = numLocs;
  _numValues = numValues;
  _spaceDim = spaceDim;
  _dataDim = dataDim;
} // allocate

// ----------------------------------------------------------------------
// Set data values.
void
spatialdata::spatialdb::SimpleDBData::data(const double* values,
					   const int numLocs,
					   const int numValues)
{ // data
  assert(0 != values);
  assert(numLocs == _numLocs);
  assert(numValues == _numValues);
 
  memcpy(_data, values, numLocs*numValues*sizeof(double));
} // data

// ----------------------------------------------------------------------
// Set coordinates of locations.
void
spatialdata::spatialdb::SimpleDBData::coordinates(const double* values,
						  const int numLocs,
						  const int spaceDim)
{ // coordinates
  assert(0 != values);
  assert(numLocs == _numLocs);
  assert(spaceDim == _spaceDim);

  memcpy(_coordinates, values, numLocs*spaceDim*sizeof(double));
} // coordinates

// ----------------------------------------------------------------------
// Set names of values.
void
spatialdata::spatialdb::SimpleDBData::names(const char* const* values,
					    const int numValues)
{ // names
  assert(0 != values);
  assert(numValues == _numValues);

  for (int i=0; i < numValues; ++i)
    _names[i] = values[i];
} // names

// ----------------------------------------------------------------------
// Set units of values.
void
spatialdata::spatialdb::SimpleDBData::units(const char* const* values,
					    const int numValues)
{ // units
  assert(0 != values);
  assert(numValues == _numValues);

  for (int i=0; i < numValues; ++i)
    _units[i] = values[i];
} // units


// End of file 
