// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

#include "CoordSys.hh" // implementation of class methods

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CoordSys::CoordSys(void) :
  _csType(CARTESIAN)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Copy destructor
spatialdata::geocoords::CoordSys::CoordSys(const CoordSys& cs) :
  _csType(cs._csType)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CoordSys::~CoordSys(void)
{ // destructor
} // destructor

// version
// $Id$

// End of file 
