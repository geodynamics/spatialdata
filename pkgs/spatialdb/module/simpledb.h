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

/** @file module/simpledb.h
 *
 * @brief Bindings for SimpleDB
 */

#if !defined(pyspatialdb_simpledb_h)
#define pyspatialdb_simpledb_h

// CppSimpleDB
/// Create C++ SimpleDB object and return pointer to it
extern "C"
PyObject* pyspatialdb_CppSimpleDB(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleDB__name__[];
extern char pyspatialdb_CppSimpleDB__doc__[];

/// Call SimpleDB::QueryType
extern "C"
PyObject* pyspatialdb_CppSimpleDB_QueryType(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleDB_QueryType__name__[];
extern char pyspatialdb_CppSimpleDB_QueryType__doc__[];

/// Call SimpleDB::IOHandler
extern "C"
PyObject* pyspatialdb_CppSimpleDB_IOHandler(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleDB_IOHandler__name__[];
extern char pyspatialdb_CppSimpleDB_IOHandler__doc__[];

#endif // pyspatialdb_simpledb_h

// version
// $Id: simpledb.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
