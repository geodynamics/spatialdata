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

/** @file module/simpleioascii.h
 *
 * @brief Bindings for SimpleIOAscii
 */

#if !defined(pyspatialdb_simpleioascii_h)
#define pyspatialdb_simpleioascii_h

// CppSimpleIOAscii
/// Create C++ SimpleIOAscii object and return pointer to it
extern "C"
PyObject* pyspatialdb_CppSimpleIOAscii(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleIOAscii__name__[];
extern char pyspatialdb_CppSimpleIOAscii__doc__[];

// CppSimpleIOAscii_write
/// Call C++ SimpleIOAscii::write()
extern "C"
PyObject* pyspatialdb_CppSimpleIOAscii_write(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleIOAscii_write__name__[];
extern char pyspatialdb_CppSimpleIOAscii_write__doc__[];

#endif // pyspatialdb_simpleioascii_h

// version
// $Id: simpleioascii.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
