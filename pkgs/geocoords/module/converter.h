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

/// Call Converter::convert using coords in Python array
extern "C"
PyObject* pyspatialdata_geocoords_CppConverter_convertpy(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppConverter_convertpy__name__[];
extern char pyspatialdata_geocoords_CppConverter_convertpy__doc__[];

/// Call Converter::convert using coords in PyCObject 
extern "C"
PyObject* pyspatialdata_geocoords_CppConverter_convertcpp(PyObject*,
							  PyObject*);
extern char pyspatialdata_geocoords_CppConverter_convertcpp__name__[];
extern char pyspatialdata_geocoords_CppConverter_convertcpp__doc__[];

#endif // pyspatialdata_geocoords_converter_h

// version
// $Id$

// End of file
