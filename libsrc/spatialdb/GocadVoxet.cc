// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

#include "GocadVoxet.hh" // Implementation of class methods

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <fstream> // USES std::ifstream
#include <math.h> // USES round()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <string.h> // USES memcpy() and strcmp()
#include <assert.h> // USES assert()

#if defined(WORDS_BIGENDIAN)
#define NATIVE_BIG_ENDIAN
#else
#define NATIVE_LITTLE_ENDIAN
#endif

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::GocadVoxet::GocadVoxet(void) :
  _data(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::GocadVoxet::~GocadVoxet(void)
{ // destructor
  delete[] _data; _data = 0;
} // destructor

// ----------------------------------------------------------------------
// Read data files.
void
spatialdata::spatialdb::GocadVoxet::read(const char* dir,
					 const char* filename,
					 const char* property)
{ // read
  std::string fullname;
  fullname = std::string(dir) + std::string("/") + std::string(filename);
  _readVoxetFile(fullname.c_str(), property);

  fullname = std::string(dir) + std::string("/") 
    + std::string(_property.filename);
  _readPropertyFile(fullname.c_str());
} // read

// ----------------------------------------------------------------------
// Query voxet for value.
int
spatialdata::spatialdb::GocadVoxet::query(double* value,
					  const double pt[3]) const
{ // query
  // Compute indices of voxet containing pt
  const int numX = _geometry.n[0];
  const int numY = _geometry.n[1];
  const int numZ = _geometry.n[2];
  const int indexX = 
    round( (pt[0] - (_geometry.o[0]+_geometry.min[0]))*_geometry.scale[0]);
  const int indexY = 
    round( (pt[1] - (_geometry.o[1]+_geometry.min[1]))*_geometry.scale[1]);
  const int indexZ = 
    round( (pt[2] - (_geometry.o[2]+_geometry.min[2]))*_geometry.scale[2]);

  // Check if voxet is in range
  int flag = 0;
  if (indexX >= 0 && indexX < numX &&
      indexY >= 0 && indexY < numY &&
      indexZ >= 0 && indexZ < numZ) {
    int indexV = indexZ*numY*numX + indexY*numX + indexX;
    *value = _data[indexV];

    // If voxet value is "no data value"
    if (fabs(1.0 - *value / _property.noDataValue) < 1.0e-6) {
      // If near indexZ=0, retry with indexZ+1, otherwise if near
      // indexZ=numZ, retry with indexZ-1.
      const int dz = (indexZ < numZ/2) ? +1 : -1;
      const int maxRetries = 32;
      for (int iTry=0; iTry < maxRetries; ++iTry) {
	const int indexZNew = indexZ + dz*iTry;
	assert(indexZNew >= 0 && indexZNew < numZ);
	indexV = indexZNew*numY*numX + indexY*numX + indexX;
	*value = _data[indexV];
	if (fabs(1.0 - *value / _property.noDataValue) > 1.0e-6)
	  break;
      } // for
    } // if
  } else {
    *value = _property.noDataValue;
    flag = 1;
  } // if/else

  return flag;
} // query

// ----------------------------------------------------------------------
// Query voxet for value at nearest location.
int
spatialdata::spatialdb::GocadVoxet::queryNearest(double* value,
						 const double pt[3]) const
{ // queryNearest
  // Compute indices of voxet containing pt
  const int numX = _geometry.n[0];
  const int numY = _geometry.n[1];
  const int numZ = _geometry.n[2];
  int indexX = 
    round( (pt[0] - (_geometry.o[0]+_geometry.min[0]))*_geometry.scale[0]);
  int indexY = 
    round( (pt[1] - (_geometry.o[1]+_geometry.min[1]))*_geometry.scale[1]);
  int indexZ = 
    round( (pt[2] - (_geometry.o[2]+_geometry.min[2]))*_geometry.scale[2]);

  // Correct to range of voxet, if necessary.
  int flag = 0;
  if (indexX < 0)
    indexX = 0;
  else if (indexX >= numX)
    indexX = numX - 1;
  if (indexY < 0)
    indexY = 0;
  else if (indexY >= numY)
    indexY = numY - 1;
  if (indexZ < 0)
    indexZ = 0;
  else if (indexZ >= numZ)
    indexZ = numZ - 1;

  // Make sure voxet is in range
  assert(indexX >= 0 && indexX < numX);
  assert(indexY >= 0 && indexY < numY);
  assert(indexZ >= 0 && indexZ < numZ);

  int indexV = indexZ*numY*numX + indexY*numX + indexX;
  *value = _data[indexV];

  return flag;
} // queryNearest

// ----------------------------------------------------------------------
// Read voxet file.
void
spatialdata::spatialdb::GocadVoxet::_readVoxetFile(const char* filename,
						   const char* propertyName)
{ // _readVoxetFile
  try {
    std::ifstream vfile(filename);
    if (!vfile.is_open() || !vfile.good()) {
      std::ostringstream msg;
      msg << "Could not open Gocad Voxet file '" << filename
	  << "' for reading.\n";
      throw std::runtime_error(msg.str());
    } // if

    utils::LineParser parser(vfile);
    parser.eatwhitespace(true);

    std::istringstream buffer;

    buffer.str(parser.next());
    buffer.clear();

    const char* headerE = "GOCAD Voxet 1";    
    const int headerLen = strlen(headerE);
    std::string hbuffer;
    hbuffer.resize(headerLen+1);
    buffer.read((char*) hbuffer.c_str(), sizeof(char)*headerLen);
    hbuffer[headerLen] = '\0';
    if (0 != strcmp(headerE, hbuffer.c_str())) {
      std::ostringstream msg;
      msg
	<< "Header '" << hbuffer << "' does not match expected header '"
	<< headerE << "' in Gocad Voxet file '" << filename << "'.\n";
      throw std::runtime_error(msg.str());
    } // if
    
    std::string token;
    const int maxIgnore = 256;

    _resetData();
    int propertyId = 0;
    int propertyIdTarget = -1;

    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (vfile.good() && !vfile.eof()) {
      if (0 == strcmp(token.c_str(), "AXIS_O"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.o[i];
      else if (0 == strcmp(token.c_str(), "AXIS_U"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.u[i];
      else if (0 == strcmp(token.c_str(), "AXIS_V"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.v[i];
      else if (0 == strcmp(token.c_str(), "AXIS_W"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.w[i];
      else if (0 == strcmp(token.c_str(), "AXIS_MIN"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.min[i];
      else if (0 == strcmp(token.c_str(), "AXIS_MAX"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.max[i];
      else if (0 == strcmp(token.c_str(), "AXIS_N"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.n[i];
      else if (0 == strcmp(token.c_str(), "AXIS_NAME"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.name[i];
      else if (0 == strcmp(token.c_str(), "AXIS_TYPE"))
	for (int i=0; i < 3; ++i)
	  buffer >> _geometry.type[i];

      else if (0 == strcmp(token.c_str(), "PROPERTY")) {
	std::string name;
	buffer >> propertyId;
	buffer >> name;
	if (0 == strcmp(name.c_str(), propertyName)) {
	  propertyIdTarget = propertyId;
	  _property.name = name;
	} // if
      } else if (0 == strcmp(token.c_str(), "PROP_NO_DATA_VALUE")) {
	buffer >> propertyId;
	if (propertyIdTarget == propertyId)
	  buffer >> _property.noDataValue;
      } else if (0 == strcmp(token.c_str(), "PROP_ESIZE")) {
	buffer >> propertyId;
	if (propertyIdTarget == propertyId)
	  buffer >> _property.esize;
      } else if (0 == strcmp(token.c_str(), "PROP_ETYPE")) {
	buffer >> propertyId;
	if (propertyIdTarget == propertyId)
	  buffer >> _property.etype;
      } else if (0 == strcmp(token.c_str(), "PROP_OFFSET")) {
	buffer >> propertyId;
	if (propertyIdTarget == propertyId)
	  buffer >> _property.offset;
      } else if (0 == strcmp(token.c_str(), "PROP_FILE")) {
	buffer >> propertyId;
	if (propertyIdTarget == propertyId)
	  buffer >> _property.filename;
      } else if (0 == strcmp(token.c_str(), "END"))
	break;
      
      buffer.str(parser.next());
      buffer.clear();
      buffer >> token;
    } // while
    if (token != "END" || !vfile.good())
      throw std::runtime_error("I/O error while parsing Gocad Voxet tokens.");
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while reading Gocad Voxet file '"
	<< filename << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while reading Gocad Voxet file '"
	<< filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch

  // Compute resolution
  assert(0 == _geometry.u[1] && 0 == _geometry.u[2]);
  assert(0 == _geometry.v[0] && 0 == _geometry.v[2]);
  assert(0 == _geometry.w[0] && 0 == _geometry.w[1]);
  const double lenX = _geometry.max[0]*_geometry.u[0] - _geometry.min[0];
  const double lenY = _geometry.max[1]*_geometry.v[1] - _geometry.min[1];
  const double lenZ = _geometry.max[2]*_geometry.w[2] - _geometry.min[2];
  _geometry.scale[0] = (lenX != 0.0) ? (_geometry.n[0]-1) / lenX : 1.0e+30;
  _geometry.scale[1] = (lenY != 0.0) ? (_geometry.n[1]-1) / lenY : 1.0e+30;
  _geometry.scale[2] = (lenZ != 0.0) ? (_geometry.n[2]-1) / lenZ : 1.0e+30;
} // _readVoxetFile

// ----------------------------------------------------------------------
// Read property data.
void
spatialdata::spatialdb::GocadVoxet::_readPropertyFile(const char* filename)
{ // _readPropertyFile
  assert(sizeof(float) == _property.esize);
  const int nvals = _geometry.n[0] * _geometry.n[1] * _geometry.n[2];
  delete[] _data; _data = new float[nvals];

  try {
    std::ifstream pfile(filename);
    if (!pfile.is_open() || !pfile.good()) {
      std::ostringstream msg;
      msg << "Could not open Gocad Voxet property file '" << filename
	  << "' for reading.\n";
      throw std::runtime_error(msg.str());
    } // if

    pfile.read((char*) _data, sizeof(float)*nvals);
    _endianBigToNative(_data, nvals);
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while reading Gocad Voxet property file '"
	<< filename << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while reading Gocad Voxet property file '"
	<< filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // _readPropertyFile

// ----------------------------------------------------------------------
// Convert array of float values from big endian to native float type.
void
spatialdata::spatialdb::GocadVoxet::_endianBigToNative(float* vals,
						       const int nvals) const
{ // _endianBigToNative
  assert(0 != vals);
#if defined(NATIVE_LITTLE_ENDIAN)
  for (int i=0; i < nvals; ++i) {
    char* buf = (char*) (vals + i);
    char tmp = buf[3];
    buf[3] = buf[0];
    buf[0] = tmp;
    tmp = buf[2];
    buf[2] = buf[1];
    buf[1] = tmp;
  } // for
#endif
} // _endianBigToNative

// ----------------------------------------------------------------------
// Reset class data.
void
spatialdata::spatialdb::GocadVoxet::_resetData(void)
{ // _resetData
  const float zero[] = { 0.0, 0.0, 0.0 };
  const float one[] = { 1.0, 1.0, 1.0 };

  memcpy(_geometry.o, zero, 3*sizeof(float));
  memcpy(_geometry.u, zero, 3*sizeof(float));
  memcpy(_geometry.v, zero, 3*sizeof(float));
  memcpy(_geometry.w, zero, 3*sizeof(float));
  memcpy(_geometry.min, zero, 3*sizeof(float));
  memcpy(_geometry.max, one, 3*sizeof(float));
  _geometry.name[0] = "";
  _geometry.name[1] = "";
  _geometry.name[2] = "";
  _geometry.type[0] = "";
  _geometry.type[1] = "";
  _geometry.type[2] = "";

  _property.name = "";
  _property.noDataValue = -99999;
  _property.esize = 4;
  _property.isSigned = 1;
  _property.etype = "IEEE";
  _property.offset = 0;
  _property.filename = "";

  delete[] _data; _data = 0;
} // _resetData


// End of file 
