// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "CoordSys.hh" // implementation of class methods

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CoordSys::CoordSys(void) :
    _spaceDim(3),
    _csType(CARTESIAN)
{}


// ----------------------------------------------------------------------
// Copy destructor
spatialdata::geocoords::CoordSys::CoordSys(const CoordSys& cs) :
    _spaceDim(cs._spaceDim),
    _csType(cs._csType)
{}


// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CoordSys::~CoordSys(void)
{}


// ----------------------------------------------------------------------
// Set number of spatial dimensions in coordinate system.
void
spatialdata::geocoords::CoordSys::setSpaceDim(const int ndims) {
    if (ndims < 1) {
        std::ostringstream msg;
        msg
            << "Number of spatial dimensions (" << ndims
            << ") must be >= 1.";
        throw std::runtime_error(msg.str());
    } // if
    _spaceDim = ndims;
} // setSpaceDim


// ----------------------------------------------------------------------
// Get number of spatial dimensions in coordinate system.
int
spatialdata::geocoords::CoordSys::spaceDim(void) const {
    return _spaceDim;
} // spaceDim


// ----------------------------------------------------------------------
// Get type of coordinate system
spatialdata::geocoords::CoordSys::CSTypeEnum
spatialdata::geocoords::CoordSys::csType(void) const {
    return _csType;
} // csType


// ----------------------------------------------------------------------
// Set type of coordinate system.
void
spatialdata::geocoords::CoordSys::csType(const CSTypeEnum cs) {
    _csType = cs;
} // csType


// End of file
