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

#include <fstream> // USES std::ofstream, std::ifstream
#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()

#include "SimpleDBTypes.h" // USES SimpleDBTypes

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL

// ----------------------------------------------------------------------
const char* spatial::SimpleIOAscii::HEADER =  "#SPATIAL.ascii";
//const char* spatial::SimpleIOAscii::ASCIIHEADER =  "#EQSIM.spatial.ascii";

const char* spatial::SimpleIOAscii::POINTSTRING = "point";
const char* spatial::SimpleIOAscii::LINESTRING = "line";
const char* spatial::SimpleIOAscii::AREASTRING = "area";
const char* spatial::SimpleIOAscii::VOLSTRING = "volume";

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatial::SimpleIOAscii::Read(SimpleDB::DataStruct* pData)
{ // Read
  FIREWALL(0 != pData);

  try {
    std::ifstream filein(Filename());
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
	ReadV1(pData, filein);
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
      << Filename() << "'.\n"
      << err.what();
    throw std::runtime_error(msg.str());
  } // catch
  catch (...) { // catch
    std::ostringstream msg;
    msg
      << "Unknown error occurred while reading spatial database file '"
      << Filename() << "'.\n";
      throw std::runtime_error(msg.str());
  } // catch

} // Read

// ----------------------------------------------------------------------
// Read ascii database file.
void
spatial::SimpleIOAscii::ReadV1(SimpleDB::DataStruct* pData,
			       std::istream& filein)
{ // ReadV1
  FIREWALL(0 != pData);

  filein >> pData->NumVals;
  delete[] pData->ValNames; 
  const int numVals = pData->NumVals;
  pData->ValNames = (numVals > 0) ? new std::string[numVals] : 0;
  for (int iVal=0; iVal < numVals; ++iVal)
    filein >> pData->ValNames[iVal];
  filein >> pData->NumLocs;

  std::string topoString;
  filein >> topoString;
  pData->Topology = ParseTopoString(topoString.c_str());
  
  const int numCoords = 3;
  const int dataSize = pData->NumLocs * (numCoords + numVals);
  delete[] pData->Data; 
  pData->Data = (dataSize > 0) ? new double[dataSize] : 0;
  for (int i=0; i < dataSize; ++i)
    filein >> pData->Data[i];
  
  // Check compatibility of topology and number of points
  CheckCompatibility(*pData);
} // ReadV1

// ----------------------------------------------------------------------
// Write ascii database file.
void
spatial::SimpleIOAscii::Write(const SimpleDB::DataStruct& data)
{ // Write
  std::ofstream fileout(Filename());
  if (!fileout.is_open() || !fileout.good()) {
    std::ostringstream msg;
    msg << "Could not open spatial database file " << Filename()
	<< "\nfor writing.";
    throw std::runtime_error(msg.str());
  } // if

  const int version = 1;
  const int numLocs = data.NumLocs;
  const int numVals = data.NumVals;

  fileout
    << HEADER << " " << version << "\n"
    << std::setw(6) << numVals << "\n";
  for (int iVal=0; iVal < numVals; ++iVal)
    fileout << "  " << data.ValNames[iVal];
  fileout
    << "\n"
    << std::setw(6) << numLocs << "\n"
    << TopoString(data.Topology) << "\n";

  fileout
    << std::resetiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::scientific)
    << std::setprecision(6);
  const int numCoords = 3;
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    const double* pCoords = SimpleDBTypes::DataCoords(data, iLoc);
    for (int iCoord=0; iCoord < numCoords; ++iCoord)
      fileout << std::setw(14) << pCoords[iCoord];
    const double* pVals = SimpleDBTypes::DataVals(data, iLoc);
    for (int iVal=0; iVal < numVals; ++iVal)
      fileout << std::setw(14) << pVals[iVal];
    fileout << "\n";
  } // for
} // Write

// ----------------------------------------------------------------------
// Parse string into topology type.
spatial::SimpleDB::TopoEnum
spatial::SimpleIOAscii::ParseTopoString(const char* str)
{ // ParseTopoString
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
} // ParseTopoString

// ----------------------------------------------------------------------
// Get string associated with topology type.
const char*
spatial::SimpleIOAscii::TopoString(SimpleDB::TopoEnum topoType)
{ // ParseTopoString
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
} // ParseTopoString

// version
// $Id: SimpleIOAscii.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
