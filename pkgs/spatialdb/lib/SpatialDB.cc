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

#include "SpatialDB.h" // Implementation of class methods

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::SpatialDB::SpatialDB(void) :
  mLabel("")
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::SpatialDB::SpatialDB(const char* label) :
  mLabel(label)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::SpatialDB::~SpatialDB(void)
{ // destructor
} // destructor

// version
// $Id: SpatialDB.cc,v 1.1 2005/05/25 18:42:57 baagaard Exp $

// End of file 