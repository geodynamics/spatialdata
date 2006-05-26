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
 * @param pVals Pointer to computed values (output from query)
 * @param numVals Number of values expected (size of pVals array)
 * @param x C coordinate of location for query
 * @param y Y coordinate of location for query
 * @param z Z coordinate of location for query
 * @param cs Pointer to CoordSys
 *
 * @returns 0 on success, 1 on failure (i.e., values not set)
 */
int spatialdb_query(void* db, 
		    double** pVals,
		    const int numVals,
		    const double x,
		    const double y,
		    const double z,
		    const void* cs);

#endif /* spatialdata_cspatialdb_h */

/* version */
/* $Id$ */

/* End of file  */
