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

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

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
			      const SimpleDB::DataStruct& data,
			      const spatialdata::geocoords::CoordSys* pCS)
{ // checkCompatibility
  assert(0 != pCS);

  const int numLocs = data.numLocs;
  const int spaceDim = data.spaceDim;
  const int dataDim = data.dataDim;
  if (numLocs < 1 + dataDim) {
    std::ostringstream msg;
    msg << "Spatial distribution with data dimensions of " << dataDim 
	<< " must have at least " << 1+dataDim << " points. "
	<< "Found " << numLocs << " points in distribution.";
    throw std::runtime_error(msg.str());
  } // if
  if (dataDim > spaceDim) {
    std::ostringstream msg;
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") exceeds the number of dimensions of the coordinates ("
	<< spaceDim << ").";
    throw std::runtime_error(msg.str());
  } // if
  if (spaceDim != pCS->spaceDim()) {
    std::ostringstream msg;
    msg << "Number of dimensions in coordinates of spatial distribution ("
	<< spaceDim << ") does not match number of dimensions in coordinate "
	<< "system (" << pCS->spaceDim() << ")";
    throw std::runtime_error(msg.str());
  } // if
} // checkCompatibility


// End of file 
