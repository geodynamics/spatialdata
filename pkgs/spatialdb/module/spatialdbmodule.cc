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

/** @file modue/spatialdbmodule.cc
 *
 * @brief Initialization of the spatialdb python module.
 */

#include <portinfo>

#include <Python.h>

#include "exceptions.h"
#include "bindings.h"

char pyspatialdb_module__doc__[] = "";

// Initialization function for the module (*must* be called initspatialdb)
extern "C"
void
initspatialdb(void)
{ // initspatialdb
  // create the module and add the functions
  PyObject* m = Py_InitModule4("spatialdb",
			       pyspatialdb_methods,
			       pyspatialdb_module__doc__,
			       0,
			       PYTHON_API_VERSION);

  // get its dictionary
  PyObject* d = PyModule_GetDict(m);

  // check for errors
  if (PyErr_Occurred()) {
    Py_FatalError("can't initialize module spatialdb");
  } // if

  // install the module exceptions
  pyspatialdb_runtimeError = 
    PyErr_NewException("spatialdb.runtime", 0, 0);
  PyDict_SetItemString(d, "RuntimeException", pyspatialdb_runtimeError);

  return;
} // initspatialdb

// version
// $Id: spatialdbmodule.cc,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
