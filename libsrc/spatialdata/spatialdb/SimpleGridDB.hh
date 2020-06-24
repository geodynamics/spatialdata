// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SimpleGridDB.hh
 *
 * @brief C++ object for performing querying of data on a nonuniform
 * (or uniform) grid in a geographic projected coordinate system.
 */

#if !defined(spatialdata_spatialdb_simplegriddb_hh)
#define spatialdata_spatialdb_simplegriddb_hh

#include "SpatialDB.hh" // ISA SpatialDB

#include <string> // HASA std::string

class spatialdata::spatialdb::SimpleGridDB : public SpatialDB { // SimpleGridDB
    friend class TestSimpleGridDB; // unit testing
    friend class TestSimpleGridAscii;
    friend class SimpleGridAscii; // reader

public:

    // PUBLIC ENUM ////////////////////////////////////////////////////////

    /** Type of query */
    enum QueryEnum {
        NEAREST=0, ///< Nearest interpolation.
        LINEAR=1, ///< Linear interpolation.
    };

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    /// Constructor
    SimpleGridDB(void);

    /// Destructor
    ~SimpleGridDB(void);

    /** Set filename containing data.
     *
     * @param value Name of data file.
     */
    void setFilename(const char* value);

    /** Set query type.
     *
     * @pre Must call Open() before QueryType()
     *
     * @param queryType Set type of query
     */
    void setQueryType(const QueryEnum queryType);

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
     * @note pVals should be preallocated to accommodate numVals values.
     *
     * @pre Must call open() before query()
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param coords Coordinates of point for query
     * @param numDims Number of dimensions for coordinates
     * @param pCSQuery Coordinate system of coordinates
     *
     * @returns 0 on success, 1 on failure (i.e., could not interpolate)
     */
    int query(double* vals,
              const size_t numVals,
              const double* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* pCSQuery);

    /** Allocate room for data.
     *
     * @param numX Number of locations along x-axis.
     * @param numY Number of locations along y-axis.
     * @param numZ Number of locations along z-axis.
     * @param numValues Number of values at each location.
     * @param spaceDim Spatial dimension.
     * @param dataDim Spatial dimension of topology.
     */
    void allocate(const size_t numX,
                  const size_t numY,
                  const size_t numZ,
                  const size_t numValues,
                  const size_t spaceDim,
                  const size_t dataDim);

    /** Set coordinates along x-axis;
     *
     * @param values Values along x-axis.
     * @param size Number of values along x-axis.
     */
    void setX(const double* values,
              const size_t size);

    /** Set coordinates along y-axis;
     *
     * @param values Values along y-axis.
     * @param size Number of values along y-axis.
     */
    void setY(const double* values,
              const size_t size);

    /** Set coordinates along z-axis;
     *
     * @param values Values along z-axis.
     * @param size Number of values along z-axis.
     */
    void setZ(const double* values,
              const size_t size);

    /** Set data values.
     *
     * @param coords Coordinates of locations.
     * @param numLocs Number of locations.
     * @param spaceDim Coordinate dimension.
     * @param values Data values.
     * @param numLocs2 Number of locations.
     * @param numValues Number of values per location.
     */
    void setData(const double* coords,
                 const size_t numLocs,
                 const size_t spaceDim,
                 const double* values,
                 const size_t numLocs2,
                 const size_t numValues);

    /** Set names of data values.
     *
     * @param values Names of values.
     * @param numValues Number of values.
     */
    void setNames(const char* const* values,
                  const size_t numValues);

    /** Set units of data values.
     *
     * @param values Units of values.
     * @param numValues Number of values.
     */
    void setUnits(const char* const* values,
                  const size_t numValues);

    /** Set coordinate system.
     *
     * @param cs Coordinate system for spatial database.
     */
    void setCoordSys(const geocoords::CoordSys& cs);

    // PRIVATE METHODS //////////////////////////////////////////////////////
private:

    /// Check compatibility of spatial database parameters.
    void _checkCompatibility(void) const;

    /** Bilinear search for coordinate.
     *
     * Returns index of target as a double.
     *
     * @param target Coordinates of target.
     * @param vals Array of ordered values to search.
     * @param nvals Number of values.
     */
    double _search(const double target,
                   const double* vals,
                   const size_t nvals) const;

    /** Interpolate in 1-D to get values at target location defined by
     * indices.
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param indexX Index along x dimension.
     * @param numX Number of coordinates along x dimension.
     */
    void _interpolate1D(double* vals,
                        const size_t numVals,
                        const double indexX,
                        const size_t numX) const;

    /** Interpolate in 2-D to get values at target location defined by
     * indices.
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param indexX Index along x dimension.
     * @param numX Number of coordinates along x dimension.
     * @param indexY Index along y dimension.
     * @param numY Number of coordinates along y dimension.
     */
    void _interpolate2D(double* vals,
                        const size_t numVals,
                        const double indexX,
                        const size_t numX,
                        const double indexY,
                        const size_t numY) const;

    /** Interpolate in 3-D to get values at target location defined by
     * indices.
     *
     * @param vals Array for computed values (output from query), must be
     *   allocated BEFORE calling query().
     * @param numVals Number of values expected (size of pVals array)
     * @param indexX Index along x dimension.
     * @param indexY Index along y dimension.
     * @param indexZ Index along z dimension.
     */
    void _interpolate3D(double* vals,
                        const size_t numVals,
                        const double indexX,
                        const double indexY,
                        const double indexZ) const;

    /** Adjust indices to account for optimizations for lower dimension
     *  distribution.
     *
     * @param index0 Adjusted index for coordinate 0.
     * @param size0 Adjusted size for coordinate 0.
     * @param index1 Adjusted index for dimension 1.
     * @param size1 Adjusted size for dimension 1.
     */
    void _reindex2d(double* const index0,
                    size_t* const size0,
                    double* const index1,
                    size_t* const size1) const;

    /** Adjust indices to account for optimizations for lower dimension
     *  distribution.
     *
     * @param index0 Adjusted index for coordinate 0.
     * @param size0 Adjusted size for coordinate 0.
     * @param index1 Adjusted index for dimension 1.
     * @param size1 Adjusted size for dimension 1.
     * @param index2 Adjusted index for dimension 2.
     * @param size2 Adjusted size for dimension 2.
     */
    void _reindex3d(double* const index0,
                    size_t* const size0,
                    double* const index1,
                    size_t* const size1,
                    double* const index2,
                    size_t* const size2) const;

    /** Get index into data array.
     *
     * @param index0 Adjusted index for coordinate 0.
     * @param size0 Adjusted size for coordinate 0.
     * @param index1 Adjusted index for dimension 1.
     * @param size1 Adjusted size for dimension 1.
     * @param index2 Adjusted index for dimension 2.
     * @param size2 Adjusted size for dimension 2.
     *
     * @returns Index into data array.
     */
    size_t _getDataIndex(const size_t index0,
                         const size_t size0,
                         const size_t index1,
                         const size_t size1,
                         const size_t index2,
                         const size_t size2) const;

    /** Get index into data array.
     *
     * @param Coordinates of point.
     * @param spaceDim Number of coordinate dimensions.
     *
     * @returns Index into data array.
     */
    size_t _getDataIndex(const double* const coords,
                         const size_t spaceDim) const;

    // PRIVATE MEMBERS //////////////////////////////////////////////////////
private:

    double* _data; ///< Array of data values.
    double* _x; ///< Array of x coordinates.
    double* _y; ///< Array of y coordinates.
    double* _z; ///< Array of z coordinates.

    double _xyz[3];

    size_t* _queryValues; ///< Indices of values to be returned in queries.
    size_t _querySize; ///< Number of values requested to be returned in queries.

    size_t _numX; ///< Number of points along x dimension.
    size_t _numY; ///< Number of points along y dimension.
    size_t _numZ; ///< Number of points along z dimension.
    size_t _dataDim; ///< Dimension of data topology.
    size_t _spaceDim; ///< Spatial dimension of data.

    size_t _numValues; ///< Number of values in database.
    std::string* _names; ///< Names of data values.
    std::string* _units; ///< Units of values.

    std::string _filename; ///< Filename of data file
    geocoords::CoordSys* _cs; ///< Coordinate system
    spatialdata::geocoords::Converter* _converter; /// Convert query points to local coordinate system.

    QueryEnum _queryType; ///< Query type

    static const char* FILEHEADER;

    // NOT IMPLEMENTED //////////////////////////////////////////////////////
private:

    SimpleGridDB(const SimpleGridDB&); ///< Not implemented
    const SimpleGridDB& operator=(const SimpleGridDB&); ///< Not implemented

}; // SimpleGridDB

#include "SimpleGridDB.icc" // inline methods

#endif // spatialdata_spatialdb_simplegriddb_hh

// End of file
