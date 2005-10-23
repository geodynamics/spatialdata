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

#include "langtestspatialdb.h"

// the method table
struct PyMethodDef pytestlangspatialdb_methods[] = {

  // CTestQuery
  {pytestlangspatialdb_cTestQuery__name__,
   pytestlangspatialdb_cTestQuery,
   METH_VARARGS,
   pytestlangspatialdb_cTestQuery__doc__},

  // F77TestQuery
  {pytestlangspatialdb_f77TestQuery__name__,
   pytestlangspatialdb_f77TestQuery,
   METH_VARARGS,
   pytestlangspatialdb_f77TestQuery__doc__},

  // misc
  {pytestlangspatialdb_copyright__name__,
   pytestlangspatialdb_copyright,
   METH_VARARGS,
   pytestlangspatialdb_copyright__doc__},

  // Sentinel
  {0, 0}

}; // pytestlangspatialdb_methods

// version
// $Id: bindings.cc,v 1.1 2005/05/25 18:43:03 baagaard Exp $

// End of file
