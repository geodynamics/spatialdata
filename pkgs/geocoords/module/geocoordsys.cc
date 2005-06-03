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

#include "geocoordsys.h"
#include "spatialdata/geocoords/GeoCoordSys.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppGeoCoordSys
char pyspatialdata_geocoords_CppGeoCoordSys__doc__[] = "";
char pyspatialdata_geocoords_CppGeoCoordSys__name__[] = "CppGeoCoordSys";

static char pyspatialdata_geocoords_CppGeoCoordSys_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoCoordSys(PyObject*, PyObject*)
{ // CppGeoCoordSys
  return PyCObject_FromVoidPtr((void*) new spatialdata::GeoCoordSys(),
	   pythiautil::BindingsTUtil<spatialdata::GeoCoordSys>::DeleteObj);
} // CppGeoCoordSys
        
// ----------------------------------------------------------------------
// CppGeoCoordSys_projection
char pyspatialdata_geocoords_CppGeoCoordSys_projection__doc__[] = "";
char pyspatialdata_geocoords_CppGeoCoordSys_projection__name__[] = "CppGeoCoordSys_projection";

static char pyspatialdata_geocoords_CppGeoCoordSys_projection_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoCoordSys_projection(PyObject*, PyObject* args)
{ // CppGeoCoordSys_projection
  PyObject* pyCoordSys = 0;
  PyObject* pyProjection = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppGeoCoordSys_projection",
			    &pyCoordSys, &pyProjection);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoCoordSys* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::GeoCoordSys*>::GetCObj(pyCoordSys, 
						      "GeoCoordSys*",
				     "Python handle to GeoCoordSys*");
    FIREWALL(0 != pCoordSys);

    const char* projection = PyString_AsString(pyProjection);

    pCoordSys->projection(projection);
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
} // CppGeoCoordSys_projection

// ----------------------------------------------------------------------
// CppGeoCoordSys_ellipsoid
char pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid__doc__[] = "";
char pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid__name__[] = "CppGeoCoordSys_ellipsoid";

static char pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoCoordSys_ellipsoid(PyObject*, PyObject* args)
{ // CppGeoCoordSys_ellipsoid
  PyObject* pyCoordSys = 0;
  PyObject* pyEllipsoid = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppGeoCoordSys_ellipsoid",
			    &pyCoordSys, &pyEllipsoid);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoCoordSys* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::GeoCoordSys*>::GetCObj(pyCoordSys, 
						      "GeoCoordSys*",
				     "Python handle to GeoCoordSys*");
    FIREWALL(0 != pCoordSys);

    const char* ellipsoid = PyString_AsString(pyEllipsoid);

    pCoordSys->ellipsoid(ellipsoid);
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
} // CppGeoCoordSys_ellipsoid

// ----------------------------------------------------------------------
// CppGeoCoordSys_datum
char pyspatialdata_geocoords_CppGeoCoordSys_datum__doc__[] = "";
char pyspatialdata_geocoords_CppGeoCoordSys_datum__name__[] = "CppGeoCoordSys_datum";

static char pyspatialdata_geocoords_CppGeoCoordSys_datum_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoCoordSys_datum(PyObject*, PyObject* args)
{ // CppGeoCoordSys_datum
  PyObject* pyCoordSys = 0;
  PyObject* pyDatum = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppGeoCoordSys_datum",
			    &pyCoordSys, &pyDatum);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoCoordSys* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::GeoCoordSys*>::GetCObj(pyCoordSys, 
						      "GeoCoordSys*",
				     "Python handle to GeoCoordSys*");
    FIREWALL(0 != pCoordSys);

    const char* datum = PyString_AsString(pyDatum);

    pCoordSys->datum(datum);
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
} // CppGeoCoordSys_datum

// ----------------------------------------------------------------------
// CppGeoCoordSys_units
char pyspatialdata_geocoords_CppGeoCoordSys_units__doc__[] = "";
char pyspatialdata_geocoords_CppGeoCoordSys_units__name__[] = "CppGeoCoordSys_units";

static char pyspatialdata_geocoords_CppGeoCoordSys_units_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoCoordSys_units(PyObject*, PyObject* args)
{ // CppGeoCoordSys_units
  PyObject* pyCoordSys = 0;
  PyObject* pyUnits = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppGeoCoordSys_units",
			    &pyCoordSys, &pyUnits);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoCoordSys* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::GeoCoordSys*>::GetCObj(pyCoordSys, 
						      "GeoCoordSys*",
				     "Python handle to GeoCoordSys*");
    FIREWALL(0 != pCoordSys);

    const char* units = PyString_AsString(pyUnits);

    pCoordSys->units(units);
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
} // CppGeoCoordSys_units

// ----------------------------------------------------------------------
// CppGeoCoordSys_initialize
char pyspatialdata_geocoords_CppGeoCoordSys_initialize__doc__[] = "";
char pyspatialdata_geocoords_CppGeoCoordSys_initialize__name__[] = "CppGeoCoordSys_initialize";

static char pyspatialdata_geocoords_CppGeoCoordSys_initialize_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppGeoCoordSys_initialize(PyObject*, PyObject* args)
{ // CppGeoCoordSys_initialize
  PyObject* pyCoordSys = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppGeoCoordSys_initialize", &pyCoordSys);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::GeoCoordSys* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::GeoCoordSys*>::GetCObj(pyCoordSys, 
						      "GeoCoordSys*",
				     "Python handle to GeoCoordSys*");
    FIREWALL(0 != pCoordSys);

    pCoordSys->initialize();
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
} // CppGeoCoordSys_initialize

// version
// $Id: geocoordsys.cc,v 1.2 2005/06/02 21:35:36 baagaard Exp $

// End of file
