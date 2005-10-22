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

#include "projector.h"
#include "spatialdata/geocoords/Projector.h"

#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CoordSysGeo.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppProjector
char pyspatialdata_geocoords_CppProjector__doc__[] = "";
char pyspatialdata_geocoords_CppProjector__name__[] = "CppProjector";

static char pyspatialdata_geocoords_CppProjector_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector(PyObject*, PyObject* args)
{ // CppProjector
  PyObject* pyCoordSys = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppProjector", &pyCoordSys);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  PyObject* pyProjector = 0;
  try {
    spatialdata::geocoords::CoordSysGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo*>::GetCObj(pyCoordSys, 
						      "CoordSysGeo*",
				     "Python handle to CoordSysGeo*");
    FIREWALL(0 != pCoordSys);

    pyProjector = 
      PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::Projector(*pCoordSys),
        pythiautil::BindingsTUtil<spatialdata::geocoords::Projector>::DeleteObj);
  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  return pyProjector;
} // CppProjector
        
// ----------------------------------------------------------------------
// CppProjector_projection
char pyspatialdata_geocoords_CppProjector_projection__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_projection__name__[] = "CppProjector_projection";

static char pyspatialdata_geocoords_CppProjector_projection_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_projection(PyObject*, PyObject* args)
{ // CppProjector_projection
  PyObject* pyProjector = 0;
  PyObject* pyProjection = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppProjector_projection",
			    &pyProjector, &pyProjection);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    const char* projection = PyString_AsString(pyProjection);

    pProjector->projection(projection);
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
} // CppProjector_projection

// ----------------------------------------------------------------------
// CppProjector_falseEasting
char pyspatialdata_geocoords_CppProjector_falseEasting__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_falseEasting__name__[] = "CppProjector_falseEasting";

static char pyspatialdata_geocoords_CppProjector_falseEasting_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_falseEasting(PyObject*, PyObject* args)
{ // CppProjector_falseEasting
  PyObject* pyProjector = 0;
  double falseEasting = 0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppProjector_falseEasting",
			    &pyProjector, &falseEasting);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    pProjector->falseEasting(falseEasting);
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
} // CppProjector_falseEasting

// ----------------------------------------------------------------------
// CppProjector_falseNorthing
char pyspatialdata_geocoords_CppProjector_falseNorthing__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_falseNorthing__name__[] = "CppProjector_falseNorthing";

static char pyspatialdata_geocoords_CppProjector_falseNorthing_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_falseNorthing(PyObject*, PyObject* args)
{ // CppProjector_falseNorthing
  PyObject* pyProjector = 0;
  double falseNorthing = 0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppProjector_falseNorthing",
			    &pyProjector, &falseNorthing);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    pProjector->falseNorthing(falseNorthing);
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
} // CppProjector_falseNorthing

// ----------------------------------------------------------------------
// CppProjector_scaleFactor
char pyspatialdata_geocoords_CppProjector_scaleFactor__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_scaleFactor__name__[] = "CppProjector_scaleFactor";

static char pyspatialdata_geocoords_CppProjector_scaleFactor_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_scaleFactor(PyObject*, PyObject* args)
{ // CppProjector_scaleFactor
  PyObject* pyProjector = 0;
  double scaleFactor = 0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppProjector_scaleFactor",
			    &pyProjector, &scaleFactor);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    pProjector->scaleFactor(scaleFactor);
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
} // CppProjector_scaleFactor

// ----------------------------------------------------------------------
// CppProjector_units
char pyspatialdata_geocoords_CppProjector_units__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_units__name__[] = "CppProjector_units";

static char pyspatialdata_geocoords_CppProjector_units_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_units(PyObject*, PyObject* args)
{ // CppProjector_units
  PyObject* pyProjector = 0;
  PyObject* pyDatumHoriz = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppProjector_units",
			    &pyProjector, &pyDatumHoriz);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    const char* units = PyString_AsString(pyDatumHoriz);

    pProjector->units(units);
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
} // CppProjector_units

// ----------------------------------------------------------------------
// CppProjector_initialize
char pyspatialdata_geocoords_CppProjector_initialize__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_initialize__name__[] = "CppProjector_initialize";

static char pyspatialdata_geocoords_CppProjector_initialize_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_initialize(PyObject*, PyObject* args)
{ // CppProjector_initialize
  PyObject* pyProjector = 0;
  int ok = PyArg_ParseTuple(args, "O:CppProjector_initialize", &pyProjector);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    pProjector->initialize();
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
} // CppProjector_initialize

// ----------------------------------------------------------------------
// CppProjector_project
char pyspatialdata_geocoords_CppProjector_project__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_project__name__[] = "CppProjector_project";

static char pyspatialdata_geocoords_CppProjector_project_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_project(PyObject*, PyObject* args)
{ // CppProjector_project
  PyObject* pyProjector = 0;
  PyObject* pyLonLatList = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppProjector_project",
			    &pyProjector, &pyLonLatList);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  PyObject* pyXYList = 0;
  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    if (!PyList_Check(pyLonLatList)) {
      PyErr_SetString(PyExc_TypeError, "lonlat must be a list");
      return 0;
    } // if
    const int numItems = PyList_Size(pyLonLatList);
    pyXYList = PyList_New(numItems);
    for (int i=0; i < numItems; ++i) {
      PyObject* pyLonLat = PyList_GetItem(pyLonLatList, i);
      const double lon = PyFloat_AsDouble(PyList_GetItem(pyLonLat, 0));
      const double lat = PyFloat_AsDouble(PyList_GetItem(pyLonLat, 1));
      double x = 0;
      double y = 0;
      pProjector->project(&x, &y, lon, lat);
      const int numCoords = 2;
      PyObject* pyXY = PyList_New(numCoords);
      PyList_SetItem(pyXY, 0, PyFloat_FromDouble(x));
      PyList_SetItem(pyXY, 1, PyFloat_FromDouble(y));
      PyList_SetItem(pyXYList, i, pyXY);
    } // for
  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  Py_INCREF(pyXYList);
  return pyXYList;
} // CppProjector_project

// ----------------------------------------------------------------------
// CppProjector_invproject
char pyspatialdata_geocoords_CppProjector_invproject__doc__[] = "";
char pyspatialdata_geocoords_CppProjector_invproject__name__[] = "CppProjector_invproject";

static char pyspatialdata_geocoords_CppProjector_invproject_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppProjector_invproject(PyObject*, PyObject* args)
{ // CppProjector_invproject
  PyObject* pyProjector = 0;
  PyObject* pyXYList = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppProjector_project",
			    &pyProjector, &pyXYList);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  PyObject* pyLonLatList = 0;
  try {
    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pProjector);

    if (!PyList_Check(pyXYList)) {
      PyErr_SetString(PyExc_TypeError, "lonlat must be a list");
      return 0;
    } // if
    const int numItems = PyList_Size(pyXYList);
    pyLonLatList = PyList_New(numItems);
    for (int i=0; i < numItems; ++i) {
      PyObject* pyXY = PyList_GetItem(pyXYList, i);
      const double x = PyFloat_AsDouble(PyList_GetItem(pyXY, 0));
      const double y = PyFloat_AsDouble(PyList_GetItem(pyXY, 1));
      double lon = 0;
      double lat = 0;
      pProjector->invproject(&lon, &lat, x, y);
      const int numCoords = 2;
      PyObject* pyLonLat = PyList_New(numCoords);
      PyList_SetItem(pyLonLat, 0, PyFloat_FromDouble(lon));
      PyList_SetItem(pyLonLat, 1, PyFloat_FromDouble(lat));
      PyList_SetItem(pyLonLatList, i, pyLonLat);
    } // for
  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  Py_INCREF(pyLonLatList);
  return pyLonLatList;
} // CppProjector_invproject

// version
// $Id$

// End of file
