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
spatial::SpatialDB::SpatialDB(void) :
  mLabel("")
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatial::SpatialDB::SpatialDB(const char* label) :
  mLabel(label)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatial::SpatialDB::~SpatialDB(void)
{ // destructor
} // destructor

// version
// $Id: SpatialDB.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
