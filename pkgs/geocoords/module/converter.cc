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

#include "converter.h"
#include "spatialdata/geocoords/Converter.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

#include <iostream>

// ----------------------------------------------------------------------
// CppConverter_convert
char pyspatialdata_geocoords_CppConverter_convert__doc__[] = "";
char pyspatialdata_geocoords_CppConverter_convert__name__[] = "CppConverter_convert";

static char pyspatialdata_geocoords_CppConverter_convert_note[] = 
  "spatialdata geocoords python module: U.S. Geological Survey";

PyObject*
pyspatialdata_geocoords_CppConverter_convert(PyObject*, PyObject* args)
{ // CppConverter_convert
  PyObject* pyCoordsSrcList = 0;
  PyObject* pyCSDest = 0;
  PyObject* pyCSSrc = 0;
  int ok = PyArg_ParseTuple(args,
			    "OOO:CppConverter_convert",
			    &pyCoordsSrcList, &pyCSDest, &pyCSSrc);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if
  
  PyObject* pyCoordsDestList = 0;
  try {
    spatialdata::geocoords::CoordSys* pCSDest = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSys*>::GetCObj(pyCSDest, 
						      "CoordSys*",
				     "Python handle to CoordSys*");
    FIREWALL(0 != pCSDest);

    spatialdata::geocoords::CoordSys* pCSSrc = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSys*>::GetCObj(pyCSSrc, 
						      "CoordSys*",
				     "Python handle to CoordSys*");
    FIREWALL(0 != pCSSrc);

    if (!PyList_Check(pyCoordsSrcList)) {
      PyErr_SetString(PyExc_TypeError, "Source coordinates must be a list.");
      return 0;
    } // if
    const int numLocs = PyList_Size(pyCoordsSrcList);
    const int numCoords = (numLocs > 0) ?
      PyList_Size(PyList_GetItem(pyCoordsSrcList, 0)) :
      0;
    const int size = numLocs * numCoords;
    double* pCoords = (size > 0) ? new double[size] : 0;
    for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
      PyObject* pyCoordsSrc = PyList_GetItem(pyCoordsSrcList, iLoc);
      for (int iCoord=0; iCoord < numCoords; ++iCoord)
	pCoords[i++] = PyFloat_AsDouble(PyList_GetItem(pyCoordsSrc, iCoord));
    } // for

    const bool is2D = (2 == numCoords) ? true : false;
    spatialdata::geocoords::Converter::convert(&pCoords, 
					       numLocs, *pCSDest, *pCSSrc,
					       is2D);

    pyCoordsDestList = PyList_New(numLocs);
    for (int iLoc=0, i=0; iLoc < numLocs; ++iLoc) {
      PyObject* pyCoords = PyList_New(numCoords);
      for (int iCoord=0; iCoord < numCoords; ++iCoord)
	PyList_SetItem(pyCoords, iCoord, PyFloat_FromDouble(pCoords[i++]));
      PyList_SetItem(pyCoordsDestList, iLoc, pyCoords);
    } // for

  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  Py_INCREF(pyCoordsDestList);
  return pyCoordsDestList;
} // CppConverter_convert

// version
// $Id$

// End of file
