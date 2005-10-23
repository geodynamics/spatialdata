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

/** @file geocoords/module/csgeoproj.h
 *
 * @brief Bindings for CSGeoProj
 */

#if !defined(pyspatialdata_geocoords_csgeoproj_h)
#define pyspatialdata_geocoords_csgeoproj_h

/// Call CSGeoProj()
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeoProj(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeoProj__name__[];
extern char pyspatialdata_geocoords_CppCSGeoProj__doc__[];

/// Call CSGeoProj::projector
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeoProj_projector(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeoProj_projector__name__[];
extern char pyspatialdata_geocoords_CppCSGeoProj_projector__doc__[];

#endif // pyspatialdata_geocoords_csgeoproj_h

// version
// $Id$

// End of file
