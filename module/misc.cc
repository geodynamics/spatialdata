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

#include "misc.h"

// copyright

char pyspatialdata_copyright__doc__[] = "";
char pyspatialdata_copyright__name__[] = "copyright";

static char pyspatialdata_copyright_note[] = 
  "solver python module: Copyright (c) 2005 U.S. Geological Survey";

PyObject* pyspatialdata_copyright(PyObject*, PyObject*)
{ // pyspatialdata_copyright
  return Py_BuildValue("s", pyspatialdata_copyright_note);
} // pyspatialdata_copyright
        
// version
// $Id: misc.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
