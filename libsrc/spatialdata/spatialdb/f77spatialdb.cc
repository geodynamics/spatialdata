// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

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
