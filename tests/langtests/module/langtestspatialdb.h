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

/** @file tests/langtests/module/langtestspatialdb.h
 */

#if !defined(pytestlangspatialdb_ctestspatialdb_h)
#define pytestlangspatialdb_ctestspatialdb_h

/// CTestQuery
extern "C"
PyObject* pytestlangspatialdb_CTestQuery(PyObject*, PyObject*);
extern char pytestlangspatialdb_CTestQuery__name__[];
extern char pytestlangspatialdb_CTestQuery__doc__[];

/// F77TestQuery
extern "C"
PyObject* pytestlangspatialdb_F77TestQuery(PyObject*, PyObject*);
extern char pytestlangspatialdb_F77TestQuery__name__[];
extern char pytestlangspatialdb_F77TestQuery__doc__[];

#endif // pytestlangspatialdb_ctestspatialdb_h

// version
// $Id: langtestspatialdb.h,v 1.1 2005/03/19 00:46:57 baagaard Exp $

// End of file
