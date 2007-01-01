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

#if !defined(spatialdata_spatialdb_cspatialdb_h)
#define spatialdata_spatialdb_cspatialdb_h

/** Call SpatialDB:Query().
 *
 * @param db Pointer to SpatialDB
 * @param vals Array for computed values (output from query), must be
 *   allocated BEFORE calling spatialdb_query*()
 * @param numVals Number of values expected (size of pVals array)
 * @param x C coordinate of location for query
 * @param y Y coordinate of location for query
 * @param z Z coordinate of location for query
 * @param cs Pointer to CoordSys
 *
 * @returns 0 on success, 1 on failure (i.e., values not set)
 */
int spatialdb_query(void* db, 
		    double* vals,
		    const int numVals,
		    const double x,
		    const double y,
		    const double z,
		    const void* cs);

#endif /* spatialdata_cspatialdb_h */

/* End of file  */
