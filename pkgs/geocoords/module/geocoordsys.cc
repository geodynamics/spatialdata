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
// $Id: geocoordsys.cc,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
