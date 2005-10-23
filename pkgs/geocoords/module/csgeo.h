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

/** @file geocoords/module/csgeo.h
 *
 * @brief Bindings for CSGeo
 */

#if !defined(pyspatialdata_geocoords_csgeo_h)
#define pyspatialdata_geocoords_csgeo_h

/// Call CSGeo()
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeo(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeo__name__[];
extern char pyspatialdata_geocoords_CppCSGeo__doc__[];

/// Call CSGeo::ellipsoid
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeo_ellipsoid(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeo_ellipsoid__name__[];
extern char pyspatialdata_geocoords_CppCSGeo_ellipsoid__doc__[];

/// Call CSGeo::datumHoriz
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeo_datumHoriz(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeo_datumHoriz__name__[];
extern char pyspatialdata_geocoords_CppCSGeo_datumHoriz__doc__[];

/// Call CSGeo::datumVert
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeo_datumVert(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeo_datumVert__name__[];
extern char pyspatialdata_geocoords_CppCSGeo_datumVert__doc__[];

/// Call CSGeo::isGeocentric
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeo_isGeocentric(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeo_isGeocentric__name__[];
extern char pyspatialdata_geocoords_CppCSGeo_isGeocentric__doc__[];

/// Call CSGeo::toMeters
extern "C"
PyObject* pyspatialdata_geocoords_CppCSGeo_toMeters(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppCSGeo_toMeters__name__[];
extern char pyspatialdata_geocoords_CppCSGeo_toMeters__doc__[];

#endif // pyspatialdata_geocoords_csgeo_h

// version
// $Id$

// End of file
