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

#include "ctestspatialdb.h"

#include "spatialdata/cspatialdb.h" /* USES spatialdb_query */

#include <stdlib.h> // USES malloc(), free()

/* Query SpatialDB using C. */
int
ctest_query(void* db)
{ /* ctest_query */

  const int numVals = 2;
  const double queryLoc[] = {1.0, 2.0, 3.0};
  const double pVals[] = { 6.3, 4.7 };

  int err = 0;
  int iVal = 0;

  double* pValsQ = (numVals > 0) ? malloc(sizeof(double)*numVals) : 0;
  spatialdb_query(db, &pValsQ, numVals, 
		  &queryLoc[0], &queryLoc[1], &queryLoc[2]);
  const double tolerance = 1.0e-06;
  for (iVal=0; iVal < numVals; ++iVal)
    if (1.0 - pValsQ[iVal]/pVals[numVals-iVal-1] > tolerance) {
      err = 1;
      break;
    } /* if */
  
  free(pValsQ); pValsQ = 0;

  return err;
} /* ctest_query */

/* version */
/* $Id: ctestspatialdb.c,v 1.1 2005/03/19 00:46:56 baagaard Exp $ */

/* End of file  */
