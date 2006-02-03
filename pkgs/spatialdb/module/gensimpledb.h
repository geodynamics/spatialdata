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

/** @file module/gensimpledb.h
 *
 * @brief Bindings for Gensimpledb
 */

#if !defined(pyspatialdb_gensimpledb_h)
#define pyspatialdb_gensimpledb_h

// CppGenSimpleDB
/// Create C++ SimpleDB::DataStruct and return pointer to it
extern "C"
PyObject* pyspatialdb_CppGenSimpleDB_create(PyObject*, PyObject*);
extern char pyspatialdb_CppGenSimpleDB_create__name__[];
extern char pyspatialdb_CppGenSimpleDB_create__doc__[];

/// Create C++ array and fill it with zeros
extern "C"
PyObject* pyspatialdb_CppGenSimpleDB_initializeValue(PyObject*, PyObject*);
extern char pyspatialdb_CppGenSimpleDB_initializeValue__name__[];
extern char pyspatialdb_CppGenSimpleDB_initializeValue__doc__[];

/// Set value in SimpleDB::DataStruct
extern "C"
PyObject* pyspatialdb_CppGenSimpleDB_setValue(PyObject*, PyObject*);
extern char pyspatialdb_CppGenSimpleDB_setValue__name__[];
extern char pyspatialdb_CppGenSimpleDB_setValue__doc__[];

/// Apply filter to value
extern "C"
PyObject* pyspatialdb_CppGenSimpleDB_applyFilter(PyObject*, PyObject*);
extern char pyspatialdb_CppGenSimpleDB_applyFilter__name__[];
extern char pyspatialdb_CppGenSimpleDB_applyFilter__doc__[];

#endif // pyspatialdb_gensimpledb_h

// version
// $Id$

// End of file
