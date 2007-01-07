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

#include "SimpleDBData.hh"

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SimpleDBData::SimpleDBData(void) :
  numLocs(0),
  spaceDim(0),
  numVals(0),
  dataDim(0),
  dbData(0),
  errFlags(0),
  names(0),
  units(0),
  numQueries(0),
  queryNearest(0),
  queryLinear(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SimpleDBData::~SimpleDBData(void)
{ // destructor
} // destructor


// End of file
