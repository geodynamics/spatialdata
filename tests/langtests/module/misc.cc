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

char pytestlangspatialdb_copyright__doc__[] = "";
char pytestlangspatialdb_copyright__name__[] = "copyright";

static char pytestlangspatialdb_copyright_note[] = 
  "ctestspatialdata python module: Copyright (c) 2005 U.S. Geological Survey";

PyObject* pytestlangspatialdb_copyright(PyObject*, PyObject*)
{ // pytestlangspatialdb_copyright
  return Py_BuildValue("s", pytestlangspatialdb_copyright_note);
} // pytestlangspatialdb_copyright
        
// version
// $Id: misc.cc,v 1.1 2005/03/19 00:46:58 baagaard Exp $

// End of file
