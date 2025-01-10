// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
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
spatialdata::spatialdb::SimpleIO::SimpleIO(void) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SimpleIO::~SimpleIO(void) {}


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleIO::checkCompatibility(
    const SimpleDBData& data,
    const spatialdata::geocoords::CoordSys* cs) {
    assert(cs);

    const size_t numLocs = data.getNumLocs();
    const size_t spaceDim = data.getSpaceDim();
    const size_t dataDim = data.getDataDim();
    std::ostringstream msg;
    if (numLocs < 1 + dataDim) {
        msg << "Spatial distribution with data dimensions of " << dataDim
            << " must have at least " << 1+dataDim << " points.\n"
            << "Found " << numLocs << " points in distribution.";
        throw std::domain_error(msg.str());
    } // if
    if (( 0 == dataDim) && ( numLocs > 1) ) {
        msg << "Spatial distribution with data dimensions of " << dataDim
            << " cannot have more than one point.\n"
            << "Found " << numLocs << " points in distribution.";
        throw std::domain_error(msg.str());
    } // if
    if (dataDim > spaceDim) {
        msg << "Dimension of data in spatial distribution (" << dataDim
            << ") exceeds the number of dimensions of the coordinates ("
            << spaceDim << ").";
        throw std::domain_error(msg.str());
    } // if
    if (spaceDim != cs->getSpaceDim()) {
        msg << "Number of dimensions in coordinates of spatial distribution ("
            << spaceDim << ") does not match number of dimensions in coordinate "
            << "system (" << cs->getSpaceDim() << ")";
        throw std::domain_error(msg.str());
    } // if
} // checkCompatibility


// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleIO::convertToSI(SimpleDBData* const data) {
    assert(data);

    spatialdata::units::Parser parser;

    const size_t numValues = data->getNumValues();
    std::vector<double> scales(numValues);
    for (size_t iVal = 0; iVal < numValues; ++iVal) {
        if (strcasecmp(data->getUnits(iVal), "none") != 0) {
            scales[iVal] = parser.parse(data->getUnits(iVal));
        } else {
            scales[iVal] = 1.0;
        }
    } // for

    const size_t numLocs = data->getNumLocs();
    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        double* values = data->getData(iLoc);
        for (size_t iVal = 0; iVal < numValues; ++iVal) {
            values[iVal] *= scales[iVal];
        }
    } // for
} // convertToSI


// End of file
