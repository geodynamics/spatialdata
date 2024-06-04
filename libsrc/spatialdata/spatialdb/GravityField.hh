// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "SpatialDB.hh"

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::GravityField : public SpatialDB {
    friend class TestGravityField; // unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    GravityField(void);

    /// Default destructor.
    ~GravityField(void);

    /** Set direction of gravitational body force. Used only with
     * Cartesian coordinate system.
     *
     * @param x X component of direction
     * @param y Y component of direction
     * @param z Z component of direction
     */
    void setGravityDir(const double x,
                       const double y,
                       const double z);

    /** Set gravitational acceleration.
     *
     * @param acceleration Gravitational acceleration.
     */
    void setGravityAcc(const double acceleration);

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
     * Valid values for use in names are {'x', 'y', 'z'}.
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
     * @param cs Coordinate system of coordinates
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate
     *   so values set to 0)
     */
    int query(double* vals,
              const size_t numVals,
              const double* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* cs);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    GravityField(const GravityField& data); ///< Not implemented
    const GravityField& operator=(const GravityField& data); ///< Not implemented

private:

    // PRIVATE MEMBERS /////////////////////////////////////////////////////

    double _gravityDir[3]; ///< Direction of gravitational body force.
    double _acceleration; ///< Acceleration due to gravity.
    size_t _queryValues[3]; ///< Indices of values to be returned in queries.
    size_t _querySize; ///< Number of values requested to be returned in queries.
}; // class GravityField

// End of file
