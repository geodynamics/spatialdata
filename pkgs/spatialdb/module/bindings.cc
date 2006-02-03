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
#include "gensimpledb.h"  // SimpleIOAscii bindings

// the method table
struct PyMethodDef pyspatialdb_methods[] = {

  // SpatialDB
  {pyspatialdb_CppSpatialDB_open__name__,
   pyspatialdb_CppSpatialDB_open,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_open__doc__},

  {pyspatialdb_CppSpatialDB_close__name__,
   pyspatialdb_CppSpatialDB_close,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_close__doc__},

  {pyspatialdb_CppSpatialDB_queryVals__name__,
   pyspatialdb_CppSpatialDB_queryVals,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_queryVals__doc__},

  {pyspatialdb_CppSpatialDB_label__name__,
   pyspatialdb_CppSpatialDB_label,
   METH_VARARGS,
   pyspatialdb_CppSpatialDB_label__doc__},

  // SimpleDB
  {pyspatialdb_CppSimpleDB__name__,
   pyspatialdb_CppSimpleDB,
   METH_VARARGS,
   pyspatialdb_CppSimpleDB__doc__},
  
  {pyspatialdb_CppSimpleDB_queryType__name__,
   pyspatialdb_CppSimpleDB_queryType,
   METH_VARARGS,
   pyspatialdb_CppSimpleDB_queryType__doc__},

  {pyspatialdb_CppSimpleDB_ioHandler__name__,
   pyspatialdb_CppSimpleDB_ioHandler,
   METH_VARARGS,
   pyspatialdb_CppSimpleDB_ioHandler__doc__},

  // SimpleIO
  {pyspatialdb_CppSimpleIO_filename__name__,
   pyspatialdb_CppSimpleIO_filename,
   METH_VARARGS,
   pyspatialdb_CppSimpleIO_filename__doc__},

  // SimpleIOAscii
  {pyspatialdb_CppSimpleIOAscii__name__,
   pyspatialdb_CppSimpleIOAscii,
   METH_VARARGS,
   pyspatialdb_CppSimpleIOAscii__doc__},

  {pyspatialdb_CppSimpleIOAscii_write__name__,
   pyspatialdb_CppSimpleIOAscii_write,
   METH_VARARGS,
   pyspatialdb_CppSimpleIOAscii_write__doc__},

  // GenSimpleDB
  {pyspatialdb_CppGenSimpleDB_create__name__,
   pyspatialdb_CppGenSimpleDB_create,
   METH_VARARGS,
   pyspatialdb_CppGenSimpleDB_create__doc__},

  {pyspatialdb_CppGenSimpleDB_initializeValue__name__,
   pyspatialdb_CppGenSimpleDB_initializeValue,
   METH_VARARGS,
   pyspatialdb_CppGenSimpleDB_initializeValue__doc__},

  {pyspatialdb_CppGenSimpleDB_setValue__name__,
   pyspatialdb_CppGenSimpleDB_setValue,
   METH_VARARGS,
   pyspatialdb_CppGenSimpleDB_setValue__doc__},

  {pyspatialdb_CppGenSimpleDB_applyFilter__name__,
   pyspatialdb_CppGenSimpleDB_applyFilter,
   METH_VARARGS,
   pyspatialdb_CppGenSimpleDB_applyFilter__doc__},

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
