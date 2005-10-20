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

/** @file geocoords/module/coordsysgeo.h
 *
 * @brief Bindings for CoordSysGeo
 */

#if !defined(pyspatialdata_geocoords_coordsysgeo_h)
#define pyspatialdata_geocoords_coordsysgeo_h

/// Call CoordSysGeo()
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysGeo(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysGeo__name__[];
extern char pyspatialdata_geocoords_CppCoordSysGeo__doc__[];

/// Call CoordSysGeo::ellipsoid
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid__name__[];
extern char pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid__doc__[];

/// Call CoordSysGeo::datumHoriz
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz__name__[];
extern char pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz__doc__[];

/// Call CoordSysGeo::datumVert
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysGeo_datumVert(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysGeo_datumVert__name__[];
extern char pyspatialdata_geocoords_CppCoordSysGeo_datumVert__doc__[];

/// Call CoordSysGeo::isGeocentric
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric__name__[];
extern char pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric__doc__[];

/// Call CoordSysGeo::elevToMeters
extern "C"
PyObject* pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters__name__[];
extern char pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters__doc__[];

#endif // pyspatialdata_geocoords_coordsysgeo_h

// version
// $Id$

// End of file
