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

#if !defined(pyspatialdata_simpledb_h)
#define pyspatialdata_simpledb_h

// CppSimpleDB
/// Create C++ SimpleDB object and return pointer to it
extern "C"
PyObject* pyspatialdata_CppSimpleDB(PyObject*, PyObject*);
extern char pyspatialdata_CppSimpleDB__name__[];
extern char pyspatialdata_CppSimpleDB__doc__[];

/// Call SimpleDB::QueryType
extern "C"
PyObject* pyspatialdata_CppSimpleDB_QueryType(PyObject*, PyObject*);
extern char pyspatialdata_CppSimpleDB_QueryType__name__[];
extern char pyspatialdata_CppSimpleDB_QueryType__doc__[];

/// Call SimpleDB::IOHandler
extern "C"
PyObject* pyspatialdata_CppSimpleDB_IOHandler(PyObject*, PyObject*);
extern char pyspatialdata_CppSimpleDB_IOHandler__name__[];
extern char pyspatialdata_CppSimpleDB_IOHandler__doc__[];

#endif // pyspatialdata_simpledb_h

// version
// $Id: simpledb.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
