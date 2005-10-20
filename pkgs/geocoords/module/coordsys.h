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

/** @file geocoords/module/coordsys.h
 *
 * @brief Bindings for CoordSys
 */

#if !defined(pyspatialdata_geocoords_coordsys_h)
#define pyspatialdata_geocoords_coordsys_h

/// Call CoordSys::initialize
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSys_initialize(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSys_initialize__name__[];
extern char pyspatialdata_geocoords_CppCoordSys_initialize__doc__[];

#endif // pyspatialdata_geocoords_coordsys_h

// version
// $Id$

// End of file
