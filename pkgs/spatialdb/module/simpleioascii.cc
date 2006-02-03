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

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
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
  return PyCObject_FromVoidPtr((void*) new spatialdata::spatialdb::SimpleIOAscii(),
   pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleIOAscii>::DeleteObj);
} // CppSimpleIOAscii
        
// ----------------------------------------------------------------------
// CppSimpleIOAscii_write
char pyspatialdb_CppSimpleIOAscii_write__doc__[] = "";
char pyspatialdb_CppSimpleIOAscii_write__name__[] = "CppSimpleIOAscii_write";

static char pyspatialdb_CppSimpleIOAscii_write_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSimpleIOAscii_write(PyObject*, PyObject* args)
{ // CppSimpleDB
  PyObject* pyIO = 0;
  PyObject* pyData = 0;
  PyObject* pyCS = 0;
  int ok = PyArg_ParseTuple(args,
			    "OOO:CppSimpleIOAscii_write", 
			    &pyIO, &pyData, &pyCS);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if


  try {
    spatialdata::spatialdb::SimpleIOAscii* pIO = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleIOAscii*>::GetCObj(pyIO, 
							     "SimpleIOAscii*",
					      "Python handle to SimpleIOAscii*");
    FIREWALL(0 != pIO);

    spatialdata::spatialdb::SimpleDB::DataStruct* pData = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleDB::DataStruct*>::GetCObj(pyData, 
							     "DataStruct*",
					      "Python handle to DataStruct*");
    FIREWALL(0 != pData);

    spatialdata::geocoords::CoordSys* pCS = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSys*>::GetCObj(pyCS, 
							     "CoordSys*",
					      "Python handle to CoordSys*");
    FIREWALL(0 != pCS);

    pIO->write(*pData, pCS);
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
} // CppSimpleIOAscii_write
        
// version
// $Id: simpleioascii.cc,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
