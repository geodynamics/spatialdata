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

#include "simpleio.h"
#include "spatialdata/SpatialDB.h"
#include "spatialdata/SimpleDB.h"
#include "spatialdata/SimpleIO.h"

#include <stdexcept> // USES std::exception

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppSimpleIO_Filename
char pyspatialdata_CppSimpleIO_Filename__doc__[] = "";
char pyspatialdata_CppSimpleIO_Filename__name__[] = "CppSimpleIO_Filename";

static char pyspatialdata_CppSimpleIO_Filename_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdata_CppSimpleIO_Filename(PyObject*, PyObject* args)
{ // CppSimpleIO_Filename
  PyObject* pyDB = 0;
  PyObject* pyFilename = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSimpleIO_Filename", &pyDB, &pyFilename);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatial::SimpleIO* pDB = 
      pythiautil::BindingsTUtil<spatial::SimpleIO*>::GetCObj(pyDB, 
							      "SimpleIO*",
					      "Python handle to SimpleIO*");
    FIREWALL(0 != pDB);
    const char* filename = PyString_AsString(pyFilename);
    pDB->Filename(filename);
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
} // CppSimpleIO_Filename
        
// version
// $Id: simpleio.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
