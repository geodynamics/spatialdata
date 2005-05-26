// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

/** @file module/misc.h
 *
 * @brief Python solver module copyright information
 */

#if !defined(pyspatialdb_misc_h)
#define pyspatialdb_misc_h

/// copyright
extern "C" {
PyObject* pyspatialdb_copyright(PyObject*, PyObject*);
extern char pyspatialdb_copyright__name__[];
extern char pyspatialdb_copyright__doc__[];
}

#endif // pyspatialdb_misc_h

// version
// $Id: misc.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
