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

/** @file geocoords/module/projector.h
 *
 * @brief Bindings for Projector
 */

#if !defined(pyspatialdata_geocoords_projector_h)
#define pyspatialdata_geocoords_projector_h

/// Call Projector()
extern "C"
PyObject* pyspatialdata_geocoords_CppProjector(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppProjector__name__[];
extern char pyspatialdata_geocoords_CppProjector__doc__[];

/// Call Projector::projection
extern "C"
PyObject* pyspatialdata_geocoords_CppProjector_projection(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppProjector_projection__name__[];
extern char pyspatialdata_geocoords_CppProjector_projection__doc__[];

/// Call Projector::units
extern "C"
PyObject* pyspatialdata_geocoords_CppProjector_units(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppProjector_units__name__[];
extern char pyspatialdata_geocoords_CppProjector_units__doc__[];

/// Call Projector::initialize
extern "C"
PyObject* pyspatialdata_geocoords_CppProjector_initialize(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppProjector_initialize__name__[];
extern char pyspatialdata_geocoords_CppProjector_initialize__doc__[];

/// Call Projector::project
extern "C"
PyObject* pyspatialdata_geocoords_CppProjector_project(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppProjector_project__name__[];
extern char pyspatialdata_geocoords_CppProjector_project__doc__[];

/// Call Projector::invproject
extern "C"
PyObject* pyspatialdata_geocoords_CppProjector_invproject(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppProjector_invproject__name__[];
extern char pyspatialdata_geocoords_CppProjector_invproject__doc__[];

#endif // pyspatialdata_geocoords_projector_h

// version
// $Id$

// End of file
