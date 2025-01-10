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

#include "spatialdbfwd.hh" // forward declarations

#include <string> // USES std::string

class spatialdata::spatialdb::SimpleDBData { // SimpleDBData
    friend class TestSimpleDBData; // unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor
    SimpleDBData(void);

    /// Default destructor
    ~SimpleDBData(void);

    /** Allocate data structues.
     *
     * @param numLocs Number of locations.
     * @param numValues Number of values.
     * @param spaceDim Spatial dimension of domain.
     * @param dataDim Spatial dimension of data distribution.
     */
    void allocate(const size_t numLocs,
                  const size_t numValues,
                  const size_t spaceDim,
                  const size_t dataDim);

    /** Set data values.
     *
     * @pre Must call allocate() before setData().
     *
     * @param values Array of data values [numLocs*numValues].
     * @param numLocs Number of locations.
     * @param numValues Number of values.
     */
    void setData(const double* values,
                 const size_t numLocs,
                 const size_t numValues);

    /** Set coordinates of locations.
     *
     * @pre Must call allocate() before setLocations().
     *
     * @param values Array of coordinates of locations [numLocs*spaceDim].
     * @param numLocs Number of locations.
     * @param spaceDim Spatial dimension of coordinates.
     */
    void setCoordinates(const double* values,
                        const size_t numLocs,
                        const size_t spaceDim);

    /** Set names of values.
     *
     * @pre Must call allocate() before setNames().
     *
     * @param names Array of names of values [numValues].
     * @param numValues Number of values.
     */
    void setNames(const char* const* values,
                  const size_t numValues);

    /** Set units of values.
     *
     * @pre Must call allocate() before setUnits().
     *
     * @param units Array of units of values [numValues].
     * @param numValues Number of values.
     */
    void setUnits(const char* const* values,
                  const size_t numValues);

    /** Get number of locations for data.
     *
     * @returns Number of locations.
     */
    size_t getNumLocs(void) const;

    /** Get number of values for data.
     *
     * @returns Number of values.
     */
    size_t getNumValues(void) const;

    /** Get spatial dimension of data distribution.
     *
     * @returns Spatial dimension.
     */
    size_t getDataDim(void) const;

    /** Get spatial dimension of locations.
     *
     * @returns Spatial dimension.
     */
    size_t getSpaceDim(void) const;

    /** Get coordinates of location in database.
     *
     * @param index Index of location in database
     * @returns Coordinates of location.
     */
    const double* getCoordinates(const size_t index) const;

    /** Get coordinates of location in database.
     *
     * @param index Index of location in database
     * @returns Coordinates of location.
     */
    double* getCoordinates(const size_t index);

    /** Get data values at location in database.
     *
     * @param index Index of location in database.
     * @returns Data values at location.
     */
    const double* getData(const size_t index) const;

    /** Get data values at location in database.
     *
     * @param index Index of location in database.
     * @returns Data values at location.
     */
    double* getData(const size_t index);

    /** Get name of value.
     *
     * @param index Index of value.
     * @returns Name of value.
     */
    const char* getName(const size_t index) const;

    /** Get units of value.
     *
     * @param index Index of value.
     * @returns Units of value.
     */
    const char* getUnits(const size_t index) const;

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    double* _data; ///< Array of data values.
    double* _coordinates; ///< Array of coordinates of locations.
    std::string* _names; ///< Names of data values.
    std::string* _units; ///< Units of values.
    size_t _numLocs; ///< Number of locations.
    size_t _numValues; ///< Number of values.
    size_t _dataDim; ///< Spatial dimension of data distribution.
    size_t _spaceDim; ///< Spatial dimension of coordinate locations.

}; // class SpatialDBData

#include "SimpleDBData.icc" // inline methods

// End of file
