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

#include "SpatialDB.hh" // USES SimpleDB
#include "SimpleDB.hh" // USES SimpleDB

#include "SimpleIO.hh" // ISA SimpleIO
#include "SimpleIOAscii.hh" // implementation of class methods

#include "SimpleDBTypes.hh" // USES SimpleDBTypes
#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPicklerAscii

#include <fstream> // USES std::ofstream, std::ifstream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
const char* spatialdata::spatialdb::SimpleIOAscii::HEADER =  "#SPATIAL.ascii";

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::read(
				   SimpleDB::DataStruct* pData,
				   spatialdata::geocoords::CoordSys** ppCS)
{ // Read
  assert(0 != pData);

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
spatialdata::spatialdb::SimpleIOAscii::_readV1(
				     SimpleDB::DataStruct* pData,
				     spatialdata::geocoords::CoordSys** ppCS,
				     std::istream& filein)
{ // ReadV1
  assert(0 != pData);
  assert(0 != ppCS);

  // Clear memory and set default values
  delete[] pData->valNames; pData->valNames = 0;
  delete[] pData->valUnits; pData->valUnits = 0;
  delete[] pData->data; pData->data = 0;
  delete *ppCS; *ppCS = new spatialdata::geocoords::CSCart();
  pData->dataDim = 0;
  pData->spaceDim = 3;

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
      } else if (0 == strcasecmp(token.c_str(), "data-dim")) {
	filein.ignore(maxIgnore, '=');
	filein >> pData->dataDim;
      } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
	filein.ignore(maxIgnore, '=');
	filein >> pData->spaceDim;
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

  const int dataSize = pData->numLocs * (pData->spaceDim + pData->numVals);
  delete[] pData->data; 
  pData->data = (dataSize > 0) ? new double[dataSize] : 0;
  for (int i=0; i < dataSize; ++i)
    filein >> pData->data[i];
  
  // Check compatibility of dimension of data, spatial dimension and
  // number of points
  checkCompatibility(*pData, *ppCS);
  
  (*ppCS)->initialize();
} // ReadV1

// ----------------------------------------------------------------------
// Write ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::write(
				const SimpleDB::DataStruct& data,
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
    << "  data-dim = " << std::setw(4) << data.dataDim << "\n"
    << "  space-dim = " << std::setw(4) << data.spaceDim << "\n"
    << "  cs-data = ";
  spatialdata::geocoords::CSPicklerAscii::pickle(fileout, pCS);
  fileout << "}\n";

  fileout
    << std::resetiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::scientific)
    << std::setprecision(6);
  const int numCoords = data.spaceDim;
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


// End of file 
