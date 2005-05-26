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
struct PyMethodDef pyspatialdb_methods[] = {

  // SpatialDB
  {pyspatialdb_CppSpatialDB_Open__name__,
   pyspatialdb_CppSpatialDB_Open,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_Open__doc__},

  {pyspatialdb_CppSpatialDB_Close__name__,
   pyspatialdb_CppSpatialDB_Close,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_Close__doc__},

  {pyspatialdb_CppSpatialDB_QueryVals__name__,
   pyspatialdb_CppSpatialDB_QueryVals,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_QueryVals__doc__},

  {pyspatialdb_CppSpatialDB_Label__name__,
   pyspatialdb_CppSpatialDB_Label,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_Label__doc__},

  // SimpleDB
  {pyspatialdb_CppSimpleDB__name__,
   pyspatialdb_CppSimpleDB,
   METH_VARARGS,
   pyspatialdb_CppSimpleDB__doc__},
  
  {pyspatialdb_CppSimpleDB_QueryType__name__,
   pyspatialdb_CppSimpleDB_QueryType,
   METH_VARARGS,
   pyspatialdb_CppSimpleDB_QueryType__doc__},

  {pyspatialdb_CppSimpleDB_IOHandler__name__,
   pyspatialdb_CppSimpleDB_IOHandler,
   METH_VARARGS,
   pyspatialdb_CppSimpleDB_IOHandler__doc__},

  // SimpleIO
  {pyspatialdb_CppSimpleIO_Filename__name__,
   pyspatialdb_CppSimpleIO_Filename,
   METH_VARARGS,
   pyspatialdb_CppSimpleIO_Filename__doc__},

  // SimpleIOAscii
  {pyspatialdb_CppSimpleIOAscii__name__,
   pyspatialdb_CppSimpleIOAscii,
   METH_VARARGS,
   pyspatialdb_CppSimpleIOAscii__doc__},

  // misc
  {pyspatialdb_copyright__name__,
   pyspatialdb_copyright,
   METH_VARARGS,
   pyspatialdb_copyright__doc__},

  // Sentinel
  {0, 0}

}; // pyspatialdb_methods

// version
// $Id: bindings.cc,v 1.1 2005/05/25 18:42:58 baagaard Exp $

// End of file
