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
	   double x,
	   double y,
	   double z,
	   void* cs)
{ // testcquery
  return spatialdb_query(db, vals, numVals, x, y, z, cs);
} // testcquery

/* End of file  */
