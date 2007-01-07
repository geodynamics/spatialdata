/*  -*- C -*-  */
/*
 * ======================================================================
 *
 *                           Brad T. Aagaard
 *                        U.S. Geological Survey
 *
 * {LicenseText}
 *
 * ======================================================================
 */

#include "testcquery.h"
#include "spatialdata/spatialdb/cspatialdb.h"

/* ------------------------------------------------------------------- */
int
testcquery(void* db,
	   double* vals,
	   int numVals,
	   const double* coords,
	   const int numDims,
	   void* cs)
{ // testcquery
  return spatialdb_query(db, vals, numVals, coords, numDims, cs);
} // testcquery

/* End of file  */
