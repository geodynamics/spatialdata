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

#include "coordsyslocal.h"
#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CoordSysLocal.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCoordSysLocal
char pyspatialdata_geocoords_CppCoordSysLocal__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysLocal__name__[] = "CppCoordSysLocal";

static char pyspatialdata_geocoords_CppCoordSysLocal_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysLocal(PyObject*, PyObject*)
{ // CppCoordSysLocal
  return PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::CoordSysLocal(),
    pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysLocal>::DeleteObj);
} // CppCoordSysLocal
        
// ----------------------------------------------------------------------
// CppCoordSysLocal_localOrigin
char pyspatialdata_geocoords_CppCoordSysLocal_localOrigin__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysLocal_localOrigin__name__[] = "CppCoordSysLocal_localOrigin";

static char pyspatialdata_geocoords_CppCoordSysLocal_localOrigin_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysLocal_localOrigin(PyObject*, PyObject* args)
{ // CppCoordSysLocal_localOrigin
  PyObject* pyCoordSys = 0;
  double originLon = 0;
  double originLat = 0;
  double originElev = 0;
  PyObject* pyEllipsoid = 0;
  PyObject* pyDatumHoriz = 0;
  PyObject* pyDatumVert = 0;
  int ok = PyArg_ParseTuple(args,
			    "OdddOOO:CppCoordSysLocal_originLon",
			    &pyCoordSys, 
			    &originLon, &originLat, &originElev,
			    &pyEllipsoid, &pyDatumHoriz, &pyDatumVert);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysLocal* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysLocal*>::GetCObj(pyCoordSys, 
						      "CoordSysLocal*",
				     "Python handle to CoordSysLocal*");
    FIREWALL(0 != pCoordSys);

    const char* ellipsoid = PyString_AsString(pyEllipsoid);
    const char* datumHoriz = PyString_AsString(pyDatumHoriz);
    const char* datumVert = PyString_AsString(pyDatumVert);

    pCoordSys->localOrigin(originLon, originLat, originElev,
			   ellipsoid, datumHoriz, datumVert);
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
} // CppCoordSysLocal_originLon

// ----------------------------------------------------------------------
// CppCoordSysLocal_xyzToMeters
char pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters__name__[] = "CppCoordSysLocal_xyzToMeters";

static char pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSysLocal_xyzToMeters(PyObject*, PyObject* args)
{ // CppCoordSysLocal_xyzToMeters
  PyObject* pyCoordSys = 0;
  double xyzToMeters = 1.0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppCoordSysLocal_xyzToMeters",
			    &pyCoordSys, &xyzToMeters);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSysLocal* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSysLocal*>::GetCObj(pyCoordSys, 
						      "CoordSysLocal*",
				     "Python handle to CoordSysLocal*");
    FIREWALL(0 != pCoordSys);

    pCoordSys->xyzToMeters(xyzToMeters);
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
} // CppCoordSysLocal_xyzToMeters

// version
// $Id$

// End of file
