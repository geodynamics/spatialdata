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

/// cTestQuery
extern "C"
PyObject* pytestlangspatialdb_cTestQuery(PyObject*, PyObject*);
extern char pytestlangspatialdb_cTestQuery__name__[];
extern char pytestlangspatialdb_cTestQuery__doc__[];

/// f77TestQuery
extern "C"
PyObject* pytestlangspatialdb_f77TestQuery(PyObject*, PyObject*);
extern char pytestlangspatialdb_f77TestQuery__name__[];
extern char pytestlangspatialdb_f77TestQuery__doc__[];

#endif // pytestlangspatialdb_ctestspatialdb_h

// version
// $Id: langtestspatialdb.h,v 1.1 2005/05/25 18:43:03 baagaard Exp $

// End of file
