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

/// Call SimpleDB::queryType
extern "C"
PyObject* pyspatialdb_CppSimpleDB_queryType(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleDB_queryType__name__[];
extern char pyspatialdb_CppSimpleDB_queryType__doc__[];

/// Call SimpleDB::ioHandler
extern "C"
PyObject* pyspatialdb_CppSimpleDB_ioHandler(PyObject*, PyObject*);
extern char pyspatialdb_CppSimpleDB_ioHandler__name__[];
extern char pyspatialdb_CppSimpleDB_ioHandler__doc__[];

#endif // pyspatialdb_simpledb_h

// version
// $Id: simpledb.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
