// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
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
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Copy destructor
spatialdata::geocoords::CoordSys::CoordSys(const CoordSys& cs) :
  _spaceDim(cs._spaceDim),
  _csType(cs._csType)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CoordSys::~CoordSys(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Set number of spatial dimensions in coordinate system.
void
spatialdata::geocoords::CoordSys::setSpaceDim(const int ndims)
{ // setSpaceDim
  if (ndims < 1) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions (" << ndims
      << ") must be >= 1.";
    throw std::runtime_error(msg.str());
  } // if
  _spaceDim = ndims;
} // setSpaceDim


// End of file 
