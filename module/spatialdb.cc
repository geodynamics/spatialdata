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

#include "spatialdb.h"
#include "spatialdata/SpatialDB.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppSpatialDB_Open
char pyspatialdata_CppSpatialDB_Open__doc__[] = "";
char pyspatialdata_CppSpatialDB_Open__name__[] = "CppSpatialDB_Open";

static char pyspatialdata_CppSpatialDB_Open_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdata_CppSpatialDB_Open(PyObject*, PyObject* args)
{ // CppSpatialDB_Open
  PyObject* pyDB = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppSpatialDB_Open", &pyDB);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatial::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatial::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    pDB->Open();
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
} // CppSpatialDB_Open

// ----------------------------------------------------------------------
// CppSpatialDB_Close
char pyspatialdata_CppSpatialDB_Close__doc__[] = "";
char pyspatialdata_CppSpatialDB_Close__name__[] = "CppSpatialDB_Close";

static char pyspatialdata_CppSpatialDB_Close_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdata_CppSpatialDB_Close(PyObject*, PyObject* args)
{ // CppSpatialDB_Close
  PyObject* pyDB = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppSpatialDB_Close", &pyDB);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatial::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatial::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    pDB->Close();
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
} // CppSpatialDB_Close

// ----------------------------------------------------------------------
// CppSpatialDB_QueryVals
char pyspatialdata_CppSpatialDB_QueryVals__doc__[] = "";
char pyspatialdata_CppSpatialDB_QueryVals__name__[] = "CppSpatialDB_QueryVals";

static char pyspatialdata_CppSpatialDB_QueryVals_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdata_CppSpatialDB_QueryVals(PyObject*, PyObject* args)
{ // CppSpatialDB_QueryVals
  PyObject* pyDB = 0;
  PyObject* pyNames = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSpatialDB_QueryVals", &pyDB, &pyNames);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatial::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatial::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    if (!PyList_Check(pyNames))
      throw std::runtime_error("Names of values must be a list.");
    const int numNames = PyList_Size(pyNames);
    const char** pNames = 
      (numNames > 0) ? new const char*[numNames] : 0;
    for (int iName=0; iName < numNames; ++iName) {
      PyObject *pyName = PyList_GetItem(pyNames, iName);
      pNames[iName] = PyString_AsString(pyName);
    } // for
    pDB->QueryVals(pNames, numNames);
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
} // CppSpatialDB_QueryVals

// ----------------------------------------------------------------------
// CppSpatialDB_Label
char pyspatialdata_CppSpatialDB_Label__doc__[] = "";
char pyspatialdata_CppSpatialDB_Label__name__[] = "CppSpatialDB_Label";

static char pyspatialdata_CppSpatialDB_Label_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdata_CppSpatialDB_Label(PyObject*, PyObject* args)
{ // CppSpatialDB_Label
  PyObject* pyDB = 0;
  PyObject* pyLabel = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSpatialDB_Label", &pyDB, &pyLabel);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatial::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatial::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    const char* label = PyString_AsString(pyLabel);
    pDB->Label(label);
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
} // CppSpatialDB_Label
        
// version
// $Id: spatialdb.cc,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
