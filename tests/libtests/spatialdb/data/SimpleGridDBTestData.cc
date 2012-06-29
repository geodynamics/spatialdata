// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include "SimpleGridDBTestData.hh"

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SimpleGridDBTestData::SimpleGridDBTestData(void) :
  numX(0),
  numY(0),
  numZ(0),
  spaceDim(0),
  numVals(0),
  dataDim(0),
  dbX(0),
  dbY(0),
  dbZ(0),
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
spatialdata::spatialdb::SimpleGridDBTestData::~SimpleGridDBTestData(void)
{ // destructor
} // destructor


// End of file
