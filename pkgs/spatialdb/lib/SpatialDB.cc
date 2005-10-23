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
spatialdata::spatialdb::SpatialDB::SpatialDB(void) :
  _label("")
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::SpatialDB::SpatialDB(const char* label) :
  _label(label)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SpatialDB::~SpatialDB(void)
{ // destructor
} // destructor

// version
// $Id: SpatialDB.cc,v 1.1 2005/05/25 18:42:57 baagaard Exp $

// End of file 
