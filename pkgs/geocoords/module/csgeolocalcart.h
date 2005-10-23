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

/** @file geocoords/module/csgeolocalcart.h
 *
 * @brief Bindings for CSGeoLocalCart
 */

#if !defined(pyspatialdata_geocoords_csgeolocalcart_h)
#define pyspatialdata_geocoords_csgeolocalcart_h

/// Call CSGeoLocalCart()
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeoLocalCart(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeoLocalCart__name__[];
extern char pyspatialdata_geocoords_CppCSGeoLocalCart__doc__[];

/// Call CSGeoLocalCart::origin
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeoLocalCart_origin(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeoLocalCart_origin__name__[];
extern char pyspatialdata_geocoords_CppCSGeoLocalCart_origin__doc__[];

#endif // pyspatialdata_geocoords_csgeolocalcart_h

// version
// $Id$

// End of file
