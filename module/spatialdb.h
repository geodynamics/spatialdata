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

#if !defined(pyspatialdata_spatialdb_h)
#define pyspatialdata_spatialdb_h

/// Call SpatialDB::Open
extern "C"
PyObject* pyspatialdata_CppSpatialDB_Open(PyObject*, PyObject*);
extern char pyspatialdata_CppSpatialDB_Open__name__[];
extern char pyspatialdata_CppSpatialDB_Open__doc__[];

/// Call SpatialDB::Close
extern "C"
PyObject* pyspatialdata_CppSpatialDB_Close(PyObject*, PyObject*);
extern char pyspatialdata_CppSpatialDB_Close__name__[];
extern char pyspatialdata_CppSpatialDB_Close__doc__[];

/// Call SpatialDB::QueryVals
extern "C"
PyObject* pyspatialdata_CppSpatialDB_QueryVals(PyObject*, PyObject*);
extern char pyspatialdata_CppSpatialDB_QueryVals__name__[];
extern char pyspatialdata_CppSpatialDB_QueryVals__doc__[];

/// Call SpatialDB::Label
extern "C"
PyObject* pyspatialdata_CppSpatialDB_Label(PyObject*, PyObject*);
extern char pyspatialdata_CppSpatialDB_Label__name__[];
extern char pyspatialdata_CppSpatialDB_Label__doc__[];

#endif // pyspatialdata_spatialdb_h

// version
// $Id: spatialdb.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file
