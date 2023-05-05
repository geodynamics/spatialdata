// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>
#include "f77spatialdb.h"

extern "C" {
#include "cspatialdb.h"
}

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SpatialDB

#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Call SpatialDB:Query().
extern "C"
void
spatialdb_query_f(void* db,
                  double* vals,
                  const int* numVals,
                  const double* coords,
                  const int* numDims,
                  const void* cs,
                  int* ok) { // spatialdb_query_f
    spatialdata::spatialdb::SpatialDB* pDB =
        (spatialdata::spatialdb::SpatialDB*) db;
    const spatialdata::geocoords::CoordSys* pCS =
        (const spatialdata::geocoords::CoordSys*) cs;
    assert(0 != pDB);
    assert(0 != pCS);
    assert(0 != numVals);
    assert(0 != coords);
    assert(0 != numDims);
    assert(0 != ok);
    *ok = pDB->query(vals, *numVals, coords, *numDims, pCS);
} // spatialdb_query_f


// version
// $Id$

// End of file
