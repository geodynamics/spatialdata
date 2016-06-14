// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

extern "C" {
#include "cspatialdb.h"
}

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SpatialDB

#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Call SpatialDB:Query().
extern "C"
int
spatialdb_query(void* db, 
		double* vals,
		const int numVals,
		const double* coords,
		const int numDims,
		const void* cs)
{ // spatialdb_query
  spatialdata::spatialdb::SpatialDB* pDB = 
    (spatialdata::spatialdb::SpatialDB*) db;
  const spatialdata::geocoords::CoordSys* pCS = 
    (const spatialdata::geocoords::CoordSys*) cs;
  assert(0 != pDB);
  assert(0 != pCS);
  return pDB->query(vals, numVals, coords, numDims, pCS);
} // spatialdb_query


// End of file
