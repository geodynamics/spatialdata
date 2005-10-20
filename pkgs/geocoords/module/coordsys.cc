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

#include "coordsys.h"
#include "spatialdata/geocoords/CoordSys.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCoordSys_initialize
char pyspatialdata_geocoords_CppCoordSys_initialize__doc__[] = "";
char pyspatialdata_geocoords_CppCoordSys_initialize__name__[] = "CppCoordSys_initialize";

static char pyspatialdata_coords_CppCoordSys_initialize_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCoordSys_initialize(PyObject*, PyObject* args)
{ // CppCoordSys_initialize
  PyObject* pyCoordSys = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppCoordSys_initialize", &pyCoordSys);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CoordSys* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSys*>::GetCObj(pyCoordSys, 
						      "CoordSys*",
				     "Python handle to CoordSys*");
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
} // CppCoordSys_initialize

// version
// $Id$

// End of file
