// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

/** @file tests/langtests/libf77/f77testspatialdb.h
 *  @brief C/C++ header file defining Fortran f77 function.
 */

#if !defined(spatialdata_f77testspatialdb_h)
#define spatialdata_f77testspatialdb_h

// ----------------------------------------------------------------------
/** Fortran name mangling */
#define f77test_query_f \
  FC_FUNC_(f77test_query, F77TEST_QUERY)
/** Fortran 77 function testing f77 interface for SpatialDB queries.
 *
 * C/C++ definition of function
 *
 * @param db Pointer to spatial database
 * @param cs Pointer to coordinate system used in queries
 */
extern "C" {
  int f77test_query_f(void* db,
		      void* cs);
}

#endif // spatialdata_f77testspatialdb_h

// version
// $Id$

// End of file 
