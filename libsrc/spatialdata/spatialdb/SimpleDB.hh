// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "SpatialDB.hh" // ISA Spatialdb

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::SimpleDB : public SpatialDB { // class SimpleDB
    friend class SimpleDBQuery; // helper
    friend class TestSimpleDB; // unit testing
    friend class TestSimpleDBQuery; // unit testing

public:

    // PUBLIC ENUM ////////////////////////////////////////////////////////

    /** Topology of spatial data */
    enum TopoEnum {
        POINT=0,
        LINE=1,
        AREA=2,
        VOLUME=3
    };

    /** Type of query */
    enum QueryEnum {
        NEAREST=0,
        LINEAR=1
    };

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    SimpleDB(void);

    /** Constructor with label.
     *
     * @param label Label of database
     */
    SimpleDB(const char* label);

    /// Default destructor.
    ~SimpleDB(void);

    /** Set query type.
     *
     * @pre Must call Open() before QueryType()
     *
     * @param queryType Set type of query
     */
    void setQueryType(const SimpleDB::QueryEnum queryType);

    /** Set the I/O handler.
     *
     * @param iohandler
     */
    void setIOHandler(const SimpleIO* iohandler);

    /// Open the database and prepare for querying.
    void open(void);

    /// Close the database.
    void close(void);

    /** Get names of values in spatial database.
     *
     * @param[out] valueNames Array of names of values.
     * @param[out] numValues Size of array.
     */
    void getNamesDBValues(const char*** valueNames,
                          size_t* numValues) const;

    /** Set values to be returned by queries.
     *
     * @pre Must call open() before setQueryValues()
     *
     * @param names Names of values to be returned in queries
     * @param numVals Number of values to be returned in queries
     */
    void setQueryValues(const char* const* names,
                        const size_t numVals);

    /** Query the database.
     *
     * @pre Must call open() before query()
     *
     * @param vals Array for computed values (output from query), vals
     *   must be allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param coords Coordinates of point for query
     * @param numDims Number of dimensions for coordinates
     * @param pCSQuery Coordinate system of coordinates
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate
     *   so values set to 0)
     */
    int query(double* vals,
              const size_t numVals,
              const double* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* pCSQuery);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    SimpleDB(const SimpleDB& data); ///< Not implemented
    const SimpleDB& operator=(const SimpleDB& data); ///< Not implemented

private:

    // PRIVATE MEMBERS /////////////////////////////////////////////////////

    SimpleDBData* _data; ///< Pointer to data
    SimpleIO* _iohandler; ///< I/O handler
    SimpleDBQuery* _query; ///< Query handler
    spatialdata::geocoords::CoordSys* _cs; ///< Coordinate system

}; // class SimpleDB

// End of file
