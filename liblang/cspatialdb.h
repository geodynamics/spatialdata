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

#if !defined(_spatial_cspatialdb_h)
#define _spatial_cspatialdb_h

/** Call SpatialDB:Query().
 *
 * @param db Pointer to SpatialDB
 * @param pVals Pointer to computed values (output from query)
 * @param numVals Number of values expected (size of pVals array)
 * @param x Pointer to x coordinate of location for query
 * @param y Pointer to y coordinate of location for query
 * @param z Pointer to z coordinate of location for query
 */
void spatialdb_query(void* db, 
		     double** pVals,
		     const int numVals,
		     const double* x,
		     const double* y,
		     const double* z);

#endif /* _spatial_cspatialdb_h */

/* version */
/* $Id: cspatialdb.h,v 1.1 2005/03/19 00:47:11 baagaard Exp $ */

/* End of file  */
