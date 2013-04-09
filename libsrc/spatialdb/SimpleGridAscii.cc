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

#include "SimpleGridAscii.hh" // implementation of class methods

#include "SpatialDB.hh" // USES SimpleDB
#include "SimpleDB.hh" // USES SimpleDB

#include "SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPicklerAscii

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <fstream> // USES std::ofstream, std::ifstream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()
#include <cmath> // USES pow()
#include <algorithm> // USES std::sort()
#include <vector> // USES std::vector

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <string.h> // USES strlen()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
const char* spatialdata::spatialdb::SimpleGridAscii::FILEHEADER = "#SPATIAL_GRID.ascii";

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatialdata::spatialdb::SimpleGridAscii::read(SimpleGridDB* db)
{ // read
  assert(db);

  try {
    std::ifstream filein(db->_filename.c_str());
    if (!filein.is_open() || !filein.good()) {
      std::ostringstream msg;
      msg << "Could not open spatial database file '" << db->_filename
	  << "' for reading.\n";
      throw std::runtime_error(msg.str());
    } // if

    _readHeader(filein, db);
    _readData(filein, db);
    
    if (!filein.good())
      throw std::runtime_error("Unknown error while reading.");

    filein.close();
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while reading spatial database file '"
	<< db->_filename << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while reading spatial database file '"
	<< db->_filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // read


// ----------------------------------------------------------------------
// Write ascii database file.
void
spatialdata::spatialdb::SimpleGridAscii::write(const SimpleGridDB& db)
{ // write
  try {
    std::ofstream fileout(db._filename.c_str());
    if (!fileout.is_open() || !fileout.good()) {
      std::ostringstream msg;
      msg << "Could not open spatial database file '" << db._filename
	  << "' for writing.\n";
      throw std::runtime_error(msg.str());
    } // if
    
    _writeHeader(fileout, db);
    _writeData(fileout, db);
    
    if (!fileout.good())
      throw std::runtime_error("Unknown error while writing.");

    fileout.close();
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while writing spatial database file '"
	<< db._filename << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while writing spatial database file '"
	<< db._filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // write


// ----------------------------------------------------------------------
// Read data file header.
void
spatialdata::spatialdb::SimpleGridAscii::_readHeader(std::istream& filein,
						     SimpleGridDB* const db)
{ // _readHeader
  assert(db);

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
      << FILEHEADER << "' in spatial database file '" << db->_filename << "'.\n";
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

  db->_numX = 0;
  db->_numY = 0;
  db->_numZ = 0;
  delete[] db->_x; db->_x = 0;
  delete[] db->_y; db->_y = 0;
  delete[] db->_z; db->_z = 0;
  
  db->_numValues = 0;
  delete[] db->_names; db->_names = 0;
  delete[] db->_units; db->_units = 0;

  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  while (buffer.good() && token != "}") {
    if (0 == strcasecmp(token.c_str(), "num-x")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> db->_numX;
    } else if (0 == strcasecmp(token.c_str(), "num-y")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> db->_numY;
    } else if (0 == strcasecmp(token.c_str(), "num-z")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> db->_numZ;
    } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> db->_spaceDim;
    } else if (0 == strcasecmp(token.c_str(), "num-values")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> db->_numValues;
    } else if (0 == strcasecmp(token.c_str(), "value-names")) {
      if (db->_numValues > 0) {
	db->_names = new std::string[db->_numValues];
      } else
	throw std::runtime_error("Number of values must be specified BEFORE "
				 "names of values in SimpleGridDB file.");
      buffer.ignore(maxIgnore, '=');
      for (int iVal=0; iVal < db->_numValues; ++iVal)
	buffer >> db->_names[iVal];
    } else if (0 == strcasecmp(token.c_str(), "value-units")) {
      if (db->_numValues > 0) {
	db->_units = new std::string[db->_numValues];
      } else
	throw std::runtime_error("Number of values must be specified BEFORE "
				 "units of values in SimpleGridDB file.");
      buffer.ignore(maxIgnore, '=');
      for (int iVal=0; iVal < db->_numValues; ++iVal)
	buffer >> db->_units[iVal];
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
      spatialdata::geocoords::CSPicklerAscii::unpickle(filein, &db->_cs);
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
  if (db->_numValues <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-values'.\n";
  } // if
  if (db->_spaceDim <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include positive 'space-dim'.\n";
  } // if

  if (db->_spaceDim > 0 && db->_numX <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-x'.\n";
  } // if
  if (db->_spaceDim > 1 && db->_numY <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-y' with 2-D and 3-D data.\n";
  } // if
  if (db->_spaceDim > 2 && db->_numZ <= 0) {
    ok = false;
    msg << "SimpleGridDB settings must include 'num-z' with 3-D data.\n";
  } // if
  if (!db->_names) {
    ok = false;
    msg << "SimpleGridDB settings must include 'value-names'.\n";
  } // if
  if (!db->_units) {
    ok = false;
    msg << "SimpleGridDB settings must include 'value-units'.\n";
  } // if
  if (!ok)
    throw std::runtime_error(msg.str());

  // Set data dimension based on dimensions of data.
  db->_dataDim = 0;
  if (db->_numX > 1) {
    db->_dataDim += 1;
  } // if
  if (db->_numY > 1) {
    db->_dataDim += 1;
  } // if
  if (db->_numZ > 1) {
    db->_dataDim += 1;
  } // if

  assert(db->_cs);
  db->_cs->initialize();
} // _readHeader

#include <iostream>
// ----------------------------------------------------------------------
// Read data values.
void
spatialdata::spatialdb::SimpleGridAscii::_readData(std::istream& filein,
						   SimpleGridDB* const db)
{ // _readData
  delete[] db->_x; db->_x = 0;
  delete[] db->_y; db->_y = 0;
  delete[] db->_z; db->_z = 0;
  delete[] db->_data; db->_data = 0;

  const int numX = db->_numX;
  const int numY = db->_numY;
  const int numZ = db->_numZ;
  const int numValues = db->_numValues;
  const int spaceDim = db->_spaceDim;

  const int bufsize = 32768;
  utils::LineParser parser(filein, "//", bufsize);
  parser.eatwhitespace(true);

  std::istringstream buffer;

  int numLocs = 1;
  if (numX >= 1) {
    numLocs *= numX;
    db->_x = new double[numX];
    buffer.str(parser.next());
    buffer.clear();
    for (int i=0; i < numX; ++i) {
      buffer >> db->_x[i];
    } // for
    std::vector<double> xVec(numX);
    for (int i=0; i < numX; ++i)
      xVec[i] = db->_x[i];
    std::sort(xVec.begin(), xVec.end());
    for (int i=0; i < numX; ++i)
      db->_x[i] = xVec[i];
  } // if

  if (numY >= 1) {
    numLocs *= numY;
    db->_y = new double[numY];
    buffer.str(parser.next());
    buffer.clear();
    for (int i=0; i < numY; ++i) {
      buffer >> db->_y[i];
    } // for
    std::vector<double> yVec(numY);
    for (int i=0; i < numY; ++i)
      yVec[i] = db->_y[i];
    std::sort(yVec.begin(), yVec.end());
    for (int i=0; i < numY; ++i)
      db->_y[i] = yVec[i];
  } // if

  if (numZ >= 1) {
    numLocs *= numZ;
    db->_z = new double[numZ];
    buffer.str(parser.next());
    buffer.clear();
    for (int i=0; i < numZ; ++i) {
      buffer >> db->_z[i];
    } // for
    std::vector<double> zVec(numZ);
    for (int i=0; i < numZ; ++i)
      zVec[i] = db->_z[i];
    std::sort(zVec.begin(), zVec.end());
    for (int i=0; i < numZ; ++i)
      db->_z[i] = zVec[i];
  } // if

  assert(numLocs > 0);
  assert(numValues > 0);
  db->_data = new double[numLocs*db->_numValues];
  assert(spaceDim > 0);
  double* coords = new double[spaceDim];
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    buffer.str(parser.next());
    buffer.clear();
    for (int iDim=0; iDim < spaceDim; ++iDim) {
      buffer >> coords[iDim];
    } // for

    const int indexData = db->_dataIndex(coords, spaceDim);
    for (int iVal=0; iVal < db->_numValues; ++iVal) {
      buffer >> db->_data[indexData+iVal];
    } // for
    if (buffer.bad()) {
      throw std::runtime_error("Error reading points.");
    } // if
  } // for
  delete[] coords; coords = 0;
  if (!filein.good())
    throw std::runtime_error("I/O error while reading SimpleGridDB data.");

  // Set dimensions without any data to 1.
  if (0 == db->_numX) {
    db->_numX = 1;
  } // if
  if (0 == db->_numY) {
    db->_numY = 1;
  } // if
  if (0 == db->_numZ) {
    db->_numZ = 1;
  } // if

  // Check compatibility of dimension of data, spatial dimension and
  // number of points
  db->_checkCompatibility();
} // _readData

// ----------------------------------------------------------------------
// Write the data file header.
void
spatialdata::spatialdb::SimpleGridAscii::_writeHeader(std::ostream& fileout,
						      const SimpleGridDB& db)
{ // _writeHeader
  const int version = 1;
  const int numValues = db._numValues;
  const int spaceDim = db._spaceDim;
    
  fileout
    << FILEHEADER << " " << version << "\n"
    << "SimpleGridDB {\n"
    << "  num-x = " << db._numX << "\n"
    << "  num-y = " << db._numY << "\n"
    << "  num-z = " << db._numZ << "\n"
    << "  space-dim = " << spaceDim << "\n"
    << "  num-values = " << numValues << "\n"
    << "  value-names =";

  assert(db._names);
  for (int iVal=0; iVal < numValues; ++iVal)
    fileout << "  " << db._names[iVal];
  fileout << "\n";

  assert(db._units);
  fileout << "  value-units =";
  for (int iVal=0; iVal < numValues; ++iVal)
    fileout << "  " << db._units[iVal];
  fileout << "\n";
  fileout << "  cs-data = ";
  spatialdata::geocoords::CSPicklerAscii::pickle(fileout, db._cs);
  fileout << "}\n";

  if (!fileout.good())
    throw std::runtime_error("I/O error while writing SimpleGridDB settings.");
} // _writeHeader
  

// ----------------------------------------------------------------------
// Write data values.
void
spatialdata::spatialdb::SimpleGridAscii::_writeData(std::ostream& fileout,
						    const SimpleGridDB& db)
{ // _writeData
  fileout
    << std::resetiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::scientific)
    << std::setprecision(6);

  const int numX = db._numX;
  const int numY = db._numY;
  const int numZ = db._numZ;
  const int numValues = db._numValues;

  fileout << "// x-coordinates\n";
  for (int i=0; i < numX; ++i) {
    fileout << std::setw(14) << db._x[i];
  } // for
  fileout << "\n";
  
  fileout << "// y-coordinates\n";
  for (int i=0; i < numY; ++i) {
    fileout << std::setw(14) << db._y[i];
  } // for
  fileout << "\n";
  
  fileout << "// z-coordinates\n";
  for (int i=0; i < numZ; ++i) {
    fileout << std::setw(14) << db._z[i];
  } // for
  fileout << "\n";

  fileout << "// data\n";
  for (int iZ=0; iZ < numZ; ++iZ) {
    for (int iY=0; iY < numY; ++iY) {
      for (int iX=0; iX < numX; ++iX) {
	const int iD = db._dataIndex(iX, numX, iY, numY, iZ, numZ);
	fileout 
	  << std::setw(14) << db._x[iX]
	  << std::setw(14) << db._y[iY]
	  << std::setw(14) << db._z[iZ];
	for (int iV=0; iV < numValues; ++iV) {
	  fileout << std::setw(14) << db._data[iD+iV];
	} // for
	fileout << "\n";
      } // for
    } // for
  } // for
} // _writeData


// End of file 
