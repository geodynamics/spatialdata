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

#include <portinfo>
#include <Python.h>

#include "misc.h" // misc methods

#include "geocoordsys.h"  // GeoCoordSys bindings
#include "geolocalconverter.h"  // GeoLocalConverter bindings

// the method table
struct PyMethodDef pyspatialdata_geocoords_methods[] = {

  // GeoCoordSys
  {pyspatialdata_geocoords_CppGeoCoordSys__name__,
   pyspatialdata_geocoords_CppGeoCoordSys,
   METH_VARARGS,
   pyspatialdata_geocoords_CppGeoCoordSys__doc__},
  
  {pyspatialdata_geocoords_CppGeoCoordSys_initialize__name__,
   pyspatialdata_geocoords_CppGeoCoordSys_initialize,
   METH_VARARGS,
   pyspatialdata_geocoords_CppGeoCoordSys_initialize__doc__},

  // GeoLocalConverter
  {pyspatialdata_geocoords_CppGeoLocalConverter__name__,
   pyspatialdata_geocoords_CppGeoLocalConverter,
   METH_VARARGS,
   pyspatialdata_geocoords_CppGeoLocalConverter__doc__},
  
  {pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin__name__,
   pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin,
   METH_VARARGS,
   pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin__doc__},

  {pyspatialdata_geocoords_CppGeoLocalConverter_convert__name__,
   pyspatialdata_geocoords_CppGeoLocalConverter_convert,
   METH_VARARGS,
   pyspatialdata_geocoords_CppGeoLocalConverter_convert__doc__},

  // misc
  {pyspatialdata_geocoords_copyright__name__,
   pyspatialdata_geocoords_copyright,
   METH_VARARGS,
   pyspatialdata_geocoords_copyright__doc__},

  // Sentinel
  {0, 0}

}; // pyspatialdata_geocoords_methods

// version
// $Id: bindings.cc,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
