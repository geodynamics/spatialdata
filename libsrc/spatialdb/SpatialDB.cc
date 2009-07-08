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


// End of file 
