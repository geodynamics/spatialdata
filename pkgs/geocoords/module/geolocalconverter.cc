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

#include "geolocalconverter.h"
#include "spatialdata/geocoords/GeoLocalConverter.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppGeoLocalConverter
char pyspatialdata_geocoords_CppGeoLocalConverter__doc__[] = "";
char pyspatialdata_geocoords_CppGeoLocalConverter__name__[] = "CppGeoLocalConverter";

static char pyspatialdata_geocoords_CppGeoLocalConverter_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoLocalConverter(PyObject*, PyObject* args)
{ // CppGeoLocalConverter
  PyObject* pyCoordSys = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppGeoLocalConverter_localOrigin",
			    &pyCoordSys);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  spatialdata::GeoCoordSys* pCoordSys = 
    pythiautil::BindingsTUtil<spatialdata::GeoCoordSys*>::GetCObj(pyCoordSys, 
							"GeoCoordSys*",
				       "Python handle to GeoCoordSys*");
  FIREWALL(0 != pCoordSys);

  return PyCObject_FromVoidPtr((void*) new spatialdata::GeoLocalConverter(*pCoordSys),
	   pythiautil::BindingsTUtil<spatialdata::GeoLocalConverter>::DeleteObj);
} // CppGeoLocalConverter
        
// ----------------------------------------------------------------------
// CppGeoLocalConverter_localOrigin
char pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin__doc__[] = "";
char pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin__name__[] = "CppGeoLocalConverter_localOrigin";

static char pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoLocalConverter_localOrigin(PyObject*, PyObject* args)
{ // CppGeoLocalConverter_localOrigin
  PyObject* pyConverter = 0;
  double lon = 0;
  double lat = 0;
  double elev = 0;
  int ok = PyArg_ParseTuple(args,
			    "Oddd:CppGeoLocalConverter_localOrigin",
			    &pyConverter,
			    &lon, &lat, &elev);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoLocalConverter* pConverter = 
      pythiautil::BindingsTUtil<spatialdata::GeoLocalConverter*>::GetCObj(pyConverter, 
						      "GeoLocalConverter*",
				     "Python handle to GeoLocalConverter*");
    FIREWALL(0 != pConverter);

    pConverter->localOrigin(lon, lat, elev);
  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  Py_INCREF(Py_None);
  return Py_None;
} // CppGeoLocalConverter_localOrigin

// ----------------------------------------------------------------------
// CppGeoLocalConverter_convert
char pyspatialdata_geocoords_CppGeoLocalConverter_convert__doc__[] = "";
char pyspatialdata_geocoords_CppGeoLocalConverter_convert__name__[] = "CppGeoLocalConverter_convert";

static char pyspatialdata_geocoords_CppGeoLocalConverter_convert_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoLocalConverter_convert(PyObject*, PyObject* args)
{ // CppGeoLocalConverter_convert
  PyObject* pyConverter = 0;
  PyObject* pyCoords = 0;
  int numLocs = 0;
  int numCoords = 0;
  int invertFlag = 0;
  int ok = PyArg_ParseTuple(args,
			    "OOiii:CppGeoLocalConverter_convert",
			    &pyConverter, 
			    &pyCoords, &numLocs, &numCoords, &invertFlag);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoLocalConverter* pConverter = 
      pythiautil::BindingsTUtil<spatialdata::GeoLocalConverter*>::GetCObj(pyConverter, 
						      "GeoLocalConverter*",
				     "Python handle to GeoLocalConverter*");
    FIREWALL(0 != pConverter);

    double* pCoords = 
      pythiautil::BindingsTUtil<double*>::GetCObj(pyCoords, 
						  "double*",
						  "Python handle to double*");
    FIREWALL(0 != pCoords);

    const bool invert = invertFlag;
  
    if (3 != numCoords) {
      PyErr_SetString(PyExc_ValueError,
		      "C++ bindings error: "
		      "Number of coordinates per location must be 3.");
      return 0;
    }

    pConverter->convert(&pCoords, numLocs, invert);

  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  Py_INCREF(Py_None);
  return Py_None;
} // CppGeoLocalConverter_convert

// version
// $Id: geolocalconverter.cc,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
