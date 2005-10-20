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

/** @file geocoords/module/converter.h
 *
 * @brief Bindings for Converter
 */

#if !defined(pyspatialdata_geocoords_converter_h)
#define pyspatialdata_geocoords_converter_h

/// Call Converter::convert
extern "C"
PyObject* pyspatialdata_geocoords_CppConverter_convert(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppConverter_convert__name__[];
extern char pyspatialdata_geocoords_CppConverter_convert__doc__[];

#endif // pyspatialdata_geocoords_converter_h

// version
// $Id$

// End of file
