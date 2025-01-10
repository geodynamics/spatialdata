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

#include "SpatialDB.hh"

#include "spatialdata/muparser/muparserfwd.hh" // HOLDSA mu::parser

#include <string> // HASA std::string

/// C++ manager for analytic spatial database.
class spatialdata::spatialdb::AnalyticDB : public SpatialDB {
    friend class TestAnalyticDB; // unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor.
    AnalyticDB(void);

    /** Constructor with label.
     *
     * @param label Label of database
     */
    AnalyticDB(const char* label);

    /// Default destructor.
    ~AnalyticDB(void);

    /// Clear values from database.Default destructor.
    void clear(void);

    /** Set expressions in database.
     *
     * @param names Array of names of expressions in database.
     * @param units Array of units for expressions in database.
     * @param expressions Array of expressions in database.
     * @param numValues Number of expressions in database.
     */
    void setData(const char* const* names,
                 const char* const* units,
                 const char* const* expressions,
                 const size_t numValues);

    /** Set coordinate system associated with user functions.
     *
     * @param cs Coordinate system.
     */
    void setCoordSys(const spatialdata::geocoords::CoordSys& cs);

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
     * @param numValues Number of values to be returned in queries
     */
    void setQueryValues(const char* const* names,
                        const size_t numValues);

    /** Query the database.
     *
     * @pre Must call open() before query()
     *
     * @param vals Array for computed values (output from query), vals
     *   must be allocated BEFORE calling query().
     * @param numValues Number of values expected (size of pVals array)
     * @param coords Coordinates of point for query
     * @param numDims Number of dimensions for coordinates
     * @param csQuery Coordinate system of coordinates
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate
     *   so values set to 0)
     */
    int query(double* vals,
              const size_t numValues,
              const double* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* csQuery);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    AnalyticDB(const AnalyticDB& data); ///< Not implemented
    const AnalyticDB& operator=(const AnalyticDB& data); ///< Not implemented

private:

    // PRIVATE MEMBERS /////////////////////////////////////////////////////

    mu::value_type _expVars[3]; ///< Storage for default expression variables
    std::string* _names; ///< Names of values in database
    double* _scales; ///< Scales to convert expressions to SI units.
    std::string* _expressions; ///< Expressions in database
    mu::Parser* _parsers; ///< Handle for muParser context
    geocoords::CoordSys* _cs; ///< Coordinate system
    geocoords::Converter* _converter; /// Convert query points to local coordinate system.
    size_t* _queryValues; ///< Indices of values to be returned in queries.
    size_t _numValues; ///< Number of valuess in database
    size_t _querySize; ///< Number of values requested to be returned in queries.

}; // class AnalyticDB

#include "AnalyticDB.icc"

// End of file
