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

#include <fstream> // USES std::ofstream, std::ifstream
#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()

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

  try {
    std::ifstream filein(filename());
    if (!filein.is_open() || !filein.good()) {
    std::ostringstream msg;
    msg << "Could not open spatial database file for reading.";
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
	<< HEADER << "'.";
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
	    << " of spatial database file.";
	  throw std::runtime_error(msg.str());
	} // default
      } // switch

  } // try
  catch (std::exception& err) {
    std::ostringstream msg;
    msg
      << "Error occurred while reading spatial database file '"
      << filename() << "'.\n"
      << err.what();
    throw std::runtime_error(msg.str());
  } // catch
  catch (...) { // catch
    std::ostringstream msg;
    msg
      << "Unknown error occurred while reading spatial database file '"
      << filename() << "'.\n";
      throw std::runtime_error(msg.str());
  } // catch

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

  // Set coordinate system to Cartesian by default
  *ppCS = new spatialdata::geocoords::CSCart();

  const int maxLineLen = 256;
  filein.ignore(maxLineLen, ':');
  filein >> pData->numVals;
  delete[] pData->valNames; 
  const int numVals = pData->numVals;
  pData->valNames = (numVals > 0) ? new std::string[numVals] : 0;
  filein.ignore(maxLineLen, ':');
  for (int iVal=0; iVal < numVals; ++iVal)
    filein >> pData->valNames[iVal];
  filein.ignore(maxLineLen, ':');
  filein >> pData->numLocs;

  std::string topoString;
  filein.ignore(maxLineLen, ':');
  filein >> topoString;
  pData->topology = parseTopoString(topoString.c_str());
  
  const int numCoords = 3;
  const int dataSize = pData->numLocs * (numCoords + numVals);
  delete[] pData->data; 
  pData->data = (dataSize > 0) ? new double[dataSize] : 0;
  for (int i=0; i < dataSize; ++i)
    filein >> pData->data[i];
  
  // Check compatibility of topology and number of points
  checkCompatibility(*pData);

} // ReadV1

// ----------------------------------------------------------------------
// Write ascii database file.
void
spatialdata::spatialdb::SimpleIOAscii::write(const SimpleDB::DataStruct& data,
				    const spatialdata::geocoords::CoordSys& cs)
{ // write
  std::ofstream fileout(filename());
  if (!fileout.is_open() || !fileout.good()) {
    std::ostringstream msg;
    msg << "Could not open spatial database file " << filename()
	<< "\nfor writing.";
    throw std::runtime_error(msg.str());
  } // if

  const int version = 1;
  const int numLocs = data.numLocs;
  const int numVals = data.numVals;

  fileout
    << HEADER << " " << version << "\n"
    << "Number of values: " << std::setw(6) << numVals << "\n";
  fileout << "Names of values: ";
  for (int iVal=0; iVal < numVals; ++iVal)
    fileout << "  " << data.valNames[iVal];
  fileout
    << "\n"
    << "Number of locations: " << std::setw(6) << numLocs << "\n"
    << "Topology: " << topoString(data.topology) << "\n";

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
