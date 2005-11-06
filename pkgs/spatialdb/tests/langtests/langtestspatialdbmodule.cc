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

/** @file tests/langtests/module/langtestspatialdbmodule.cc
 *
 * @brief Initialization of the langtestspatialdb python module.
 */

#include <portinfo>

#include <Python.h>

#include "exceptions.h"
#include "bindings.h"

char pytestlangspatialdb_module__doc__[] = "";

// Initialization function for the module (*must* be called initlangtestspatialdb)
extern "C"
void
initlangtestspatialdb(void)
{ // initlangtestspatialdb
  // create the module and add the functions
  PyObject* m = Py_InitModule4("langtestspatialdb",
			       pytestlangspatialdb_methods,
			       pytestlangspatialdb_module__doc__,
			       0,
			       PYTHON_API_VERSION);

  // get its dictionary
  PyObject* d = PyModule_GetDict(m);

  // check for errors
  if (PyErr_Occurred()) {
    Py_FatalError("can't initialize module langtestspatialdb");
  } // if

  // install the module exceptions
  pytestlangspatialdb_runtimeError = 
    PyErr_NewException("langtestspatialdb.runtime", 0, 0);
  PyDict_SetItemString(d, "RuntimeException", pytestlangspatialdb_runtimeError);

  return;
} // initlangtestspatialdb

// version
// $Id$

// End of file
