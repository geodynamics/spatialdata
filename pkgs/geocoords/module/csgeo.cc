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

#include "csgeo.h"
#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CSGeo.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCSGeo
char pyspatialdata_geocoords_CppCSGeo__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeo__name__[] = "CppCSGeo";

static char pyspatialdata_geocoords_CppCSGeo_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeo(PyObject*, PyObject*)
{ // CppCSGeo
  return PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::CSGeo(),
    pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeo>::DeleteObj);
} // CppCSGeo
        
// ----------------------------------------------------------------------
// CppCSGeo_ellipsoid
char pyspatialdata_geocoords_CppCSGeo_ellipsoid__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeo_ellipsoid__name__[] = 
  "CppCSGeo_ellipsoid";

static char pyspatialdata_geocoords_CppCSGeo_ellipsoid_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeo_ellipsoid(PyObject*, PyObject* args)
{ // CppCSGeo_ellipsoid
  PyObject* pyCoordSys = 0;
  PyObject* pyEllipsoid = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCSGeo_ellipsoid",
			    &pyCoordSys, &pyEllipsoid);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeo*>::GetCObj(pyCoordSys, 
						      "CSGeo*",
				     "Python handle to CSGeo*");
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
} // CppCSGeo_ellipsoid

// ----------------------------------------------------------------------
// CppCSGeo_datumHoriz
char pyspatialdata_geocoords_CppCSGeo_datumHoriz__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeo_datumHoriz__name__[] =
  "CppCSGeo_datumHoriz";

static char pyspatialdata_geocoords_CppCSGeo_datumHoriz_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeo_datumHoriz(PyObject*, PyObject* args)
{ // CppCSGeo_datumHoriz
  PyObject* pyCoordSys = 0;
  PyObject* pyDatumHoriz = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCSGeo_datumHoriz",
			    &pyCoordSys, &pyDatumHoriz);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeo*>::GetCObj(pyCoordSys, 
						      "CSGeo*",
				     "Python handle to CSGeo*");
    FIREWALL(0 != pCoordSys);

    const char* datumHoriz = PyString_AsString(pyDatumHoriz);

    pCoordSys->datumHoriz(datumHoriz);
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
} // CppCSGeo_datumHoriz

// ----------------------------------------------------------------------
// CppCSGeo_datumVert
char pyspatialdata_geocoords_CppCSGeo_datumVert__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeo_datumVert__name__[] = 
  "CppCSGeo_datumVert";

static char pyspatialdata_geocoords_CppCSGeo_datumVert_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeo_datumVert(PyObject*, PyObject* args)
{ // CppCSGeo_datumVert
  PyObject* pyCoordSys = 0;
  PyObject* pyDatumVert = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCSGeo_datumVert",
			    &pyCoordSys, &pyDatumVert);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeo*>::GetCObj(pyCoordSys, 
						      "CSGeo*",
				     "Python handle to CSGeo*");
    FIREWALL(0 != pCoordSys);

    const char* datumVert = PyString_AsString(pyDatumVert);

    pCoordSys->datumVert(datumVert);
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
} // CppCSGeo_datumVert

// ----------------------------------------------------------------------
// CppCSGeo_isGeocentric
char pyspatialdata_geocoords_CppCSGeo_isGeocentric__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeo_isGeocentric__name__[] = 
  "CppCSGeo_isGeocentric";

static char pyspatialdata_geocoords_CppCSGeo_isGeocentric_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeo_isGeocentric(PyObject*, PyObject* args)
{ // CppCSGeo_isGeocentric
  PyObject* pyCoordSys = 0;
  int pyIsGeocentric = 0;
  int ok = PyArg_ParseTuple(args,
			    "Oi:CppCSGeo_isGeocentric",
			    &pyCoordSys, &pyIsGeocentric);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeo*>::GetCObj(pyCoordSys, 
						      "CSGeo*",
				     "Python handle to CSGeo*");
    FIREWALL(0 != pCoordSys);

    const bool isGeocentric = pyIsGeocentric ? true : false;

    pCoordSys->isGeocentric(isGeocentric);
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
} // CppCSGeo_isGeocentric

// ----------------------------------------------------------------------
// CppCSGeo_toMeters
char pyspatialdata_geocoords_CppCSGeo_toMeters__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeo_toMeters__name__[] =
  "CppCSGeo_toMeters";

static char pyspatialdata_geocoords_CppCSGeo_toMeters_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeo_toMeters(PyObject*, PyObject* args)
{ // CppCSGeo_toMeters
  PyObject* pyCoordSys = 0;
  double toMeters = 1.0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppCSGeo_toMeters",
			    &pyCoordSys, &toMeters);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeo*>::GetCObj(pyCoordSys, 
						      "CSGeo*",
				     "Python handle to CSGeo*");
    FIREWALL(0 != pCoordSys);

    pCoordSys->toMeters(toMeters);
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
} // CppCSGeo_toMeters

// version
// $Id$

// End of file
