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

#include "cscart.h"
#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CSCart.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCSCart
char pyspatialdata_geocoords_CppCSCart__doc__[] = "";
char pyspatialdata_geocoords_CppCSCart__name__[] = "CppCSCart";

static char pyspatialdata_geocoords_CppCSCart_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSCart(PyObject*, PyObject*)
{ // CppCSCart
  return PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::CSCart(),
    pythiautil::BindingsTUtil<spatialdata::geocoords::CSCart>::DeleteObj);
} // CppCSCart
        
// ----------------------------------------------------------------------
// CppCSCart_toMeters
char pyspatialdata_geocoords_CppCSCart_toMeters__doc__[] = "";
char pyspatialdata_geocoords_CppCSCart_toMeters__name__[] =
  "CppCSCart_toMeters";

static char pyspatialdata_geocoords_CppCSCart_toMeters_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSCart_toMeters(PyObject*, PyObject* args)
{ // CppCSCart_toMeters
  PyObject* pyCoordSys = 0;
  double toMeters = 1.0;
  int ok = PyArg_ParseTuple(args,
			    "Od:CppCSCart_toMeters",
			    &pyCoordSys, &toMeters);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSCart* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSCart*>::GetCObj(pyCoordSys, 
						      "CSCart*",
				     "Python handle to CSCart*");
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
} // CppCSCart_toMeters

// version
// $Id$

// End of file
