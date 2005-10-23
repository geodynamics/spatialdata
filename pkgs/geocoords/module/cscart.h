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

/** @file geocoords/module/cscart.h
 *
 * @brief Bindings for CSCart
 */

#if !defined(pyspatialdata_geocoords_cscart_h)
#define pyspatialdata_geocoords_cscart_h

/// Call CSCart()
extern "C"
PyObject* pyspatialdata_geocoords_CppCSCart(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSCart__name__[];
extern char pyspatialdata_geocoords_CppCSCart__doc__[];

/// Call CSCart::toMeters
extern "C"
PyObject* pyspatialdata_geocoords_CppCSCart_toMeters(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSCart_toMeters__name__[];
extern char pyspatialdata_geocoords_CppCSCart_toMeters__doc__[];

#endif // pyspatialdata_geocoords_cscart_h

// version
// $Id$

// End of file
