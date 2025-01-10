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

#include "spatialdbfwd.hh"
#include "spatialdata/geocoords/geocoordsfwd.hh"

#include <string> // USES std::string

/// C++ manager for spatial database.
class spatialdata::spatialdb::SpatialDB {
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    SpatialDB(void);

    /** Constructor with label.
     *
     * @param label Label for database
     */
    SpatialDB(const char* label);

    /// Default destructor.
    virtual ~SpatialDB(void);

    /** Set description of spatial database.
     *
     * @param description Description of database
     */
    void setDescription(const char* description);

    /** Get description of spatial database.
     *
     * @returns Description of database
     */
    const char* getDescription(void) const;

    /// Open the database and prepare for querying.
    virtual
    void open(void) = 0;

    /// Close the database.
    virtual
    void close(void) = 0;

    /** Get names of values in spatial database.
     *
     * @param[out] valueNames Array of names of values.
     * @param[out] numValues Size of array.
     */
    virtual
    void getNamesDBValues(const char*** valueNames,
                          size_t* numValues) const = 0;

    /** Set values to be returned by queries.
     *
     * @pre Must call open() before setQueryValues()
     *
     * @param names Names of values to be returned in queries
     * @param numVals Number of values to be returned in queries
     */
    virtual
    void setQueryValues(const char* const* names,
                        const size_t numVals) = 0;

    /** Query the database.
     *
     * @note vals should be preallocated to accommodate numVals values.
     *
     * @pre Must call open() before query().
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param coords Coordinates of point for query [numDims].
     * @param numDims Number of dimensions for coordinates.
     * @param csQuery Coordinate system of coordinates.
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate)
     */
    virtual
    int query(double* vals,
              const size_t numVals,
              const double* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* csQuery) = 0;

    /** Query the database.
     *
     * @note vals should be preallocated to accommodate numVals values.
     *
     * @pre Must call open() before query().
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param coords Coordinates of point for query [numDims].
     * @param numDims Number of dimensions for coordinates.
     * @param csQuery Coordinate system of coordinates.
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate)
     */
    int query(float* vals,
              const size_t numVals,
              const float* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* csQuery);

    /** Perform multiple queries of the database.
     *
     * @note vals should be preallocated to accommodate numVals values
     * at numLocs locations.
     *
     * @note err should be preallocated to accommodate numLocs values.
     *
     * @pre Must call open() before query().
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query() [numLocs*numVals].
     * @param numLocsV Number of locations.
     * @param numValsV Number of values expected.
     * @param err Array for error flag values (output from query), must be
     *   allocated BEFORE calling query() [numLocs].
     * @param numLocsE Number of locations.
     * @param coords Coordinates of point for query [numLocs*numDims].
     * @param numLocsC Number of locations.
     * @param numDimsC Number of dimensions for coordinates.
     * @param csQuery Coordinate system of coordinates.
     */
    void multiquery(double* vals,
                    const size_t numLocsV,
                    const size_t numValsV,
                    int* err,
                    const size_t numLocsE,
                    const double* coords,
                    const size_t numLocsC,
                    const size_t numDimsC,
                    const spatialdata::geocoords::CoordSys* csQuery);

    /** Perform multiple queries of the database.
     *
     * @note vals should be preallocated to accommodate numVals values
     * at numLocs locations.
     *
     * @note err should be preallocated to accommodate numLocs values.
     *
     * @pre Must call open() before query().
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query() [numLocs*numVals].
     * @param numLocsV Number of locations.
     * @param numValsV Number of values expected.
     * @param err Array for error flag values (output from query), must be
     *   allocated BEFORE calling query() [numLocs].
     * @param numLocsE Number of locations.
     * @param coords Coordinates of point for query [numLocs*numDims].
     * @param numLocsC Number of locations.
     * @param numDimsC Number of dimensions for coordinates.
     * @param csQuery Coordinate system of coordinates.
     */
    void multiquery(float* vals,
                    const size_t numLocsV,
                    const size_t numValsV,
                    int* err,
                    const size_t numLocsE,
                    const float* coords,
                    const size_t numLocsC,
                    const size_t numDimsC,
                    const spatialdata::geocoords::CoordSys* csQuery);

    // PROTECTED METHODS //////////////////////////////////////////////////
protected:

    /** Convert values to SI units.
     *
     * @param data Array of data.
     * @param units Units for values.
     * @param numLocs Number of locations.
     * @param numVals Number of values per location.
     */
    static
    void _convertToSI(double* vals,
                      std::string* units,
                      const size_t numLocs,
                      const size_t numVals);

    // PRIVATE METHODS ////////////////////////////////////////////////////
private:

    SpatialDB(const SpatialDB& data); ///< Not implemented
    const SpatialDB& operator=(const SpatialDB& data); ///< Not implemented

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    std::string _description; ///< Description of spatial database.

}; // class SpatialDB

#include "SpatialDB.icc" // inline methods

// End of file
