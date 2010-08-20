/*  -*- C -*-  */
/*
 * ======================================================================
 *
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
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
