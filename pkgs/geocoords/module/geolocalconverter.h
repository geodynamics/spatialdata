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

/** @file geocoords/module/geolocalconverter.h
 *
 * @brief Bindings for GeoLocalConverter
 */

#if !defined(pyspatialdata_geocoords_geolocalconverter_h)
#define pyspatialdata_geocoords_geolocalconverter_h

/// Call GeoLocalConverter()
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoLocalConverter(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoLocalConverter__name__[];
extern char pyspatialdata_geocoords_CppGeoLocalConverter__doc__[];

/// Call GeoLocalConverter::localOrigin
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin__name__[];
extern char pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin__doc__[];

/// Call GeoLocalConverter::convert
extern "C"
PyObject* pyspatialdata_geocoords_CppGeoLocalConverter_convert(PyObject*, PyObject*);
extern char pyspatialdata_geocoords_CppGeoLocalConverter_convert__name__[];
extern char pyspatialdata_geocoords_CppGeoLocalConverter_convert__doc__[];

#endif // pyspatialdata_geocoords_geolocalconverter_h

// version
// $Id: geolocalconverter.h,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
