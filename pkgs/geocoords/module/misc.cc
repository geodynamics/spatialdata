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

char pyspatialdata_geocoords_copyright__doc__[] = "";
char pyspatialdata_geocoords_copyright__name__[] = "copyright";

static char pyspatialdata_geocoords_copyright_note[] = 
  "spatialdata geocoords python module: Copyright (c) 2005 U.S. Geological Survey";

PyObject* pyspatialdata_geocoords_copyright(PyObject*, PyObject*)
{ // pyspatialdata_geocoords_copyright
  return Py_BuildValue("s", pyspatialdata_geocoords_copyright_note);
} // pyspatialdata_geocoords_copyright
        
// version
// $Id: misc.cc,v 1.1 2005/06/01 23:56:09 baagaard Exp $

// End of file
