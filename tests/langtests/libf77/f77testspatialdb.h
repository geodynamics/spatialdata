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

#if !defined(_spatial_f77testspatialdb_h)
#define _spatial_f77testspatialdb_h

#if defined(NEEDS_F77_TRANSLATION)

// ----------------------------------------
#if defined(F77EXTERNS_LOWERCASE_TRAILINGBAR)

#define f77test_query_f f77test_query_

// ----------------------------------------
#elif defined(F77EXTERNS_NOTRAILINGBAR)

#define f77test_query_f f77test_query

// ----------------------------------------
#elif defined(F77EXTERNS_EXTRATRAILINGBAR)

#define f77test_query_f f77test_query__

// ----------------------------------------
#elif defined(F77EXTERNS_UPPERCASE_NOTRAILINGBAR)

#define f77test_query_f F77TEST_QUERY

// ----------------------------------------
#elif defined(F77EXTERNS_COMPAQ_F90)

// symbols that contain underbars get two underbars at the end
// symbols that do not contain underbars get one underbar at the end
// this applies to the FORTRAN external, not the local macro alias!!!

#define f77test_query_f f77test_query__

// ----------------------------------------
#else
#error "Unknown translation for FORTRAN external symbols"
#endif

#endif

// ----------------------------------------------------------------------
/** Fortran 77 function testing f77 interface for SpatialDB queries.
 *
 * C/C++ definition of function
 *
 * @param db Pointer to spatial database
 */
extern "C" {
  int f77test_query_f(void* db);
}

#endif // _spatial_f77testspatialdb_h

// version
// $Id: f77testspatialdb.h,v 1.1 2005/03/19 00:46:57 baagaard Exp $

// End of file 
