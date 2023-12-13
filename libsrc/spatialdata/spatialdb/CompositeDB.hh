// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "SpatialDB.hh"

#include <string> // HASA std::string

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::CompositeDB : public SpatialDB { // class CompositeDB
    friend class TestCompositeDB; // unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    CompositeDB(void);

    /** Constructor with label.
     *
     * @param label Label of database
     */
    CompositeDB(const char* label);

    /// Default destructor.
    ~CompositeDB(void);

    /** Set database A.
     *
     * @param db Pointer to database.
     * @param names Array of names of values to use with database.
     * @param numNames Size of array of names.
     */
    void setDBA(SpatialDB* db,
                const char* const* names,
                const size_t numNames);

    /** Set database B.
     *
     * @param db Pointer to database.
     * @param names Array of names of values to use with database.
     * @param numNames Size of array of names.
     */
    void setDBB(SpatialDB* db,
                const char* const* names,
                const size_t numNames);

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

    // NOT IMPLEMENTED ////////////////////////////////////////////////////

    CompositeDB(const CompositeDB& data); ///< Not implemented
    const CompositeDB& operator=(const CompositeDB& data); ///< Not implemented

private:

    // PRIVATE STRUCTS ////////////////////////////////////////////////////

    struct DBInfo {
        double* query_buffer;
        size_t* query_indices;
        std::string* names_values;
        size_t query_size;
        size_t num_names;

        DBInfo(void) :
            query_buffer(NULL),
            query_indices(NULL),
            names_values(NULL),
            query_size(0),
            num_names(0) {}


        ~DBInfo(void) {
            delete[] query_buffer;query_buffer = NULL;
            delete[] query_indices;query_indices = NULL;
            delete[] names_values;names_values = NULL;
            query_size = 0;
            num_names = 0;
        } // destructor

    }; // DBInfo

private:

    // PRIVATE MEMBERS /////////////////////////////////////////////////////

    SpatialDB* _dbA; ///< Spatial database A
    SpatialDB* _dbB; ///< Spatial database B

    DBInfo* _infoA; ///< Information for database A
    DBInfo* _infoB; ///< Information for database B
}; // class CompositeDB

// End of file
