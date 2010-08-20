// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "SimpleIOAscii.hh" // implementation of class methods

#include "SpatialDB.hh" // USES SimpleDB
#include "SimpleDB.hh" // USES SimpleDB

#include "SimpleDBData.hh" // USES SimpleDBData
#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPicklerAscii

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <fstream> // USES std::ofstream, std::ifstream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <string.h> // USES strlen()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
const char* spatialdata::spatialdb::SimpleIOAscii::HEADER =
  "#SPATIAL.ascii";

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::read(
				   SimpleDBData* pData,
				   spatialdata::geocoords::CoordSys** ppCS)
{ // read
  assert(0 != pData);

  try {
    std::ifstream filein(filename());
    if (!filein.is_open() || !filein.good()) {
      std::ostringstream msg;
      msg << "Could not open spatial database file '" << filename()
	  << "' for reading.\n";
      throw std::runtime_error(msg.str());
    } // if

    utils::LineParser parser(filein, "//");
    parser.eatwhitespace(true);

    std::istringstream buffer;

    buffer.str(parser.next());
    buffer.clear();

    const int headerLen = strlen(HEADER);
    std::string hbuffer;
    hbuffer.resize(headerLen+1);
    buffer.read((char*) hbuffer.c_str(), sizeof(char)*headerLen);
    hbuffer[headerLen] = '\0';
    if (0 != strcasecmp(HEADER, hbuffer.c_str())) {
      std::ostringstream msg;
      msg
	<< "Magic header '" << buffer << "' does not match expected header '"
	<< HEADER << "' in spatial database file '" << filename() << "'.\n";
      throw std::runtime_error(msg.str());
    } // if
    int version = 0;
    buffer >> version;
    switch (version)
      { // switch
      case 1 :
	_readV1(pData, ppCS, filein);
	break;
      default :
	{ // default
	  std::ostringstream msg;
	  msg
	    << "Did not recognize format version " << version
	    << " of spatial database file '" << filename() << "'.\n";
	  throw std::runtime_error(msg.str());
	} // default
      } // switch
    if (!filein.good())
      throw std::runtime_error("Unknown error while reading.");
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while reading spatial database file '"
	<< filename() << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while reading spatial database file '"
	<< filename() << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch

} // read

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::_readV1(
				     SimpleDBData* pData,
				     spatialdata::geocoords::CoordSys** ppCS,
				     std::istream& filein)
{ // ReadV1
  assert(0 != pData);
  assert(0 != ppCS);

  utils::LineParser parser(filein, "//");
  parser.eatwhitespace(true);

  std::string token;
  std::istringstream buffer;
  const int maxIgnore = 256;

  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  if (0 != strcasecmp(token.c_str(), "SimpleDB")) {
    std::ostringstream msg;
    msg << "Could not parse '" << token << "' into 'SimpleDB'.\n";
    throw std::runtime_error(msg.str());
  } // else

  int numValues = 0;
  int numLocs = 0;
  int spaceDim = 3; // default
  int dataDim = 0;
  std::string* names = 0;
  std::string* units = 0;

  buffer.str(parser.next());
  buffer.clear();
  buffer >> token;
  while (buffer.good() && token != "}") {
    if (0 == strcasecmp(token.c_str(), "num-values")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> numValues;
    } else if (0 == strcasecmp(token.c_str(), "num-locs")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> numLocs;
    } else if (0 == strcasecmp(token.c_str(), "value-names")) {
      if (numValues > 0) {
	delete[] names; names = new std::string[numValues];
      } else
	throw std::runtime_error("Number of values must be specified BEFORE "
				 "names of values in SimpleDB file.");
      buffer.ignore(maxIgnore, '=');
      for (int iVal=0; iVal < numValues; ++iVal)
	buffer >> names[iVal];
    } else if (0 == strcasecmp(token.c_str(), "value-units")) {
      if (numValues > 0) {
	delete[] units; units = new std::string[numValues];
      } else
	throw std::runtime_error("Number of values must be specified BEFORE "
				 "units of values in SimpleDB file.");
      buffer.ignore(maxIgnore, '=');
      for (int iVal=0; iVal < numValues; ++iVal)
	buffer >> units[iVal];
    } else if (0 == strcasecmp(token.c_str(), "data-dim")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> dataDim;
    } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
      buffer.ignore(maxIgnore, '=');
      buffer >> spaceDim;
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
      spatialdata::geocoords::CSPicklerAscii::unpickle(filein, ppCS);
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a SimpleDB setting.";
      throw std::runtime_error(msg.str());
    } // else

    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
  } // while
  if (token != "}" || !filein.good())
    throw std::runtime_error("I/O error while parsing SimpleDB settings.");

  bool ok = true;
  std::ostringstream msg;
  if (0 == numValues) {
    ok = false;
    msg << "SimpleDB settings must include 'num-values'.\n";
  } // if
  if (0 == numLocs) {
    ok = false;
    msg << "SimpleDB settings must include 'num-locs'.\n";
  } // if
  if (0 == names) {
    ok = false;
      msg << "SimpleDB settings must include 'value-names'.\n";
  } // if
  if (0 == units) {
    ok = false;
    msg << "SimpleDB settings must include 'value-units'.\n";
  } // if
  if (!ok)
    throw std::runtime_error(msg.str());
  
  pData->allocate(numLocs, numValues, spaceDim, dataDim);
  char** cnames = (numValues > 0) ? new char*[numValues] : 0;
  char** cunits = (numValues > 0) ? new char*[numValues] : 0;
  for (int i=0; i < numValues; ++i) {
    cnames[i] = const_cast<char*>(names[i].c_str());
    cunits[i] = const_cast<char*>(units[i].c_str());
  } // for
  pData->names(const_cast<const char**>(cnames), numValues);
  pData->units(const_cast<const char**>(cunits), numValues);
  delete[] names; names = 0;
  delete[] units; units = 0;
  delete[] cnames; cnames = 0;
  delete[] cunits; cunits = 0;

  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    buffer.str(parser.next());
    buffer.clear();
    double* coordinates = pData->coordinates(iLoc);
    for (int iDim=0; iDim < spaceDim; ++iDim)
      buffer >> coordinates[iDim];
    double* data = pData->data(iLoc);
    for (int iVal=0; iVal < numValues; ++iVal)
      buffer >> data[iVal];
  } // for
  if (!filein.good())
    throw std::runtime_error("I/O error while reading SimpleDB data.");
  
  // Check compatibility of dimension of data, spatial dimension and
  // number of points
  checkCompatibility(*pData, *ppCS);
  
  // Convert to SI units
  convertToSI(pData);

  (*ppCS)->initialize();
} // _readV1

// ----------------------------------------------------------------------
// Write ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::write(
				const SimpleDBData& data,
				const spatialdata::geocoords::CoordSys* pCS)
{ // write
  try {
    std::ofstream fileout(filename());
    if (!fileout.is_open() || !fileout.good()) {
      std::ostringstream msg;
      msg << "Could not open spatial database file " << filename()
	  << "for writing.\n";
      throw std::runtime_error(msg.str());
    } // if
    
    const int version = 1;
    const int numLocs = data.numLocs();
    const int numValues = data.numValues();
    const int spaceDim = data.spaceDim();
    const int dataDim = data.dataDim();
    
    fileout
      << HEADER << " " << version << "\n"
      << "SimpleDB {\n"
      << "  num-values = " << std::setw(6) << numValues << "\n"
      << "  value-names =";
    for (int iVal=0; iVal < numValues; ++iVal)
      fileout << "  " << data.name(iVal);
    fileout << "\n";
    fileout << "  value-units =";
    for (int iVal=0; iVal < numValues; ++iVal)
      fileout << "  " << data.units(iVal);
    fileout << "\n";
    fileout
      << "  num-locs = " << std::setw(6) << numLocs << "\n"
      << "  data-dim = " << std::setw(4) << dataDim << "\n"
      << "  space-dim = " << std::setw(4) << spaceDim << "\n"
      << "  cs-data = ";
    spatialdata::geocoords::CSPicklerAscii::pickle(fileout, pCS);
    fileout << "}\n";
    if (!fileout.good())
      throw std::runtime_error("I/O error while writing SimpleDB settings.");

    fileout
      << std::resetiosflags(std::ios::fixed)
      << std::setiosflags(std::ios::scientific)
      << std::setprecision(6);
    for (int iLoc=0; iLoc < numLocs; ++iLoc) {
      const double* coordinates = data.coordinates(iLoc);
      for (int iCoord=0; iCoord < spaceDim; ++iCoord)
	fileout << std::setw(14) << coordinates[iCoord];
      const double* values = data.data(iLoc);
      for (int iVal=0; iVal < numValues; ++iVal)
	fileout << std::setw(14) << values[iVal];
      fileout << "\n";
    } // for
    if (!fileout.good())
      throw std::runtime_error("I/O error while writing SimpleDB data.");
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while writing spatial database file '"
	<< filename() << "'.\n" 
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while writing spatial database file '"
	<< filename() << "'.";
    throw std::runtime_error(msg.str());
  } // try/catch
} // write


// End of file 
