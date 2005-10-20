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

#include "coordsysgeo.h"
#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CoordSysGeo.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCoordSysGeo
char pyspatialdata_geocoords_CppCoordSysGeo__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysGeo__name__[] = "CppCoordSysGeo";

static char pyspatialdata_geocoords_CppCoordSysGeo_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysGeo(PyObject*, PyObject*)
{ // CppCoordSysGeo
  return PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::CoordSysGeo(),
    pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo>::DeleteObj);
} // CppCoordSysGeo
        
// ----------------------------------------------------------------------
// CppCoordSysGeo_ellipsoid
char pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid__name__[] = "CppCoordSysGeo_ellipsoid";

static char pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysGeo_ellipsoid(PyObject*, PyObject* args)
{ // CppCoordSysGeo_ellipsoid
  PyObject* pyCoordSys = 0;
  PyObject* pyEllipsoid = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCoordSysGeo_ellipsoid",
			    &pyCoordSys, &pyEllipsoid);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo*>::GetCObj(pyCoordSys, 
						      "CoordSysGeo*",
				     "Python handle to CoordSysGeo*");
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
} // CppCoordSysGeo_ellipsoid

// ----------------------------------------------------------------------
// CppCoordSysGeo_datumHoriz
char pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz__name__[] = "CppCoordSysGeo_datumHoriz";

static char pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysGeo_datumHoriz(PyObject*, PyObject* args)
{ // CppCoordSysGeo_datumHoriz
  PyObject* pyCoordSys = 0;
  PyObject* pyDatumHoriz = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCoordSysGeo_datumHoriz",
			    &pyCoordSys, &pyDatumHoriz);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo*>::GetCObj(pyCoordSys, 
						      "CoordSysGeo*",
				     "Python handle to CoordSysGeo*");
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
} // CppCoordSysGeo_datumHoriz

// ----------------------------------------------------------------------
// CppCoordSysGeo_datumVert
char pyspatialdata_geocoords_CppCoordSysGeo_datumVert__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysGeo_datumVert__name__[] = "CppCoordSysGeo_datumVert";

static char pyspatialdata_geocoords_CppCoordSysGeo_datumVert_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysGeo_datumVert(PyObject*, PyObject* args)
{ // CppCoordSysGeo_datumVert
  PyObject* pyCoordSys = 0;
  PyObject* pyDatumVert = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCoordSysGeo_datumVert",
			    &pyCoordSys, &pyDatumVert);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo*>::GetCObj(pyCoordSys, 
						      "CoordSysGeo*",
				     "Python handle to CoordSysGeo*");
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
} // CppCoordSysGeo_datumVert

// ----------------------------------------------------------------------
// CppCoordSysGeo_isGeocentric
char pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric__name__[] = "CppCoordSysGeo_isGeocentric";

static char pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysGeo_isGeocentric(PyObject*, PyObject* args)
{ // CppCoordSysGeo_isGeocentric
  PyObject* pyCoordSys = 0;
  int pyIsGeocentric = 0;
  int ok = PyArg_ParseTuple(args,
			    "Oi:CppCoordSysGeo_isGeocentric",
			    &pyCoordSys, &pyIsGeocentric);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo*>::GetCObj(pyCoordSys, 
						      "CoordSysGeo*",
				     "Python handle to CoordSysGeo*");
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
} // CppCoordSysGeo_isGeocentric

// ----------------------------------------------------------------------
// CppCoordSysGeo_elevToMeters
char pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters__name__[] = "CppCoordSysGeo_elevToMeters";

static char pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysGeo_elevToMeters(PyObject*, PyObject* args)
{ // CppCoordSysGeo_elevToMeters
  PyObject* pyCoordSys = 0;
  double elevToMeters = 1.0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppCoordSysGeo_elevToMeters",
			    &pyCoordSys, &elevToMeters);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysGeo* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysGeo*>::GetCObj(pyCoordSys, 
						      "CoordSysGeo*",
				     "Python handle to CoordSysGeo*");
    FIREWALL(0 != pCoordSys);

    pCoordSys->elevToMeters(elevToMeters);
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
} // CppCoordSysGeo_elevToMeters

// version
// $Id$

// End of file
