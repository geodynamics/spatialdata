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
#include "f77spatialdb.h"

extern "C" {
#include "cspatialdb.h"
}

#include "spatialdata/spatialdb/SpatialDB.hh" // USES SpatialDB

#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Call SpatialDB:Query().
extern "C"
void spatialdb_query_f(void* db, 
		       double* pVals,
		       const int* numVals,
		       const double* x,
		       const double* y,
		       const double* z,
		       const void* cs,
		       int* ok)
{ // spatialdb_query_f
  spatialdata::spatialdb::SpatialDB* pDB = 
    (spatialdata::spatialdb::SpatialDB*) db;
  const spatialdata::geocoords::CoordSys* pCS = 
    (const spatialdata::geocoords::CoordSys*) cs;
  assert(0 != pDB);
  assert(0 != pCS);
  assert(0 != x);
  assert(0 != y);
  assert(0 != z);
  assert(0 != ok);
  *ok = pDB->query(&pVals, *numVals, *x, *y, *z, pCS);
} // spatialdb_query_f

// version
// $Id$

// End of file
