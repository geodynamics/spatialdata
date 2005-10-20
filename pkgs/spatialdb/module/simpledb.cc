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

#include "simpledb.h"
#include "spatialdata/spatialdb/SpatialDB.h"
#include "spatialdata/spatialdb/SimpleDB.h"

#include <stdexcept> // USES std::exception
#include <sstream> // USES std::ostringstream

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppSimpleDB
char pyspatialdb_CppSimpleDB__doc__[] = "";
char pyspatialdb_CppSimpleDB__name__[] = "CppSimpleDB";

static char pyspatialdb_CppSimpleDB_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSimpleDB(PyObject*, PyObject*)
{ // CppSimpleDB
  return PyCObject_FromVoidPtr((void*) new spatialdata::spatialdb::SimpleDB(),
       pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleDB>::DeleteObj);
} // CppSimpleDB
        
// ----------------------------------------------------------------------
// CppSimpleDB_QueryType
char pyspatialdb_CppSimpleDB_QueryType__doc__[] = "";
char pyspatialdb_CppSimpleDB_QueryType__name__[] = "CppSimpleDB_QueryType";

static char pyspatialdb_CppSimpleDB_QueryType_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSimpleDB_QueryType(PyObject*, PyObject* args)
{ // CppSimpleDB
  PyObject* pyDB = 0;
  PyObject* pyQueryString = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSimpleDB_QueryType", 
			    &pyDB, &pyQueryString);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if


  try {
    spatialdata::spatialdb::SimpleDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleDB*>::GetCObj(pyDB, 
							     "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    const char* queryString = PyString_AsString(pyQueryString);
    spatialdata::spatialdb::SimpleDB::QueryEnum queryType = 
      spatialdata::spatialdb::SimpleDB::NEAREST;
    if (0 == strcasecmp(queryString, "Nearest"))
      queryType = spatialdata::spatialdb::SimpleDB::NEAREST;
    else if (0 == strcasecmp(queryString, "Linear"))
      queryType = spatialdata::spatialdb::SimpleDB::LINEAR;
    else {
      std::ostringstream msg;
      msg << "Could not parse query type string '" << queryString << "'\n"
	  << "into a know query type.\n"
	  << "Known query types and their strings (case insensitive):\n"
	  << "  NEAREST: 'Nearest'\n"
	  << "  LINEAR: 'Linear'";
      throw std::runtime_error(msg.str());
    } // else
    pDB->QueryType(queryType);
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
} // CppSimpleDB_QueryType
        
// ----------------------------------------------------------------------
// CppSimpleDB_IOHandler
char pyspatialdb_CppSimpleDB_IOHandler__doc__[] = "";
char pyspatialdb_CppSimpleDB_IOHandler__name__[] = "CppSimpleDB_IOHandler";

static char pyspatialdb_CppSimpleDB_IOHandler_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppSimpleDB_IOHandler(PyObject*, PyObject* args)
{ // CppSimpleDB
  PyObject* pyDB = 0;
  PyObject* pyIOHandler = 0;
  int ok = PyArg_ParseTuple(args,
			    "OO:CppSimpleDB_IOHandler", 
			    &pyDB, &pyIOHandler);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if


  try {
    spatialdata::spatialdb::SimpleDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleDB*>::GetCObj(pyDB, 
							     "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);
    spatialdata::spatialdb::SimpleIO* pIOHandler = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleIO*>::GetCObj(pyIOHandler, 
							     "SimpleIO*",
					      "Python handle to SimpleIO*");
    FIREWALL(0 != pIOHandler);
    pDB->IOHandler(pIOHandler);
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
} // CppSimpleDB_IOHandler
        
// version
// $Id: simpledb.cc,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
