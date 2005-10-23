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

#include "langtestspatialdb.h"
extern "C" {
#include "../libc/ctestspatialdb.h"
}
#include "../libf77/f77testspatialdb.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// cTestQuery
char pytestlangspatialdb_cTestQuery__doc__[] = "";
char pytestlangspatialdb_cTestQuery__name__[] = "cTestQuery";

static char pytestlangspatialdb_cTestQuery_note[] = 
  "ctestspatialdata python module: U.S. Geological Survey";

PyObject*
pytestlangspatialdb_cTestQuery(PyObject*, PyObject* args)
{ // cTestQuery
  PyObject* pyDB = 0;
  PyObject* pyCS = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:cTestQuery", &pyDB, &pyCS);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    void* pDB = 
      pythiautil::BindingsTUtil<void*>::GetCObj(pyDB, 
						"void*",
						"Python handle to void*");
    FIREWALL(0 != pDB);
    void* pCS = 
      pythiautil::BindingsTUtil<void*>::GetCObj(pyCS, 
						"void*",
						"Python handle to void*");
    FIREWALL(0 != pCS);
    const int err = ctest_query(pDB, pCS);
    if (err) {
      std::ostringstream msg;
      msg << "Error #" << err << " in C bindings.";
      throw std::runtime_error(msg.str());
    } // if
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
} // cTestQuery

// ----------------------------------------------------------------------
// f77TestQuery
char pytestlangspatialdb_f77TestQuery__doc__[] = "";
char pytestlangspatialdb_f77TestQuery__name__[] = "f77TestQuery";

static char pytestlangspatialdb_f77TestQuery_note[] = 
  "ctestspatialdata python module: U.S. Geological Survey";

PyObject*
pytestlangspatialdb_f77TestQuery(PyObject*, PyObject* args)
{ // f77TestQuery
  PyObject* pyDB = 0;
  PyObject* pyCS = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:f77TestQuery", &pyDB, &pyCS);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    void* pDB = 
      pythiautil::BindingsTUtil<void*>::GetCObj(pyDB, 
						"void*",
						"Python handle to void*");
    FIREWALL(0 != pDB);
    void* pCS = 
      pythiautil::BindingsTUtil<void*>::GetCObj(pyCS, 
						"void*",
						"Python handle to void*");
    FIREWALL(0 != pCS);
    const int err = f77test_query_f(pDB, pCS);
    if (err) {
      std::ostringstream msg;
      msg << "Error #" << err << " in f77 bindings.";
      throw std::runtime_error(msg.str());
    } // if
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
} // f77TestQuery

// version
// $Id: langtestspatialdb.cc,v 1.1 2005/05/25 18:43:03 baagaard Exp $

// End of file
