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

#if !defined(pyspatialdata_simpleioascii_h)
#define pyspatialdata_simpleioascii_h

// CppSimpleIOAscii
/// Create C++ SimpleIOAscii object and return pointer to it
extern "C"
PyObject* pyspatialdata_CppSimpleIOAscii(PyObject*, PyObject*);
extern char pyspatialdata_CppSimpleIOAscii__name__[];
extern char pyspatialdata_CppSimpleIOAscii__doc__[];

#endif // pyspatialdata_simpleioascii_h

// version
// $Id: simpleioascii.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
