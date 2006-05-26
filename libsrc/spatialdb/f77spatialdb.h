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

#if !defined(spatialdata_spatialdb_f77spatialdb_h)
#define spatialdata_spatialdb_f77spatialdb_h


// ----------------------------------------------------------------------
/** Fortran name mangling */
#define spatialdb_query_f \
  FC_FUNC_(spatialdb_query_f, SPATIALDB_QUERY_F)
/** Call SpatialDB:Query().
 *
 * @param db Pointer to SpatialDB
 * @param pVals Pointer to computed values (output from query)
 * @param addrF Fortran address used to access values
 * @param addrOffset Offset used to access values from Fortran
 * @param x Pointer to x coordinate of location for query
 * @param y Pointer to y coordinate of location for query
 * @param z Pointer to z coordinate of location for query
 * @param cs Pointer to CS
 * @param ok Set to 0 on success, 1 on failure (i.e., values not set)
 */
extern "C"
void spatialdb_query_f(void* db,
		       double* pVals,
		       const int* numVals,
		       const double* x,
		       const double* y,
		       const double* z,
		       const void* cs,
		       int* ok);

#endif /* spatialdata_spatialdb_f77spatialdb_h */

// version
// $Id$

// End of file
