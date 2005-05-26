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

char pyspatialdb_copyright__doc__[] = "";
char pyspatialdb_copyright__name__[] = "copyright";

static char pyspatialdb_copyright_note[] = 
  "solver python module: Copyright (c) 2005 U.S. Geological Survey";

PyObject* pyspatialdb_copyright(PyObject*, PyObject*)
{ // pyspatialdb_copyright
  return Py_BuildValue("s", pyspatialdb_copyright_note);
} // pyspatialdb_copyright
        
// version
// $Id: misc.cc,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
