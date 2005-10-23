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

#include "csgeolocalcart.h"
#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CSGeo.h"
#include "spatialdata/geocoords/CSGeoLocalCart.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCSGeoLocalCart
char pyspatialdata_geocoords_CppCSGeoLocalCart__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeoLocalCart__name__[] =
  "CppCSGeoLocalCart";

static char pyspatialdata_geocoords_CppCSGeoLocalCart_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeoLocalCart(PyObject*, PyObject*)
{ // CppCSGeoLocalCart
  return PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::CSGeoLocalCart(),
    pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeoLocalCart>::DeleteObj);
} // CppCSGeoLocalCart
        
// ----------------------------------------------------------------------
// CppCSGeoLocalCart_origin
char pyspatialdata_geocoords_CppCSGeoLocalCart_origin__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeoLocalCart_origin__name__[] =
  "CppCSGeoLocalCart_origin";

static char pyspatialdata_geocoords_CppCSGeoLocalCart_origin_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeoLocalCart_origin(PyObject*, PyObject* args)
{ // CppCSGeoLocalCart_origin
  PyObject* pyCoordSys = 0;
  double originLon = 0;
  double originLat = 0;
  double originElev = 0;
  int ok = PyArg_ParseTuple(args,
			    "Oddd:CppCSGeoLocalCart_origin",
			    &pyCoordSys, 
			    &originLon, &originLat, &originElev);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeoLocalCart* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeoLocalCart*>::GetCObj(pyCoordSys, 
						      "CSGeoLocalCart*",
				     "Python handle to CSGeoLocalCart*");
    FIREWALL(0 != pCoordSys);

    pCoordSys->origin(originLon, originLat, originElev);
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
} // CppCSGeoLocalCart_origin

// version
// $Id$

// End of file
