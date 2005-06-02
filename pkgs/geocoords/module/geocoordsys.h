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

/// Call GeoCoordSys::initialize
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoCoordSys_initialize(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoCoordSys_initialize__name__[];
extern char pyspatialdata_geocoords_CppGeoCoordSys_initialize__doc__[];

#endif // pyspatialdata_geocoords_geocoordsys_h

// version
// $Id: geocoordsys.h,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
