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
// CTestQuery
char pytestlangspatialdb_CTestQuery__doc__[] = "";
char pytestlangspatialdb_CTestQuery__name__[] = "CTestQuery";

static char pytestlangspatialdb_CTestQuery_note[] = 
  "ctestspatialdata python module: U.S. Geological Survey";

PyObject*
pytestlangspatialdb_CTestQuery(PyObject*, PyObject* args)
{ // CTestQuery
  PyObject* pyDB = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:CTestQuery", &pyDB);
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
    const int err = ctest_query(pDB);
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
} // CTestQuery

// ----------------------------------------------------------------------
// F77TestQuery
char pytestlangspatialdb_F77TestQuery__doc__[] = "";
char pytestlangspatialdb_F77TestQuery__name__[] = "F77TestQuery";

static char pytestlangspatialdb_F77TestQuery_note[] = 
  "ctestspatialdata python module: U.S. Geological Survey";

PyObject*
pytestlangspatialdb_F77TestQuery(PyObject*, PyObject* args)
{ // F77TestQuery
  PyObject* pyDB = 0;
  int ok = PyArg_ParseTuple(args,
			    "O:F77TestQuery", &pyDB);
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
    const int err = f77test_query_f(pDB);
    if (err) {
      std::ostringstream msg;
      msg << "Error #" << err << " in F77 bindings.";
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
} // F77TestQuery

// version
// $Id: langtestspatialdb.cc,v 1.1 2005/03/19 00:46:57 baagaard Exp $

// End of file
