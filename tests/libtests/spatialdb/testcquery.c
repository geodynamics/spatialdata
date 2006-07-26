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
	   double** pVals,
	   int numVals,
	   double x,
	   double y,
	   double z,
	   void* cs)
{ // testcquery
  return spatialdb_query(db, pVals, numVals, x, y, z, cs);
} // testcquery

/* End of file  */
