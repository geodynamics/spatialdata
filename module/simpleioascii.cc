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
#include "spatialdata/SpatialDB.h"
#include "spatialdata/SimpleDB.h"
#include "spatialdata/SimpleIO.h"
#include "spatialdata/SimpleIOAscii.h"

#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppSimpleIOAscii
char pyspatialdata_CppSimpleIOAscii__doc__[] = "";
char pyspatialdata_CppSimpleIOAscii__name__[] = "CppSimpleIOAscii";

static char pyspatialdata_CppSimpleIOAscii_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdata_CppSimpleIOAscii(PyObject*, PyObject*)
{ // CppSimpleIOAscii
  return PyCObject_FromVoidPtr((void*) new spatial::SimpleIOAscii(),
		pythiautil::BindingsTUtil<spatial::SimpleIOAscii>::DeleteObj);
} // CppSimpleIOAscii
        
// version
// $Id: simpleioascii.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
