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

#include "SimpleIO.hh" // Implementation of class methods

#include <string> // USES std::string
#include "SimpleDBTypes.hh" // USES SimpleDBTypes

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::SimpleIO::SimpleIO(void)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SimpleIO::~SimpleIO(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleIO::checkCompatibility(
					    const SimpleDB::DataStruct& data)
{ // checkCompatibility
  const int numLocs = data.numLocs;
  switch (data.topology)
    { // switch
    case SimpleDB::POINT :
      if (numLocs > 1) {
	std::ostringstream msg;
	msg << "Point spatial distribution must have only 1 point. "
	    << "Found " << numLocs << " points in distribution.";
	throw std::runtime_error(msg.str());
      } // if
      break;
    case SimpleDB::LINE :
      if (numLocs < 2) {
	std::ostringstream msg;
	msg << "Linear spatial distribution must have at least 2 points. "
	    << "Found " << numLocs << " points in distribution.";
	throw std::runtime_error(msg.str());
      } // if
      break;
    case SimpleDB::AREA :
      if (numLocs < 3) {
	std::ostringstream msg;
	msg << "Areal spatial distribution must have at least 3 points. "
	    << "Found " << numLocs << " points in distribution.";
	throw std::runtime_error(msg.str());
      } // if
      break;
    case SimpleDB::VOLUME :
      if (numLocs < 4) {
	std::ostringstream msg;
	msg << "Volumetric spatial distribution must have at least 4 points. "
	    << "Found " << numLocs << " points in distribution.";
	throw std::runtime_error(msg.str());
      } // if
      break;
    default :
      throw std::runtime_error("Could not check compatiblity for unrecognized "
			       "topology type.");
    } // switch
} // checkCompatibility

// version
// $Id$

// End of file 
