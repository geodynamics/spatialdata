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

#if defined(NEEDS_F77_TRANSLATION)

// ----------------------------------------------------------------------
#if defined(F77EXTERNS_LOWERCASE_TRAILINGBAR)

#define spatialdb_query_f spatialdb_query_f_

// ----------------------------------------------------------------------
#elif defined(F77EXTERNS_NOTRAILINGBAR)

#define spatialdb_query_f spatialdb_query_f

// ----------------------------------------------------------------------
#elif defined(F77EXTERNS_EXTRATRAILINGBAR)

#define spatialdb_query_f spatialdb_query_f__

// ----------------------------------------------------------------------
#elif defined(F77EXTERNS_UPPERCASE_NOTRAILINGBAR)

#define spatialdb_query_f SPATIALDB_QUERY_F

// ----------------------------------------------------------------------
#elif defined(F77EXTERNS_UNDERBAR_EXTRATRAILINGBAR) || \
  defined(F77EXTERNS_COMPAQ_F90)

// symbols that contain underbars get two underbars at the end
// symbols that do not contain underbars get one underbar at the end

#define spatialdb_query_f spatialdb_query_f__

// ----------------------------------------------------------------------
#else
#error "Unknown translation for FORTRAN external symbols"
#endif

#endif

// ----------------------------------------------------------------------
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
 */
extern "C"
void spatialdb_query_f(void* db,
		       double* pVals,
		       const int* numVals,
		       const double* x,
		       const double* y,
		       const double* z,
		       const void* cs);

#endif /* spatialdata_spatialdb_f77spatialdb_h */

// version
// $Id: f77spatialdb.h,v 1.1 2005/05/25 18:42:58 baagaard Exp $

// End of file
