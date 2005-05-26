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

#include "simpleioascii.h"
#include "spatialdata/spatialdb/SpatialDB.h"
#include "spatialdata/spatialdb/SimpleDB.h"
#include "spatialdata/spatialdb/SimpleIO.h"
#include "spatialdata/spatialdb/SimpleIOAscii.h"

#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppSimpleIOAscii
char pyspatialdb_CppSimpleIOAscii__doc__[] = "";
char pyspatialdb_CppSimpleIOAscii__name__[] = "CppSimpleIOAscii";

static char pyspatialdb_CppSimpleIOAscii_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSimpleIOAscii(PyObject*, PyObject*)
{ // CppSimpleIOAscii
  return PyCObject_FromVoidPtr((void*) new spatialdata::SimpleIOAscii(),
		pythiautil::BindingsTUtil<spatialdata::SimpleIOAscii>::DeleteObj);
} // CppSimpleIOAscii
        
// version
// $Id: simpleioascii.cc,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
