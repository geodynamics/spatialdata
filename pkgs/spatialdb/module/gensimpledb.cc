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

#include "gensimpledb.h"

#include "spatialdata/spatialdb/SpatialDB.h"
#include "spatialdata/spatialdb/SimpleDB.h"
#include "pkgs/spatialdb/lib/SimpleDBTypes.h"

#include <stdexcept> // USES std::exception
#include <sstream> // USES std::ostringstream

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#include "pythiautil/bindings.h" // USES BindingsTUtil

// ----------------------------------------------------------------------
// CppGenSimpleDB_tearDown
void
pyspatialdb_CppGenSimpleDB_tearDown(void* pObj)
{ // CppGenSimpleDB_tearDown
  spatialdata::spatialdb::SimpleDB::DataStruct* pData = 
    (spatialdata::spatialdb::SimpleDB::DataStruct*) pObj;
  if (0 != pData) {
    delete[] pData->data;
    delete[] pData->valNames;
    delete[] pData->valUnits;
  } // if
  delete pData;
} // CppGenSimpleDB_tearDown

// ----------------------------------------------------------------------
// CppGenSimpleDB_create
char pyspatialdb_CppGenSimpleDB_create__doc__[] = "";
char pyspatialdb_CppGenSimpleDB_create__name__[] = "CppGenSimpleDB_create";

static char pyspatialdb_CppGenSimpleDB_create_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppGenSimpleDB_create(PyObject*, PyObject* args)
{ // CppGenSimpleDB_create
  PyObject* pyCoords = 0;
  int locCount = 0;
  int locDim = 0;
  int numValues = 0;
  PyObject* pyTopology = 0;
  int ok = PyArg_ParseTuple(args,
			    "OiiiO:CppGenSimpleDB_create", 
			    &pyCoords, &locCount, &locDim, &numValues,
			    &pyTopology);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  spatialdata::spatialdb::SimpleDB::DataStruct* pData = 0;
  try {
    pData = new spatialdata::spatialdb::SimpleDB::DataStruct;
    const int totalNumValues = locDim + numValues;
    const int size = locCount * totalNumValues;
    if (size > 0) {
      pData->data = new double[size];
      std::fill(pData->data, pData->data+size, 0.0);
      pData->numLocs = locCount;
      pData->numVals = numValues;
      pData->valNames = (numValues > 0) ? new std::string[numValues] : 0;
      pData->valUnits = (numValues > 0) ? new std::string[numValues] : 0;
      const char* topologyString = PyString_AsString(pyTopology);
      if (0 == strcasecmp("point", topologyString))
	pData->topology = spatialdata::spatialdb::SimpleDB::POINT;
      else if (0 == strcasecmp("line", topologyString))
	pData->topology = spatialdata::spatialdb::SimpleDB::LINE;
      else if (0 == strcasecmp("area", topologyString))
	pData->topology = spatialdata::spatialdb::SimpleDB::AREA;
      else if (0 == strcasecmp("volume", topologyString))
	pData->topology = spatialdata::spatialdb::SimpleDB::VOLUME;
      else {
	std::ostringstream msg;
	msg << "Could not parse topology '" << topologyString
	    << "' into a known topology type.";
	throw std::runtime_error(msg.str().c_str());
      } // else
    } else {
      pData->data = 0;
      pData->valNames = 0;
      pData->valUnits = 0;
      pData->numLocs = 0;
      pData->numVals = 0;
      pData->topology = spatialdata::spatialdb::SimpleDB::POINT;
    } // else
    double* pCoords =
      pythiautil::BindingsTUtil<double*>::GetCObj(pyCoords, 
						  "double*",
						  "Python handle to double*");
    for (int iLoc=0; iLoc < locCount; ++iLoc) {
      double* pDataCoords = 
	spatialdata::spatialdb::SimpleDBTypes::dataCoords(*pData, iLoc);
      for (int iDim=0; iDim < locDim; ++iDim)
	pDataCoords[iDim] = pCoords[locDim*iLoc+iDim];
    } // for
  } // try
  catch (const std::exception& err) {
    PyErr_SetString(PyExc_RuntimeError, const_cast<char*>(err.what()));
    return 0;
  } catch (...) {
    PyErr_SetString(PyExc_RuntimeError, "Caught unknown C++ exception.");
    return 0;
  } // catch

  return PyCObject_FromVoidPtr((void*) pData, 
			       pyspatialdb_CppGenSimpleDB_tearDown);
} // CppGenSimpleDB_create
        
// ----------------------------------------------------------------------
// CppGenSimpleDB_initializeValue
char pyspatialdb_CppGenSimpleDB_initializeValue__doc__[] = "";
char pyspatialdb_CppGenSimpleDB_initializeValue__name__[] = "CppGenSimpleDB_initializeValue";

static char pyspatialdb_CppGenSimpleDB_initializeValue_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppGenSimpleDB_initializeValue(PyObject*, PyObject* args)
{ // CppGenSimpleDB_initializeValue
  int count = 0;
  int ok = PyArg_ParseTuple(args,
			    "i:CppGenSimpleDB_initializeValue", &count);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  double* pValue = (count > 0) ? new double[count] : 0;
  std::fill(pValue, pValue+count, 0.0);

  return PyCObject_FromVoidPtr((void*) pValue, 
			  pythiautil::BindingsTUtil<double>::DeleteArrayPtr);
} // CppGenSimpleDB_initializeValue
        
// ----------------------------------------------------------------------
// CppGenSimpleDB_setValue
char pyspatialdb_CppGenSimpleDB_setValue__doc__[] = "";
char pyspatialdb_CppGenSimpleDB_setValue__name__[] = "CppGenSimpleDB_setValue";

static char pyspatialdb_CppGenSimpleDB_ioHandler_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppGenSimpleDB_setValue(PyObject*, PyObject* args)
{ // CppGenSimpleDB_setValue
  PyObject* pyData = 0;
  int dataIndex = 0;
  PyObject* pyValue = 0;
  int locCount = 0;
  PyObject* pyName = 0;
  PyObject* pyUnits = 0;
  int ok = PyArg_ParseTuple(args,
			    "OiOiOO:CppGenSimpleDB_setValue", 
			    &pyData, &dataIndex, 
			    &pyValue, &locCount, &pyName, &pyUnits);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    spatialdata::spatialdb::SimpleDB::DataStruct* pData = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SimpleDB::DataStruct*>::GetCObj(pyData, 
							     "DataStruct*",
					      "Python handle to DataStruct*");
    FIREWALL(0 != pData);
    double* pValue = 
      pythiautil::BindingsTUtil<double*>::GetCObj(pyValue, 
						  "double*",
						  "Python handle to double*");
    FIREWALL(0 != pValue);
    for (int iLoc=0; iLoc < locCount; ++iLoc) {
      double* pDataVals = 
	spatialdata::spatialdb::SimpleDBTypes::dataVals(*pData, iLoc);
      pDataVals[dataIndex] = pValue[iLoc];
    } // for
    pData->valNames[dataIndex] = PyString_AsString(pyName);
    pData->valUnits[dataIndex] = PyString_AsString(pyUnits);
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
} // CppGenSimpleDB_setValue
        
// ----------------------------------------------------------------------
// CppGenSimpleDB_applyFilter
char pyspatialdb_CppGenSimpleDB_applyFilter__doc__[] = "";
char pyspatialdb_CppGenSimpleDB_applyFilter__name__[] = "CppGenSimpleDB_applyFilter";

static char pyspatialdb_CppGenSimpleDB_applyFilter_note[] = 
  "spatialdata python module: U.S. Geological Survey";

PyObject*
pyspatialdb_CppGenSimpleDB_applyFilter(PyObject*, PyObject* args)
{ // CppGenSimpleDB_applyFilter
  PyObject* pyValue = 0;
  int valueCount = 0;
  PyObject* pyLocs = 0;
  int locCount = 0;
  PyObject* pyCS = 0;
  PyObject* pyDB = 0;
  PyObject* pyOperand = 0;
  int ok = PyArg_ParseTuple(args,
			    "OiOiOOO:CppGenSimpleDB_applyFilter", 
			    &pyValue, &valueCount, 
			    &pyLocs, &locCount,
			    &pyCS, &pyDB, &pyOperand);
  if (!ok) {
    PyErr_SetString(PyExc_TypeError,
		    "C++ bindings error: "
		    "Could not parse tuple for arguments.");
    return 0;
  } // if

  try {
    double* pValue = 
      pythiautil::BindingsTUtil<double*>::GetCObj(pyValue, 
						  "double*",
						  "Python handle to double*");
    FIREWALL(0 != pValue);

    double* pLocs = 
      pythiautil::BindingsTUtil<double*>::GetCObj(pyLocs, 
						  "double*",
						  "Python handle to double*");
    FIREWALL(0 != pLocs);

    spatialdata::spatialdb::SpatialDB* pDB = 
      pythiautil::BindingsTUtil<spatialdata::spatialdb::SpatialDB*>::GetCObj(pyDB, 
							       "SpatialDB*",
					      "Python handle to SpatialDB*");
    FIREWALL(0 != pDB);

    spatialdata::geocoords::CoordSys* pCS = 
      pythiautil::BindingsTUtil<spatialdata::geocoords::CoordSys*>::GetCObj(pyCS, 
							       "CoordSys*",
					      "Python handle to CoordSys*");
    FIREWALL(0 != pCS);

    double* pFilterData = (locCount > 0) ? new double[locCount] : 0;
    double* pVal = new double;
    for (int iLoc=0, index=0; iLoc < locCount; ++iLoc, index += 3) {
      pDB->query(&pVal, 1, 
		 pLocs[index], pLocs[index+1], pLocs[index+2], pCS);
      pFilterData[iLoc] = *pVal;
    } // for
    delete pVal; pVal = 0;

    const char* operand = PyString_AsString(pyOperand);
    if (0 == strcasecmp("add", operand))
      for (int iLoc=0; iLoc < locCount; ++iLoc)
	pValue[iLoc] += pFilterData[iLoc];
    else if (0 == strcasecmp("subtract", operand))
      for (int iLoc=0; iLoc < locCount; ++iLoc)
	pValue[iLoc] -= pFilterData[iLoc];
    else if (0 == strcasecmp("multiply", operand))
      for (int iLoc=0; iLoc < locCount; ++iLoc)
	pValue[iLoc] *= pFilterData[iLoc];
    else if (0 == strcasecmp("divide", operand))
      for (int iLoc=0; iLoc < locCount; ++iLoc)
	pValue[iLoc] /= pFilterData[iLoc];
    else {
      std::ostringstream msg;
      msg << "Unknown filter operand '" << operand << "'.";
      throw std::runtime_error(msg.str().c_str());
    } // else
    delete[] pFilterData; pFilterData = 0;
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
} // CppGenSimpleDB_applyFilter
        
// version
// $Id$

// End of file
