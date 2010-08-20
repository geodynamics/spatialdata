/*  -*- C -*-  */
/*
 * ======================================================================
 *
 * Brad T. Aagaard, U.S. Geological Survey
 *
 * This code was developed as part of the Computational Infrastructure
 * for Geodynamics (http://geodynamics.org).
 *
 * Copyright (c) 2010 University of California, Davis
 *
 * See COPYING for license information.
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
 * @param coords Coordinates of point for query
 * @param numDims Number of dimensions for coordinates
 * @param cs Pointer to CoordSys
 *
 * @returns 0 on success, 1 on failure (i.e., values not set)
 */
int spatialdb_query(void* db, 
		    double* vals,
		    const int numVals,
		    const double* coords,
		    const int numDims,
		    const void* cs);

#endif /* spatialdata_cspatialdb_h */

/* End of file  */
