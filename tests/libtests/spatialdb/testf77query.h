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

#if !defined(spatialdata_spatialdb_testf77query_h)
#define spatialdata_spatialdb_testf77query_h

/** Fortran name mangling */
#define testf77query \
  FC_FUNC_(testf77query, TESTF77QUERY)
/** Call spatialdb_query_f().
 *
 * @param db Pointer to SpatialDB
 * @param vals Array for computed values (output from query)
 * @param numVals Number of values expected (size of pVals array)
 * @param coords Coordinates of location for query
 * @param numDims Number of dimensions for coordinates
 * @param cs Pointer to CoordSys
 *
 * @returns 0 on success, 1 on failure (i.e., values not set)
 */
int testf77query(void* db,
		 double* vals,
		 int numVals,
		 const double* coords,
		 const int numDims,
		 void* cs);

#endif /* spatialdata_spatialdb_testf77query_h */

/* End of file  */
