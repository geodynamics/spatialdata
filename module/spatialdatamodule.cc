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

/** @file modue/spatialdatamodule.cc
 *
 * @brief Initialization of the spatialdata python module.
 */

#include <portinfo>

#include <Python.h>

#include "exceptions.h"
#include "bindings.h"

char pyspatialdata_module__doc__[] = "";

// Initialization function for the module (*must* be called initspatialdata)
extern "C"
void
initspatialdata(void)
{ // initspatialdata
  // create the module and add the functions
  PyObject* m = Py_InitModule4("spatialdata",
			       pyspatialdata_methods,
			       pyspatialdata_module__doc__,
			       0,
			       PYTHON_API_VERSION);

  // get its dictionary
  PyObject* d = PyModule_GetDict(m);

  // check for errors
  if (PyErr_Occurred()) {
    Py_FatalError("can't initialize module spatialdata");
  } // if

  // install the module exceptions
  pyspatialdata_runtimeError = 
    PyErr_NewException("spatialdata.runtime", 0, 0);
  PyDict_SetItemString(d, "RuntimeException", pyspatialdata_runtimeError);

  return;
} // initspatialdata

// version
// $Id: spatialdatamodule.cc,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
