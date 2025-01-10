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
#include "SimpleDB.hh" // USES SimpleDB

#include "spatialdata/geocoords/geocoordsfwd.hh" // HOLDSA Converter

#include <vector> // USES std::vector

// ----------------------------------------------------------------------
class spatialdata::spatialdb::SimpleDBQuery { // class SimpleDBQuery
    friend class TestSimpleDBQuery;

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /** Default constructor.
     *
     * @param db Database
     */
    SimpleDBQuery(const SimpleDB& db);

    /// Default destructor.
    ~SimpleDBQuery(void);

    /// Dellocate data structures.
    void deallocate(void);

    /** Set query type.
     *
     * @param value Set type of query
     */
    void setQueryType(const SimpleDB::QueryEnum value);

    /** Set values to be returned by queries.
     *
     * @param names Names of values to be returned in queries
     * @param numVals Number of values to be returned in queries
     */
    void setQueryValues(const char* const* names,
                        const size_t numVals);

    /** Query the database.
     *
     * @param vals Array for computed values (output from query)
     * @param numVals Number of values expected (size of pVals array)
     * @param coords Coordinates of point to query
     * @param numDims Number of dimensions for coordinates
     * @param pCSQuery Coordinate system of coordinates
     */
    void query(double* vals,
               const size_t numVals,
               const double* coords,
               const size_t numDims,
               const spatialdata::geocoords::CoordSys* pCSQuery);

private:

    // PRIVATE STRUCT /////////////////////////////////////////////////////

    /** Interpolation weighting information */
    struct WtStruct {
        double wt; ///< Weight for location
        size_t nearIndex; ///< Index into nearest
    }; // struct WtStruct

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    /** Query database using nearest neighbor algorithm.
     *
     * Values at location are equal to values at nearest location in
     * database.
     *
     * @param values Array for computed values (output from query)
     * @param numVals Number of values expected (size of pVals array)
     */
    void _queryNearest(double* vals,
                       const size_t numVals);

    /** Query database using linear interpolation algorithm.
     *
     * Values at location are interpolation from locations in database.
     *
     * @param vals Array for computed values (output from query)
     * @param numVals Number of values expected (size of pVals array)
     */
    void _queryLinear(double* vals,
                      const size_t numVals);

    /// Find locations in database nearest query location.
    void _findNearest(void);

    /** Get interpolation weighting functions for query.
     *
     * @param pWeights Pointer to array of interpolation weights
     */
    void _getWeights(std::vector<WtStruct>* pWeights);

    /** Get interpolation weighting functions for point interpolation.
     *
     * This routine is not actually used by a point query since it is
     * trivial. Instead it is used with the other topologies to build up
     * interpolation to the higher dimensions.
     *
     * @param pWeights Pointer to array of interpolation weights
     */
    void _findPointPt(std::vector<WtStruct>* pWeights);

    /** Get interpolation weighting functions for linear interpolation.
     *
     * @param pWeights Pointer to array of interpolation weights
     */
    void _findLinePt(std::vector<WtStruct>* pWeights);

    /** Get interpolation weighting functions for areal interpolation.
     *
     * @param pWeights Pointer to array of interpolation weights
     */
    void _findAreaPt(std::vector<WtStruct>* pWeights);

    /** Get interpolation weighting functions for volumetric interpolation.
     *
     * @param pWeights Pointer to array of interpolation weights
     */
    void _findVolumePt(std::vector<WtStruct>* pWeights);

    /** Set coordiantes of point in 3-D space using coordinates in
     * current coordinate system.
     *
     * @param pt3 Coordinates of point in 3-D space [output].
     * @param pt Cooridinates of point in current coordinate sytem.
     * @param spaceDim Spatial dimension of current coordinate system.
     */
    static
    void _setPoint3(double* const pt3,
                    const double* pt,
                    const size_t spaceDim);

    /** Compute square of distance between points A and B.
     *
     * @param a Coordinates of point A
     * @param b Coordinates of point B
     */
    static double _distSquared(const double a[3],
                               const double b[3]);

    /** Compute area and "direction" of triangle abc. Direction is vector
     * normal to triangular surface.
     *
     * @param a Coordinates of point A
     * @param b Coordinates of point B
     * @param c Coordinates of point C
     */
    static void _area(double* area,
                      double dir[3],
                      const double* a,
                      const double* b,
                      const double* c);

    /** Compute volume of tetrahedral defined by four points.
     *
     * @param a Coordinates of point A
     * @param b Coordinates of point B
     * @param c Coordinates of point C
     * @param d Coordinates of point D
     */
    static double _volume(const double a[3],
                          const double b[3],
                          const double c[3],
                          const double d[3]);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    double _q[3]; ///< Location of query.
    SimpleDB::QueryEnum _queryType; ///< Query type.
    std::vector<size_t> _nearest; ///< Index of nearest points in database to location.
    const SimpleDB& _db; ///< Reference to simple database.
    spatialdata::geocoords::Converter* _converter; ///< Covert query points to local coordinate system.

    size_t* _queryValues; ///< Indices of values to be returned in queries.
    size_t _querySize; ///< Nmber of values to be returned in queries.

}; // class SimpleDBQuery

// End of file
