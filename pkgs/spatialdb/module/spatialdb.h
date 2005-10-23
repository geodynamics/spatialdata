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

/** @file module/spatialdb.h
 *
 * @brief Bindings for SpatialDB
 */

#if !defined(pyspatialdb_spatialdb_h)
#define pyspatialdb_spatialdb_h

/// Call SpatialDB::open
extern "C"
PyObject* pyspatialdb_CppSpatialDB_open(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_open__name__[];
extern char pyspatialdb_CppSpatialDB_open__doc__[];

/// Call SpatialDB::close
extern "C"
PyObject* pyspatialdb_CppSpatialDB_close(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_close__name__[];
extern char pyspatialdb_CppSpatialDB_close__doc__[];

/// Call SpatialDB::queryVals
extern "C"
PyObject* pyspatialdb_CppSpatialDB_queryVals(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_queryVals__name__[];
extern char pyspatialdb_CppSpatialDB_queryVals__doc__[];

/// Call SpatialDB::label
extern "C"
PyObject* pyspatialdb_CppSpatialDB_label(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_label__name__[];
extern char pyspatialdb_CppSpatialDB_label__doc__[];

#endif // pyspatialdb_spatialdb_h

// version
// $Id: spatialdb.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
