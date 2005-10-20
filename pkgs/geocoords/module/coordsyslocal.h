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

/** @file geocoords/module/coordsyslocal.h
 *
 * @brief Bindings for CoordSysLocal
 */

#if !defined(pyspatialdata_geocoords_coordsyslocal_h)
#define pyspatialdata_geocoords_coordsyslocal_h

/// Call CoordSysLocal()
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysLocal(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysLocal__name__[];
extern char pyspatialdata_geocoords_CppCoordSysLocal__doc__[];

/// Call CoordSysLocal::localOrigin
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysLocal_localOrigin(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysLocal_localOrigin__name__[];
extern char pyspatialdata_geocoords_CppCoordSysLocal_localOrigin__doc__[];

/// Call CoordSysLocal::xyzToMeters
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters__name__[];
extern char pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters__doc__[];

#endif // pyspatialdata_geocoords_coordsyslocal_h

// version
// $Id$

// End of file
