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

/// Call SpatialDB::Open
extern "C"
PyObject* pyspatialdb_CppSpatialDB_Open(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_Open__name__[];
extern char pyspatialdb_CppSpatialDB_Open__doc__[];

/// Call SpatialDB::Close
extern "C"
PyObject* pyspatialdb_CppSpatialDB_Close(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_Close__name__[];
extern char pyspatialdb_CppSpatialDB_Close__doc__[];

/// Call SpatialDB::QueryVals
extern "C"
PyObject* pyspatialdb_CppSpatialDB_QueryVals(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_QueryVals__name__[];
extern char pyspatialdb_CppSpatialDB_QueryVals__doc__[];

/// Call SpatialDB::Label
extern "C"
PyObject* pyspatialdb_CppSpatialDB_Label(PyObject*, PyObject*);
extern char pyspatialdb_CppSpatialDB_Label__name__[];
extern char pyspatialdb_CppSpatialDB_Label__doc__[];

#endif // pyspatialdb_spatialdb_h

// version
// $Id: spatialdb.h,v 1.1 2005/05/25 18:42:59 baagaard Exp $

// End of file
