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

#if !defined(pyspatialdata_simpleio_h)
#define pyspatialdata_simpleio_h

/// Call SimpleIO::Filename
extern "C"
PyObject* pyspatialdata_CppSimpleIO_Filename(PyObject*, PyObject*);
extern char pyspatialdata_CppSimpleIO_Filename__name__[];
extern char pyspatialdata_CppSimpleIO_Filename__doc__[];

#endif // pyspatialdata_simpleio_h

// version
// $Id: simpleio.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
