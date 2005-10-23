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

/** @file module/simpleio.h
 *
 * @brief Bindings for SimpleIO
 */

#if !defined(pyspatialdb_simpleio_h)
#define pyspatialdb_simpleio_h

/// Call SimpleIO::filename
extern "C"
PyObject* pyspatialdb_CppSimpleIO_filename(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleIO_filename__name__[];
extern char pyspatialdb_CppSimpleIO_filename__doc__[];

#endif // pyspatialdb_simpleio_h

// version
// $Id: simpleio.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
