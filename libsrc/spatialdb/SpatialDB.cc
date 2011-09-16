// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "SpatialDB.hh" // Implementation of class methods

#include <cassert> // USES assert()

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

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SpatialDB::query(float* vals,
					 const int numVals,
					 const float* coords,
					 const int numDims,
					 const spatialdata::geocoords::CoordSys* csQuery)
{ // query
  double* coordsD = (numDims > 0) ? new double[numDims] : 0;
  for (int i=0; i < numDims; ++i)
    coordsD[i] = coords[i];

  double* valsD = (numVals > 0) ? new double[numVals] : 0;

  const int err = query(valsD, numVals, coordsD, numDims, csQuery);

  for (int i=0; i < numVals; ++i)
    vals[i] = valsD[i];

  delete[] valsD; valsD = 0;
  delete[] coordsD; coordsD = 0;

  return err;
} // query

// ----------------------------------------------------------------------
// Perform multiple queries of the database.
void
spatialdata::spatialdb::SpatialDB::multiquery(double* vals,
					      const int numLocsV,
					      const int numValsV,
					      int* err,
					      const int numLocsE,
					      const double* coords,
					      const int numLocsC,
					      const int numDimsC,
					      const spatialdata::geocoords::CoordSys* csQuery)
{ // multiquery
  assert(numLocsV == numLocsE);
  assert(numLocsC == numLocsE);
  assert( (0 == vals && 0 == numLocsV && 0 == numValsV) ||
	  (0 != vals && numLocsV > 0 && numValsV > 0) );
  assert( (0 == err && 0 == numLocsE) ||
	  (0 != err && numLocsE > 0) );
  assert( (0 == coords && 0 == numLocsC && 0 == numDimsC) ||
	  (0 != coords && numLocsC > 0 && numDimsC > 0) );

  for (int i=0, indexV=0, indexC=0;
       i < numLocsV;
       ++i, indexV+=numValsV, indexC+=numDimsC)
    err[i] = query(&vals[indexV], numValsV, &coords[indexC], numDimsC,
		   csQuery);
} // multiquery


// ----------------------------------------------------------------------
// Perform multiple queries of the database.
void
spatialdata::spatialdb::SpatialDB::multiquery(float* vals,
					      const int numLocsV,
					      const int numValsV,
					      int* err,
					      const int numLocsE,
					      const float* coords,
					      const int numLocsC,
					      const int numDimsC,
					      const spatialdata::geocoords::CoordSys* csQuery)
{ // multiquery
  assert(numLocsV == numLocsE);
  assert(numLocsC == numLocsE);
  assert( (0 == vals && 0 == numLocsV && 0 == numValsV) ||
	  (0 != vals && numLocsV > 0 && numValsV > 0) );
  assert( (0 == err && 0 == numLocsE) ||
	  (0 != err && numLocsE > 0) );
  assert( (0 == coords && 0 == numLocsC && 0 == numDimsC) ||
	  (0 != coords && numLocsC > 0 && numDimsC > 0) );

  for (int i=0, indexV=0, indexC=0;
       i < numLocsV;
       ++i, indexV+=numValsV, indexC+=numDimsC)
    err[i] = query(&vals[indexV], numValsV, &coords[indexC], numDimsC,
		   csQuery);
} // multiquery


// End of file 
