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

#include "misc.h" // misc methods

#include "spatialdb.h"  // SpatialDB bindings
#include "simpledb.h"  // SimpleDB bindings
#include "simpleio.h"  // SimpleIO bindings
#include "simpleioascii.h"  // SimpleIOAscii bindings

// the method table
struct PyMethodDef pyspatialdata_methods[] = {

  // SpatialDB
  {pyspatialdata_CppSpatialDB_Open__name__,
   pyspatialdata_CppSpatialDB_Open,
   METH_VARARGS,
   pyspatialdata_CppSpatialDB_Open__doc__},

  {pyspatialdata_CppSpatialDB_Close__name__,
   pyspatialdata_CppSpatialDB_Close,
   METH_VARARGS,
   pyspatialdata_CppSpatialDB_Close__doc__},

  {pyspatialdata_CppSpatialDB_QueryVals__name__,
   pyspatialdata_CppSpatialDB_QueryVals,
   METH_VARARGS,
   pyspatialdata_CppSpatialDB_QueryVals__doc__},

  {pyspatialdata_CppSpatialDB_Label__name__,
   pyspatialdata_CppSpatialDB_Label,
   METH_VARARGS,
   pyspatialdata_CppSpatialDB_Label__doc__},

  // SimpleDB
  {pyspatialdata_CppSimpleDB__name__,
   pyspatialdata_CppSimpleDB,
   METH_VARARGS,
   pyspatialdata_CppSimpleDB__doc__},
  
  {pyspatialdata_CppSimpleDB_QueryType__name__,
   pyspatialdata_CppSimpleDB_QueryType,
   METH_VARARGS,
   pyspatialdata_CppSimpleDB_QueryType__doc__},

  {pyspatialdata_CppSimpleDB_IOHandler__name__,
   pyspatialdata_CppSimpleDB_IOHandler,
   METH_VARARGS,
   pyspatialdata_CppSimpleDB_IOHandler__doc__},

  // SimpleIO
  {pyspatialdata_CppSimpleIO_Filename__name__,
   pyspatialdata_CppSimpleIO_Filename,
   METH_VARARGS,
   pyspatialdata_CppSimpleIO_Filename__doc__},

  // SimpleIOAscii
  {pyspatialdata_CppSimpleIOAscii__name__,
   pyspatialdata_CppSimpleIOAscii,
   METH_VARARGS,
   pyspatialdata_CppSimpleIOAscii__doc__},

  // misc
  {pyspatialdata_copyright__name__,
   pyspatialdata_copyright,
   METH_VARARGS,
   pyspatialdata_copyright__doc__},

  // Sentinel
  {0, 0}

}; // pyspatialdata_methods

// version
// $Id: bindings.cc,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
