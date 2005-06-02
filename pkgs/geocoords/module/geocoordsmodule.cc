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

/** @file geocoords/module/geocoordsmodule.cc
 *
 * @brief Initialization of the spatialdata geocoords python module.
 */

#include <portinfo>

#include <Python.h>

#include "exceptions.h"
#include "bindings.h"

char pyspatialdata_geocoords_module__doc__[] = "";

// Initialization function for the module (*must* be called initgeocoords)
extern "C"
void
initgeocoords(void)
{ // initgeocoords
  // create the module and add the functions
  PyObject* m = Py_InitModule4("geocoords",
			       pyspatialdata_geocoords_methods,
			       pyspatialdata_geocoords_module__doc__,
			       0,
			       PYTHON_API_VERSION);

  // get its dictionary
  PyObject* d = PyModule_GetDict(m);

  // check for errors
  if (PyErr_Occurred()) {
    Py_FatalError("Can't initialize module geocoords");
  } // if

  // install the module exceptions
  pyspatialdata_geocoords_runtimeError = 
    PyErr_NewException("geocoords.runtime", 0, 0);
  PyDict_SetItemString(d, "RuntimeException", 
		       pyspatialdata_geocoords_runtimeError);

  return;
} // initgeocoords

// version
// $Id: geocoordsmodule.cc,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
