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
  {pytestlangspatialdb_CTestQuery__name__,
   pytestlangspatialdb_CTestQuery,
   METH_VARARGS,
   pytestlangspatialdb_CTestQuery__doc__},

  // F77TestQuery
  {pytestlangspatialdb_F77TestQuery__name__,
   pytestlangspatialdb_F77TestQuery,
   METH_VARARGS,
   pytestlangspatialdb_F77TestQuery__doc__},

  // misc
  {pytestlangspatialdb_copyright__name__,
   pytestlangspatialdb_copyright,
   METH_VARARGS,
   pytestlangspatialdb_copyright__doc__},

  // Sentinel
  {0, 0}

}; // pytestlangspatialdb_methods

// version
// $Id: bindings.cc,v 1.1 2005/03/19 00:46:57 baagaard Exp $

// End of file
