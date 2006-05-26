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
		double** pVals,
		const int numVals,
		const double x,
		const double y,
		const double z,
		const void* cs)
{ // spatialdb_query
  spatialdata::spatialdb::SpatialDB* pDB = 
    (spatialdata::spatialdb::SpatialDB*) db;
  const spatialdata::geocoords::CoordSys* pCS = 
    (const spatialdata::geocoords::CoordSys*) cs;
  assert(0 != pDB);
  assert(0 != pCS);
  return pDB->query(pVals, numVals, x, y, z, pCS);
} // spatialdb_query

// version
// $Id$

// End of file
