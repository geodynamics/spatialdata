// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//
#include <portinfo>

#include "SimpleIO.hh" // Implementation of class methods

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "SpatialDB.hh" // USES SimpleDB
#include "SimpleDB.hh" // USES SimpleDB
#include "SimpleDBData.hh" // USES SimpleDBData

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/units/Parser.hh" // USES Parser

#include <sstream> // USES std::ostringstream
#include <string> // USES std::string
#include <vector> // USES std::vector
#include <stdexcept> // USES std::runtime_error, std::exception
#include <assert.h> // USES assert()

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
			      const SimpleDBData& data,
			      const spatialdata::geocoords::CoordSys* pCS)
{ // checkCompatibility
  assert(0 != pCS);

  const int numLocs = data.numLocs();
  const int spaceDim = data.spaceDim();
  const int dataDim = data.dataDim();
  std::ostringstream msg;
  if (numLocs < 1 + dataDim) {
    msg << "Spatial distribution with data dimensions of " << dataDim 
	<< " must have at least " << 1+dataDim << " points.\n"
	<< "Found " << numLocs << " points in distribution.";
    throw std::runtime_error(msg.str());
  } // if
  if (0 == dataDim && numLocs > 1) {
    msg << "Spatial distribution with data dimensions of " << dataDim 
	<< " cannot have more than one point.\n"
	<< "Found " << numLocs << " points in distribution.";
    throw std::runtime_error(msg.str());
  } // if
  if (dataDim > spaceDim) {
    msg << "Dimension of data in spatial distribution (" << dataDim
	<< ") exceeds the number of dimensions of the coordinates ("
	<< spaceDim << ").";
    throw std::runtime_error(msg.str());
  } // if
  if (spaceDim != pCS->spaceDim()) {
    msg << "Number of dimensions in coordinates of spatial distribution ("
	<< spaceDim << ") does not match number of dimensions in coordinate "
	<< "system (" << pCS->spaceDim() << ")";
    throw std::runtime_error(msg.str());
  } // if
} // checkCompatibility

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleIO::convertToSI(SimpleDBData* const data)
{ // convertToSI
  assert(0 != data);

  spatialdata::units::Parser parser;

  const int numValues = data->numValues();
  std::vector<double> scales(numValues);
  for (int iVal=0; iVal < numValues; ++iVal) {
    if (strcasecmp(data->units(iVal), "none") != 0)
      scales[iVal] = parser.parse(data->units(iVal));
    else
      scales[iVal] = 1.0;
  } // for

  const int numLocs = data->numLocs();
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    double* values = data->data(iLoc);
    for (int iVal=0; iVal < numValues; ++iVal)
      values[iVal] *= scales[iVal];
  } // for
} // convertToSI


// End of file 
