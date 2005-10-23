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
#include "spatialdata/spatialdb/SpatialDB.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppSpatialDB_open
char pyspatialdb_CppSpatialDB_open__doc__[] = "";
char pyspatialdb_CppSpatialDB_open__name__[] = "CppSpatialDB_open";

static char pyspatialdb_CppSpatialDB_open_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSpatialDB_open(PyObject*, PyObject* args)
{ // CppSpatialDB_open
  PyObject* pyDB = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppSpatialDB_open", &pyDB);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::spatialdb::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    pDB->open();
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
} // CppSpatialDB_open

// ----------------------------------------------------------------------
// CppSpatialDB_close
char pyspatialdb_CppSpatialDB_close__doc__[] = "";
char pyspatialdb_CppSpatialDB_close__name__[] = "CppSpatialDB_close";

static char pyspatialdb_CppSpatialDB_close_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSpatialDB_close(PyObject*, PyObject* args)
{ // CppSpatialDB_close
  PyObject* pyDB = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CppSpatialDB_close", &pyDB);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::spatialdb::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    pDB->close();
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
} // CppSpatialDB_close

// ----------------------------------------------------------------------
// CppSpatialDB_queryVals
char pyspatialdb_CppSpatialDB_queryVals__doc__[] = "";
char pyspatialdb_CppSpatialDB_queryVals__name__[] = "CppSpatialDB_queryVals";

static char pyspatialdb_CppSpatialDB_queryVals_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSpatialDB_queryVals(PyObject*, PyObject* args)
{ // CppSpatialDB_queryVals
  PyObject* pyDB = 0;
  PyObject* pyNames = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSpatialDB_queryVals", &pyDB, &pyNames);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::spatialdb::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SpatialDB*>::GetCObj(pyDB, 
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
    pDB->queryVals(pNames, numNames);
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
} // CppSpatialDB_queryVals

// ----------------------------------------------------------------------
// CppSpatialDB_label
char pyspatialdb_CppSpatialDB_label__doc__[] = "";
char pyspatialdb_CppSpatialDB_label__name__[] = "CppSpatialDB_label";

static char pyspatialdb_CppSpatialDB_label_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSpatialDB_label(PyObject*, PyObject* args)
{ // CppSpatialDB_label
  PyObject* pyDB = 0;
  PyObject* pyLabel = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSpatialDB_label", &pyDB, &pyLabel);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::spatialdb::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SpatialDB*>::GetCObj(pyDB, 
							      "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    const char* label = PyString_AsString(pyLabel);
    pDB->label(label);
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
} // CppSpatialDB_label
        
// version
// $Id: spatialdb.cc,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
