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

#include "SimpleGridDB.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/Projector.hh" // USES Projector
#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPicklerAscii
#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <math.h> // USES pow()
#include <algorithm> // USES std::sort()
#include <vector> // USES std::vector

#include <fstream> // USES std::ifstream
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <string.h> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
const char* spatialdata::spatialdb::SimpleGridDB::FILEHEADER = "#SPATIAL_GRID.ascii";

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SimpleGridDB::SimpleGridDB(void) :
  _data(0),
  _x(0),
  _y(0),
  _z(0),
  _queryVals(0),
  _querySize(0),
  _numX(0),
  _numY(0),
  _numZ(0),
  _dataDim(0),
  _spaceDim(0),
  _numValues(0),
  _names(0),
  _units(0),
  _filename(""),
  _cs(new geocoords::CSGeoProj),
  _queryType(NEAREST)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SimpleGridDB::~SimpleGridDB(void)
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
// Set filename containing data.
void
spatialdata::spatialdb::SimpleGridDB::filename(const char* value)
{ // filename
  _filename = value;
} // filename
 
// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::SimpleGridDB::open(void)
{ // open
  try {
    std::ifstream filein(_filename.c_str());
    if (!filein.is_open() || !filein.good()) {
      std::ostringstream msg;
      msg << "Could not open spatial database file '" << _filename
	  << "' for reading.\n";
      throw std::runtime_error(msg.str());
    } // if

    _readHeader(filein);
    _readData(filein);
    
    if (!filein.good())
      throw std::runtime_error("Unknown error while reading.");
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while reading spatial database file '"
	<< _filename << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while reading spatial database file '"
	<< _filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // open

// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::SimpleGridDB::close(void)
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
spatialdata::spatialdb::SimpleGridDB::queryType(const QueryEnum value)
{ // queryType
  _queryType = value;
} // queryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleGridDB::queryVals(const char* const* names,
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
	<< "Could not find value " << names[iVal] << " in spatial database "
	<< label() << ". Available values are:";
      for (int iName=0; iName < numNames; ++iName)
	msg << "\n  " << _names[iName];
      msg << "\n";
      throw std::runtime_error(msg.str());
    } // if
    _queryVals[iVal] = iName;
  } // for
} // queryVals

#include <iostream>
// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SimpleGridDB::query(double* vals,
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
  } else if (numDims != _spaceDim) {
    std::ostringstream msg;
    msg
      << "Spatial dimension (" << numDims
      << ") does not match spatial dimension of spatial database (" << _spaceDim << ").";
    throw std::runtime_error(msg.str());
  } // if

  // Convert coordinates
  assert(numDims <= 3);
  memcpy(_xyz, coords, numDims*sizeof(double));
  spatialdata::geocoords::Converter::convert(_xyz, 1, numDims, _cs, csQuery);

  int queryFlag = 0;
  const int spaceDim = _spaceDim;

  double indexX = 0.0;
  double indexY = 0.0;
  double indexZ = 0.0;
  int numX = 0;
  int numY = 0;
  int numZ = 0;
  if (3 == spaceDim) {
    indexX = _search(_xyz[0], _x, _numX);
    indexY = _search(_xyz[1], _y, _numY);
    indexZ = _search(_xyz[2], _z, _numZ);
    numX = _numX;
    numY = _numY;
    numZ = _numZ;
    if (2 == _dataDim) {
      if (1 == _numX) {
	indexX = indexY;
	numX = _numY;
	indexY = indexZ;
	numY = _numZ;
	indexZ = 0;
      } else if (1 == numY) {
	indexY = indexZ;
	numY = _numZ;
	indexZ = 0;
      } // if/else
    } else if (1 == _dataDim) {
      if (_numY > 1) {
	indexX = indexY;
	numX = _numY;
	indexY = 0;
      } else if (_numZ > 1) {
	indexX = indexZ;
	numX = _numZ;
	indexZ = 0;
      } // if
    } // if
  } else if (2 == spaceDim) {
    indexX = _search(_xyz[0], _x, _numX);
    indexY = _search(_xyz[1], _y, _numY);
    numX = _numX;
    numY = _numY;
    if (1 == _dataDim && 1 == _numX) {
      indexX = indexY;
      numX = _numY;
      indexY = 0;
    } // if
  } else { // else
    assert(1 == spaceDim);
    indexX = _search(_xyz[0], _x, _numX);
    numX = _numX;
  } // if/else
  if (-1.0 == indexX || -1.0 == indexY || -1.0 == indexZ) {
    queryFlag = 1;
    return queryFlag;
  } // if
  
  switch (_queryType) {
  case LINEAR : 
    switch (_dataDim) {
    case 1: {
      _interpolate1D(vals, numVals, indexX, numX);
      break;
    } // case 1
    case 2: {
      _interpolate2D(vals, numVals, indexX, numX, indexY, numY);
      break;
    } // case 2
    case 3 : {
      _interpolate3D(vals, numVals, indexX, indexY, indexZ);
      break;
    } // case 3
    default :
      assert(false);
      throw std::logic_error("Unsupported data dimension in SimpleGridDB::query().");
    } // switch
    break;
  case NEAREST : {
    const int indexNearestX = int(floor(indexX+0.5));
    const int indexNearestY = int(floor(indexY+0.5));
    const int indexNearestZ = int(floor(indexZ+0.5));
    const int indexData = _dataIndex(indexNearestX, indexNearestY, indexNearestZ);
    for (int iVal=0; iVal < querySize; ++iVal) {
      vals[iVal] = _data[indexData+_queryVals[iVal]];
#if 0 // DEBUGGING
    std::cout << "val["<<iVal<<"]: " << vals[iVal]
	      << ", indexData: " << indexData
	      << ", indexX: " << indexX
	      << ", indexY: " << indexY
	      << ", indexZ: " << indexZ
	      << std::endl;
#endif
    } // for
    break;
  } // NEAREST
  default :
    assert(false);
    throw std::logic_error("Unsupported query type in SimpleGridDB::query().");
  } // switch
    
  return queryFlag;
} // query

// ----------------------------------------------------------------------
// Read data file header.
void
spatialdata::spatialdb::SimpleGridDB::_readHeader(std::istream& filein)
{ // _readHeader
  utils::LineParser parser(filein, "//");
  parser.eatwhitespace(true);

  std::istringstream buffer;

  buffer.str(parser.next());
  buffer.clear();

  const int headerLen = strlen(FILEHEADER);
  std::string hbuffer;
  hbuffer.resize(headerLen+1);
  buffer.read((char*) hbuffer.c_str(), sizeof(char)*headerLen);
  hbuffer[headerLen] = '\0';
  if (0 != strcasecmp(FILEHEADER, hbuffer.c_str())) {
    std::ostringstream msg;
    msg
      << "Magic header '" << buffer << "' does not match expected header '"
      << FILEHEADER << "' in spatial database file '" << _filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // if

  std::string token;
  const int maxIgnore = 256;

  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  if (0 != strcasecmp(token.c_str(), "SimpleGridDB")) {
    std::ostringstream msg;
    msg << "Could not parse '" << token << "' into 'SimpleGridDB'.\n";
    throw std::runtime_error(msg.str());
  } // else

  _numX = 0;
  _numY = 0;
  _numZ = 0;
  delete[] _x; _x = 0;
  delete[] _y; _y = 0;
  delete[] _z; _z = 0;
  
  _numValues = 0;
  delete[] _names; _names = 0;
  delete[] _units; _units = 0;

  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  while (buffer.good() && token != "}") {
    if (0 == strcasecmp(token.c_str(), "num-x")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> _numX;
    } else if (0 == strcasecmp(token.c_str(), "num-y")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> _numY;
    } else if (0 == strcasecmp(token.c_str(), "num-z")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> _numZ;
    } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> _spaceDim;
    } else if (0 == strcasecmp(token.c_str(), "num-values")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> _numValues;
    } else if (0 == strcasecmp(token.c_str(), "value-names")) {
      if (_numValues > 0) {
	_names = new std::string[_numValues];
      } else
	throw std::runtime_error("Number of values must be specified BEFORE "
				 "names of values in SimpleGridDB file.");
      buffer.ignore(maxIgnore, '=');
      for (int iVal=0; iVal < _numValues; ++iVal)
	buffer >> _names[iVal];
    } else if (0 == strcasecmp(token.c_str(), "value-units")) {
      if (_numValues > 0) {
	_units = new std::string[_numValues];
      } else
	throw std::runtime_error("Number of values must be specified BEFORE "
				 "units of values in SimpleGridDB file.");
      buffer.ignore(maxIgnore, '=');
      for (int iVal=0; iVal < _numValues; ++iVal)
	buffer >> _units[iVal];
    } else if (0 == strcasecmp(token.c_str(), "cs-data")) {
      buffer.ignore(maxIgnore, '=');
      std::string rbuffer(buffer.str());
      filein.putback('\n');
      filein.clear();
      int i = rbuffer.length()-1;
      while (i >= 0) {
	filein.putback(rbuffer[i]);
	if ('=' == rbuffer[i--])
	  break;
      } // while
      filein.clear();
      spatialdata::geocoords::CSPicklerAscii::unpickle(filein, &_cs);
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a SimpleGridDB setting.";
      throw std::runtime_error(msg.str());
    } // else
    
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
  } // while
  if (token != "}" || !filein.good())
    throw std::runtime_error("I/O error while parsing SimpleGridDB settings.");
  
  bool ok = true;
  std::ostringstream msg;
  if (_numValues <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-values'.\n";
  } // if
  if (_spaceDim <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include positive 'space-dim'.\n";
  } // if

  if (_spaceDim > 0 && _numX <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-x'.\n";
  } // if
  if (_spaceDim > 1 && _numY <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-y' with 2-D and 3-D data.\n";
  } // if
  if (_spaceDim > 2 && _numZ <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-z' with 3-D data.\n";
  } // if
  if (!_names) {
    ok = false;
    msg << "SimpleGridDB settings must include 'value-names'.\n";
  } // if
  if (!_units) {
    ok = false;
    msg << "SimpleGridDB settings must include 'value-units'.\n";
  } // if
  if (!ok)
    throw std::runtime_error(msg.str());

  // Set data dimension based on dimensions of data.
  _dataDim = 0;
  if (_numX > 1) {
    _dataDim += 1;
  } // if
  if (_numY > 1) {
    _dataDim += 1;
  } // if
  if (_numZ > 1) {
    _dataDim += 1;
  } // if

  assert(_cs);
  _cs->initialize();
} // _readHeader

// ----------------------------------------------------------------------
// Read data values.
void
spatialdata::spatialdb::SimpleGridDB::_readData(std::istream& filein)
{ // _readData
  delete[] _x; _x = 0;
  delete[] _y; _y = 0;
  delete[] _z; _z = 0;
  delete[] _data; _data = 0;

  const int numX = _numX;
  const int numY = _numY;
  const int numZ = _numZ;
  const int numValues = _numValues;
  const int spaceDim = _spaceDim;

  utils::LineParser parser(filein, "//");
  parser.eatwhitespace(true);

  std::istringstream buffer;

  int numLocs = 1;
  if (numX >= 1) {
    numLocs *= numX;
    _x = new double[numX];
    buffer.str(parser.next());
    buffer.clear();
    for (int i=0; i < numX; ++i) {
      buffer >> _x[i];
    } // for
    std::vector<double> xVec(numX);
    for (int i=0; i < numX; ++i)
      xVec[i] = _x[i];
    std::sort(xVec.begin(), xVec.end());
    for (int i=0; i < numX; ++i)
      _x[i] = xVec[i];
  } // if

  if (numY >= 1) {
    numLocs *= numY;
    _y = new double[numY];
    buffer.str(parser.next());
    buffer.clear();
    for (int i=0; i < numY; ++i) {
      buffer >> _y[i];
    } // for
    std::vector<double> yVec(numY);
    for (int i=0; i < numY; ++i)
      yVec[i] = _y[i];
    std::sort(yVec.begin(), yVec.end());
    for (int i=0; i < numY; ++i)
      _y[i] = yVec[i];
  } // if

  if (numZ >= 1) {
    numLocs *= numZ;
    _z = new double[numZ];
    buffer.str(parser.next());
    buffer.clear();
    for (int i=0; i < numZ; ++i) {
      buffer >> _z[i];
    } // for
    std::vector<double> zVec(numZ);
    for (int i=0; i < numZ; ++i)
      zVec[i] = _z[i];
    std::sort(zVec.begin(), zVec.end());
    for (int i=0; i < numZ; ++i)
      _z[i] = zVec[i];
  } // if

  assert(numLocs > 0);
  assert(numValues > 0);
  _data = new double[numLocs*_numValues];
  assert(spaceDim > 0);
  double* coords = new double[spaceDim];
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    buffer.str(parser.next());
    buffer.clear();
    for (int iDim=0; iDim < spaceDim; ++iDim) {
      buffer >> coords[iDim];
    } // for
    
    int indexX = 0;
    int indexY = 0;
    int indexZ = 0;
    if (spaceDim > 2) {
      indexX = int(floor(_search(coords[0], _x, numX)+0.5));
      indexY = int(floor(_search(coords[1], _y, numY)+0.5));
      indexZ = int(floor(_search(coords[2], _z, numZ)+0.5));
    } else if (spaceDim > 1) {
      indexX = int(floor(_search(coords[0], _x, numX)+0.5));
      indexY = int(floor(_search(coords[1], _y, numY)+0.5));
    } else {
      assert(1 == spaceDim);
      indexX = int(floor(_search(coords[0], _x, numX)+0.5));
    } // if
    
    const int indexData = _dataIndex(indexX, indexY, indexZ);
    for (int iVal=0; iVal < _numValues; ++iVal) {
      buffer >> _data[indexData+iVal];
    } // for
    if (buffer.bad()) {
      throw std::runtime_error("Error reading points.");
    } // if
  } // for
  if (!filein.good())
    throw std::runtime_error("I/O error while reading SimpleGridDB data.");

  // Set dimensions without any data to 1.
  if (0 == _numX) {
    _numX = 1;
  } // if
  if (0 == _numY) {
    _numY = 1;
  } // if
  if (0 == _numZ) {
    _numZ = 1;
  } // if

  // Check compatibility of dimension of data, spatial dimension and
  // number of points
  _checkCompatibility();

  // Convert to SI units
  SpatialDB::_convertToSI(_data, _units, numLocs, _numValues);  
} // _readData

// ----------------------------------------------------------------------
/// Check compatibility of spatial database parameters.
void
spatialdata::spatialdb::SimpleGridDB::_checkCompatibility(void) const
{ // _checkCompatibility
  const int spaceDim = _spaceDim;
  const int dataDim = _dataDim;
  std::ostringstream msg;

  const int numX = _numX;
  const int numY = _numY;
  const int numZ = _numZ;

  int count1 = 0;
  if (1 == numX) {
    count1 += 1;
  } // if
  if (1 == numY) {
    count1 += 1;
  } // if
  if (1 == numZ) {
    count1 += 1;
  } // if

  if (0 == dataDim && 3 != count1) {
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") is incompatible with dimensions of a 0-D grid  ("
	<< numX << "," << numY << "," << numZ << ").";
    throw std::runtime_error(msg.str());

  } else if (1 == dataDim && 2 != count1) {
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") is incompatible with dimensions of a 1-D grid  ("
	<< numX << "," << numY << "," << numZ << ").";
    throw std::runtime_error(msg.str());

  } else if (2 == dataDim && 1 != count1) {
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") is incompatible with dimensions of a 2-D grid  ("
	<< numX << "," << numY << "," << numZ << ").";
    throw std::runtime_error(msg.str());

  } else if (3 == dataDim && 0 != count1) {
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") is incompatible with dimensions of a 3-D grid  ("
	<< numX << "," << numY << "," << numZ << ").";
    throw std::runtime_error(msg.str());
  } // if/else

  if (dataDim > spaceDim) {
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") exceeds the number of dimensions of the coordinates ("
	<< spaceDim << ").";
    throw std::runtime_error(msg.str());
  } // if

  if (spaceDim != _cs->spaceDim()) {
    msg << "Number of dimensions in coordinates of spatial distribution ("
	<< spaceDim << ") does not match number of dimensions in coordinate "
	<< "system (" << _cs->spaceDim() << ")";
    throw std::runtime_error(msg.str());
  } // if
} // _checkCompatibility

// ----------------------------------------------------------------------
// Bilinear search for coordinate.
double
spatialdata::spatialdb::SimpleGridDB::_search(const double target,
					      const double* vals,
					      const int nvals)
{ // _search
  if (1 == nvals) {
    return 0.0;
  } // if

  assert(vals);
  assert(nvals > 0);

  double index = -1.0;
  int indexL = 0;
  int indexR = nvals - 1;
  const double tolerance = 1.0e-6;
  if (target >= vals[indexL]-tolerance && target <= vals[indexR]+tolerance) {
    while (indexR - indexL > 1) {
      int indexM = indexL + (indexR-indexL) / 2;
      if (target < vals[indexM]) {
	indexR = indexM;
      } else {
	indexL = indexM;
      } // if/else
    } // while
    assert(target >= vals[indexL]-tolerance);
    assert(vals[indexR] > vals[indexL]);
    index = double(indexL) + (target - vals[indexL]) / (vals[indexR] - vals[indexL]);
  } else if (_queryType == NEAREST) {
    if (target <= vals[indexL]) {
      index = 0.0;
    } else {
      index = double(nvals-1);
    } // if/else
  } // if/else

  return index;
} // _search

// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices in 1-D.
void
spatialdata::spatialdb::SimpleGridDB::_interpolate1D(double* vals,
						     const int numVals,
						     const double indexX,
						     const int numX) const
{ // _interpolate1D
  assert(numX >= 2);
  const int indexX0 = std::min(numX-2, int(floor(indexX)));
  const double wtX0 = 1.0 - (indexX - indexX0);
  const int indexX1 = indexX0 + 1;
  const double wtX1 = 1.0 - wtX0;
  assert(0 <= indexX0 && indexX0 < numX);
  assert(0 <= indexX1 && indexX1 < numX);

  const int index000 = _dataIndex(indexX0, 0, 0);
  const int index100 = _dataIndex(indexX1, 0, 0);

  const double wt000 = wtX0;
  const double wt100 = wtX1;

  const int querySize = _querySize;
  for (int iVal=0; iVal < querySize; ++iVal) {
    const int qVal = _queryVals[iVal];
    vals[iVal] = 
      wt000 * _data[index000+qVal] +
      wt100 * _data[index100+qVal];
#if 0 // DEBUGGING
    std::cout << "val["<<iVal<<"]: " << vals[iVal]
	      << ", wt000: " << wt000 << ", data: " << _data[index000+qVal]
	      << ", wt100: " << wt100 << ", data: " << _data[index100+qVal]
	      << std::endl;
#endif
  } // for

} // _interpolate1D


// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices in 2-D.
void
spatialdata::spatialdb::SimpleGridDB::_interpolate2D(double* vals,
						     const int numVals,
						     const double indexX,
						     const int numX,
						     const double indexY,
						     const int numY) const
{ // _interpolate2D
  assert(numX >= 2);
  const int indexX0 = std::min(numX-2, int(floor(indexX)));
  const double wtX0 = 1.0 - (indexX - indexX0);
  const int indexX1 = indexX0 + 1;
  const double wtX1 = 1.0 - wtX0;
  assert(0 <= indexX0 && indexX0 < numX);
  assert(0 <= indexX1 && indexX1 < numX);

  assert(numY >= 2);
  const int indexY0 = std::min(numY-2, int(floor(indexY)));
  const double wtY0 = 1.0 - (indexY - indexY0);
  const int indexY1 = indexY0 + 1;
  const double wtY1 = 1.0 - wtY0;
  assert(0 <= indexY0 && indexY0 < numY);
  assert(0 <= indexY1 && indexY1 < numY);
  
  const int index000 = _dataIndex(indexX0, indexY0, 0);
  const int index010 = _dataIndex(indexX0, indexY1, 0);
  const int index100 = _dataIndex(indexX1, indexY0, 0);
  const int index110 = _dataIndex(indexX1, indexY1, 0);

  const double wt000 = wtX0 * wtY0;
  const double wt010 = wtX0 * wtY1;
  const double wt100 = wtX1 * wtY0;
  const double wt110 = wtX1 * wtY1;

  const int querySize = _querySize;
  for (int iVal=0; iVal < querySize; ++iVal) {
    const int qVal = _queryVals[iVal];
    vals[iVal] = 
      wt000 * _data[index000+qVal] +
      wt010 * _data[index010+qVal] +
      wt100 * _data[index100+qVal] +
      wt110 * _data[index110+qVal];
#if 0 // DEBUGGING
    std::cout << "val["<<iVal<<"]: " << vals[iVal]
	      << ", wt000: " << wt000 << ", data: " << _data[index000+qVal]
	      << ", wt010: " << wt010 << ", data: " << _data[index010+qVal]
	      << ", wt100: " << wt100 << ", data: " << _data[index100+qVal]
	      << ", wt110: " << wt110 << ", data: " << _data[index110+qVal]
	      << std::endl;
#endif
  } // for

} // _interpolate2D


// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices in 3-D.
void
spatialdata::spatialdb::SimpleGridDB::_interpolate3D(double* vals,
						      const int numVals,
						      const double indexX,
						      const double indexY,
						      const double indexZ) const
{ // _interpolate3D
  const int numX = _numX;
  const int numY = _numY;
  const int numZ = _numZ;

  assert(numX >= 2);
  const int indexX0 = std::min(numX-2, int(floor(indexX)));
  const double wtX0 = 1.0 - (indexX - indexX0);
  const int indexX1 = indexX0 + 1;
  const double wtX1 = 1.0 - wtX0;
  assert(0 <= indexX0 && indexX0 < numX);
  assert(0 <= indexX1 && indexX1 < numX);

  assert(numY >= 2);
  const int indexY0 = std::min(numY-2, int(floor(indexY)));
  const double wtY0 = 1.0 - (indexY - indexY0);
  const int indexY1 = indexY0 + 1;
  const double wtY1 = 1.0 - wtY0;
  assert(0 <= indexY0 && indexY0 < numY);
  assert(0 <= indexY1 && indexY1 < numY);
  
  assert(numZ >= 2);
  const int indexZ0 = std::min(numZ-2, int(floor(indexZ)));
  const double wtZ0 = 1.0 - (indexZ - indexZ0);
  const int indexZ1 = indexZ0 + 1;
  const double wtZ1 = 1.0 - wtZ0;
  assert(0 <= indexZ0 && indexZ0 < numZ);
  assert(0 <= indexZ1 && indexZ1 < numZ);

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

  const int querySize = _querySize;
  for (int iVal=0; iVal < querySize; ++iVal) {
    const int qVal = _queryVals[iVal];
    vals[iVal] = 
      wt000 * _data[index000+qVal] +
      wt001 * _data[index001+qVal] +
      wt010 * _data[index010+qVal] +
      wt011 * _data[index011+qVal] +
      wt100 * _data[index100+qVal] +
      wt101 * _data[index101+qVal] +
      wt110 * _data[index110+qVal] +
      wt111 * _data[index111+qVal];
#if 0 // DEBUGGING
    std::cout << "val["<<iVal<<"]: " << vals[iVal]
	      << ", wt000: " << wt000 << ", data: " << _data[index000+qVal]
	      << ", wt001: " << wt001 << ", data: " << _data[index001+qVal]
	      << ", wt010: " << wt010 << ", data: " << _data[index010+qVal]
	      << ", wt011: " << wt011 << ", data: " << _data[index011+qVal]
	      << ", wt100: " << wt100 << ", data: " << _data[index100+qVal]
	      << ", wt101: " << wt101 << ", data: " << _data[index101+qVal]
	      << ", wt110: " << wt110 << ", data: " << _data[index110+qVal]
	      << ", wt111: " << wt111 << ", data: " << _data[index111+qVal]
	      << std::endl;
#endif
  } // for

} // _interpolate3D


// End of file
