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

#include "SpatialDB.h" // USES SimpleDB
#include "SimpleDB.h" // USES SimpleDB

#include "SimpleIO.h" // ISA SimpleIO
#include "SimpleIOAscii.h" // implementation of class methods

#include "SimpleDBTypes.h" // USES SimpleDBTypes
#include "spatialdata/geocoords/CoordSys.h" // USES CSCart
#include "spatialdata/geocoords/CSCart.h" // USES CSCart
#include "spatialdata/geocoords/CSPicklerAscii.h" // USES CSPicklerAscii

#include <fstream> // USES std::ofstream, std::ifstream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
const char* spatialdata::spatialdb::SimpleIOAscii::HEADER =  "#SPATIAL.ascii";
//const char* spatialdata::spatialdb::SimpleIOAscii::ASCIIHEADER =  "#EQSIM.spatial.ascii";

const char* spatialdata::spatialdb::SimpleIOAscii::POINTSTRING = "point";
const char* spatialdata::spatialdb::SimpleIOAscii::LINESTRING = "line";
const char* spatialdata::spatialdb::SimpleIOAscii::AREASTRING = "area";
const char* spatialdata::spatialdb::SimpleIOAscii::VOLSTRING = "volume";

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::read(SimpleDB::DataStruct* pData,
					    spatialdata::geocoords::CoordSys** ppCS)
{ // Read
  FIREWALL(0 != pData);

  std::ifstream filein(filename());
  if (!filein.is_open() || !filein.good()) {
    std::ostringstream msg;
    msg << "Could not open spatial database file '" << filename()
	<< "' for reading.\n";
    throw std::runtime_error(msg.str());
  } // if

  const int headerLen = strlen(HEADER);
  std::string buffer;
  buffer.resize(headerLen+1);
  filein.read((char*) buffer.c_str(), sizeof(char)*headerLen);
  buffer[headerLen] = '\0';
  if (0 != strcasecmp(HEADER, buffer.c_str())) {
    std::ostringstream msg;
    msg
      << "Magic header '" << buffer << "' does not match expected header '"
      << HEADER << "' in spatial database file '" << filename() << "'.\n";
    throw std::runtime_error(msg.str());
  } // if
  int version = 0;
  filein >> version;
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
} // Read

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::_readV1(SimpleDB::DataStruct* pData,
					 spatialdata::geocoords::CoordSys** ppCS,
					       std::istream& filein)
{ // ReadV1
  FIREWALL(0 != pData);
  FIREWALL(0 != ppCS);

  // Clear memory and set default values
  delete[] pData->valNames; pData->valNames = 0;
  delete[] pData->valUnits; pData->valUnits = 0;
  delete[] pData->data; pData->data = 0;
  delete *ppCS; *ppCS = new spatialdata::geocoords::CSCart();

  std::string name;

  filein >> name;
  if (0 == strcasecmp(name.c_str(), "SimpleDB")) {
    int numVals = 0;
    std::string token;
    const int maxIgnore = 256;
    filein.ignore(maxIgnore, '{');
    filein >> token;
    while (filein.good() && token != "}") {
      if (0 == strcasecmp(token.c_str(), "num-values")) {
	filein.ignore(maxIgnore, '=');
	filein >> numVals;
	pData->numVals = numVals;
      } else if (0 == strcasecmp(token.c_str(), "num-locs")) {
	filein.ignore(maxIgnore, '=');
	filein >> pData->numLocs;
      } else if (0 == strcasecmp(token.c_str(), "value-names")) {
	if (numVals > 0)
	  pData->valNames = new std::string[numVals];
	else
	  throw std::runtime_error("Number of values must be specified BEFORE "
				   "names of values in SimpleDB file.");
	filein.ignore(maxIgnore, '=');
	for (int iVal=0; iVal < numVals; ++iVal)
	  filein >> pData->valNames[iVal];
      } else if (0 == strcasecmp(token.c_str(), "value-units")) {
	if (numVals > 0)
	  pData->valUnits = new std::string[numVals];
	else
	  throw std::runtime_error("Number of values must be specified BEFORE "
				   "units of values in SimpleDB file.");
	filein.ignore(maxIgnore, '=');
	for (int iVal=0; iVal < numVals; ++iVal)
	  filein >> pData->valUnits[iVal];
      } else if (0 == strcasecmp(token.c_str(), "topology")) {
	filein.ignore(maxIgnore, '=');
	std::string topoString;
	filein >> topoString;
	pData->topology = parseTopoString(topoString.c_str());
      } else if (0 == strcasecmp(token.c_str(), "cs-data")) {
	spatialdata::geocoords::CSPicklerAscii::unpickle(filein, ppCS);
      } else {
	std::ostringstream msg;
	msg << "Could not parse '" << token << "' into a SimpleDB setting.";
	throw std::runtime_error(msg.str());
      } // else
      filein >> token;
    } // while
    if (!filein.good())
      throw std::runtime_error("I/O error while parsing SimpleDB settings.");

    bool ok = true;
    std::ostringstream msg;
    if (0 == pData->numVals) {
      ok = false;
      msg << "SimpleDB settings must include 'num-values'.\n";
    } // if
    if (0 == pData->numLocs) {
      ok = false;
      msg << "SimpleDB settings must include 'num-locs'.\n";
    } // if
    if (0 == pData->valNames) {
      ok = false;
      msg << "SimpleDB settings must include 'value-names'.\n";
    } // if
    if (0 == pData->valUnits) {
      ok = false;
      msg << "SimpleDB settings must include 'value-units'.\n";
    } // if
    if (!ok)
      throw std::runtime_error(msg.str());
  } else {
    std::ostringstream msg;
    msg << "Could not parse '" << name << "' into 'SimpleDB'.\n";
    throw std::runtime_error(msg.str());
  } // else

  const int numCoords = 3;
  const int dataSize = pData->numLocs * (numCoords + pData->numVals);
  delete[] pData->data; 
  pData->data = (dataSize > 0) ? new double[dataSize] : 0;
  for (int i=0; i < dataSize; ++i)
    filein >> pData->data[i];
  
  // Check compatibility of topology and number of points
  checkCompatibility(*pData);
  
  (*ppCS)->initialize();
} // ReadV1

// ----------------------------------------------------------------------
// Write ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::write(const SimpleDB::DataStruct& data,
					     const spatialdata::geocoords::CoordSys* pCS)
{ // write
  std::ofstream fileout(filename());
  if (!fileout.is_open() || !fileout.good()) {
    std::ostringstream msg;
    msg << "Could not open spatial database file " << filename()
	<< "for writing.\n";
    throw std::runtime_error(msg.str());
  } // if

  const int version = 1;
  const int numLocs = data.numLocs;
  const int numVals = data.numVals;

  fileout
    << HEADER << " " << version << "\n"
    << "SimpleDB {\n"
    << "  num-values = " << std::setw(6) << numVals << "\n"
    << "  value-names =";
  for (int iVal=0; iVal < numVals; ++iVal)
    fileout << "  " << data.valNames[iVal];
  fileout << "\n";
  fileout << "  value-units =";
  for (int iVal=0; iVal < numVals; ++iVal)
    fileout << "  " << data.valUnits[iVal];
  fileout << "\n";
  fileout
    << "  num-locs = " << std::setw(6) << numLocs << "\n"
    << "  topology = " << topoString(data.topology) << "\n"
    << "  cs-data = ";
  spatialdata::geocoords::CSPicklerAscii::pickle(fileout, pCS);
  fileout << "}\n";

  fileout
    << std::resetiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::scientific)
    << std::setprecision(6);
  const int numCoords = 3;
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    const double* pCoords = SimpleDBTypes::dataCoords(data, iLoc);
    for (int iCoord=0; iCoord < numCoords; ++iCoord)
      fileout << std::setw(14) << pCoords[iCoord];
    const double* pVals = SimpleDBTypes::dataVals(data, iLoc);
    for (int iVal=0; iVal < numVals; ++iVal)
      fileout << std::setw(14) << pVals[iVal];
    fileout << "\n";
  } // for
} // write

// ----------------------------------------------------------------------
// Parse string into topology type.
spatialdata::spatialdb::SimpleDB::TopoEnum
spatialdata::spatialdb::SimpleIOAscii::parseTopoString(const char* str)
{ // parseTopoString
  SimpleDB::TopoEnum topoType = SimpleDB::POINT;
  if (strcasecmp(str, POINTSTRING) == 0)
    topoType = SimpleDB::POINT;
  else if (strcasecmp(str, LINESTRING) == 0)
    topoType = SimpleDB::LINE;
  else if (strcasecmp(str, AREASTRING) == 0)
    topoType = SimpleDB::AREA;
  else if (strcasecmp(str, VOLSTRING) == 0)
    topoType = SimpleDB::VOLUME;
  else {
    std::ostringstream msg;
    msg << "Could not parse topology string '" << str << "' into a known "
	<< "topology.";
    throw std::runtime_error(msg.str());
  } // else
  return topoType;
} // parseTopoString

// ----------------------------------------------------------------------
// Get string associated with topology type.
const char*
spatialdata::spatialdb::SimpleIOAscii::topoString(SimpleDB::TopoEnum topoType)
{ // topoString
  const char* str = POINTSTRING;
  switch (topoType)
    { // switch
    case SimpleDB::POINT :
      str = POINTSTRING;
      break;
    case SimpleDB::LINE :
      str = LINESTRING;
      break;
    case SimpleDB::AREA :
      str = AREASTRING;
      break;
    case SimpleDB::VOLUME :
      str = VOLSTRING;
      break;
    default :
      throw std::runtime_error("Could not find string associated with "
			       "topology type.");
    } // switch
  return str;
} // topoString

// version
// $Id: SimpleIOAscii.cc,v 1.1 2005/05/25 18:42:57 baagaard Exp $

// End of file 
