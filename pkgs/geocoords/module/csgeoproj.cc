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

#include "csgeoproj.h"
#include "spatialdata/geocoords/CoordSys.h"
#include "spatialdata/geocoords/CSGeo.h"
#include "spatialdata/geocoords/CSGeoProj.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppCSGeoProj
char pyspatialdata_geocoords_CppCSGeoProj__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeoProj__name__[] =
  "CppCSGeoProj";

static char pyspatialdata_geocoords_CppCSGeoProj_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeoProj(PyObject*, PyObject*)
{ // CppCSGeoProj
  return PyCObject_FromVoidPtr((void*) new spatialdata::geocoords::CSGeoProj(),
    pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeoProj>::DeleteObj);
} // CppCSGeoProj
        
// ----------------------------------------------------------------------
// CppCSGeoProj_projector
char pyspatialdata_geocoords_CppCSGeoProj_projector__doc__[] = "";
char pyspatialdata_geocoords_CppCSGeoProj_projector__name__[] =
  "CppCSGeoProj_projector";

static char pyspatialdata_geocoords_CppCSGeoProj_projector_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppCSGeoProj_projector(PyObject*, PyObject* args)
{ // CppCSGeoProj_projector
  PyObject* pyCoordSys = 0;
  PyObject* pyProjector = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppCSGeoProj_projector",
			    &pyCoordSys, &pyProjector);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::geocoords::CSGeoProj* pCoordSys = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CSGeoProj*>::GetCObj(pyCoordSys, 
						      "CSGeoProj*",
				     "Python handle to CSGeoProj*");
    FIREWALL(0 != pCoordSys);

    spatialdata::geocoords::Projector* pProjector = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::Projector*>::GetCObj(pyProjector, 
						      "Projector*",
				     "Python handle to Projector*");
    FIREWALL(0 != pCoordSys);

    pCoordSys->projector(*pProjector);
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
} // CppCSGeoProj_projector

// version
// $Id$

// End of file
