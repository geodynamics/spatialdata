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

#include "SimpleDBQueryData.hh"

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SimpleDBQueryData::SimpleDBQueryData(void) :
  numLocs(0),
  spaceDim(0),
  numVals(0),
  dataDim(0),
  dbData(0),
  names(0),
  units(0),
  numPts(0),
  coords(0),
  dist2(0),
  area(0),
  areaDir(0),
  volume(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SimpleDBQueryData::~SimpleDBQueryData(void)
{ // destructor
} // destructor


// End of file
