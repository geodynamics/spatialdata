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

/** @file geocoords/module/geocoordsys.h
 *
 * @brief Bindings for GeoCoordSys
 */

#if !defined(pyspatialdata_geocoords_geocoordsys_h)
#define pyspatialdata_geocoords_geocoordsys_h

/// Call GeoCoordSys()
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys__doc__[];

/// Call GeoCoordSys::projection
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys_projection(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys_projection__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys_projection__doc__[];

/// Call GeoCoordSys::ellipsoid
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid__doc__[];

/// Call GeoCoordSys::datum
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys_datum(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys_datum__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys_datum__doc__[];

/// Call GeoCoordSys::units
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys_units(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys_units__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys_units__doc__[];

/// Call GeoCoordSys::initialize
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys_initialize(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys_initialize__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys_initialize__doc__[];

#endif // pyspatialdata_geocoords_geocoordsys_h

// version
// $Id: geocoordsys.h,v 1.2 2005/06/02 21:35:36 baagaard Exp $

// End of file
