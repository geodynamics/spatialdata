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

/** @file libsrc/spatialdb/UserFunctionDB.hh
 *
 * @brief C++ object for performing querying of data on a nonuniform
 * (or uniform) grid in a geographic projected coordinate system.
 */

#if !defined(spatialdata_spatialdb_userfunctiondb_hh)
#define spatialdata_spatialdb_userfunctiondb_hh

#include "spatialdata/spatialdb/SpatialDB.hh" // ISA SpatialDB

#include <string> // HASA std::string
#include <map> // HASA std::map

class spatialdata::spatialdb::UserFunctionDB : public SpatialDB { // UserFunctionDB
    friend class TestUserFunctionDB; // unit testing

public:

    // PUBLIC TYPEDEF//////////////////////////////////////////////////////

    /** User function prototype in 1-D.
     *
     * @param x X coordinate.
     * @returns Value of user-defined function.
     */
    typedef double (*userfn1D_type)(const double x);

    /** User function prototype in 2-D.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @returns Value of user-defined function.
     */
    typedef double (*userfn2D_type)(const double x,
                                    const double y);

    /** User function prototype in 3-D.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param z Z coordinate.
     * @returns Value of user-defined function.
     */
    typedef double (*userfn3D_type)(const double x,
                                    const double y,
                                    const double z);

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    /// Constructor
    UserFunctionDB(void);

    /// Destructor
    ~UserFunctionDB(void);

    /** Add function/value to database in 1-D.
     *
     * @param name Name of value for function.
     * @param fn User function for value.
     * @param units Units associated with function value.
     */
    void addValue(const char* name,
                  userfn1D_type fn,
                  const char* units);

    /** Add function/value to database in 2-D.
     *
     * @param name Name of value for function.
     * @param fn User function for value.
     * @param units Units associated with function value.
     */
    void addValue(const char* name,
                  userfn2D_type fn,
                  const char* units);

    /** Add function/value to database in 3-D.
     *
     * @param name Name of value for function.
     * @param fn User function for value.
     * @param units Units associated with function value.
     */
    void addValue(const char* name,
                  userfn3D_type fn,
                  const char* units);

    /// Open the database and prepare for querying.
    void open(void);

    /// Close the database.
    void close(void);

    /** Set values to be returned by queries.
     *
     * @pre Must call open() before queryVals()
     *
     * @param names Names of values to be returned in queries
     * @param numVals Number of values to be returned in queries
     */
    void queryVals(const char* const* names,
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
     * @returns 0 on success, 1 on failure.
     */
    int query(double* vals,
              const size_t numVals,
              const double* coords,
              const size_t numDims,
              const spatialdata::geocoords::CoordSys* pCSQuery);

    /** Set coordinate system associated with user functions.
     *
     * @param cs Coordinate system.
     */
    void coordsys(const geocoords::CoordSys& cs);

private:

    // PRIVATE TYPEDEF//////////////////////////////////////////////////////

    /** User function prototype.
     *
     * @param value Return value of function.
     * @param coords Coordinates of point.
     * @param dim Spatial dimension of coordinate system.
     * @returns 0 if successful, 1 on failure.
     */
    typedef int (*queryfn_type)(double* value,
                                const double* coords,
                                const int dim);

    // PRIVATE METHODS //////////////////////////////////////////////////////
private:

    /** Check suitability of arguments for adding user function.
     *
     * @parma[in] name Name of value.
     * @param[in] fn User-defined function for value.
     * @param[in] units Units of value.
     */
    void _checkAdd(const char* name,
                   void* fn,
                   const char* units) const;

    /// Check compatibility of spatial database parameters.
    void _checkCompatibility(void) const;

    // PRIVATE STRUCTS //////////////////////////////////////////////////////
private:

    class QueryFn {
public:

        QueryFn(void) {}


        virtual ~QueryFn(void) {}


        virtual int query(double* value,
                          const double* coords,
                          const int dim) = 0;

    };
    class QueryFn1D;
    class QueryFn2D;
    class QueryFn3D;

    /// Structure for holding user data
    struct UserData {
        QueryFn* fn; ///< User-defined function for query.
        std::string units; ///< Units for value of user function.
        double scale; ///< Scale to convert to SI units.
    }; // UserData

    typedef std::map<std::string, UserData> function_map;

    // PRIVATE MEMBERS //////////////////////////////////////////////////////
private:

    UserData** _queryFunctions; ///< Array of pointers to _functions of values to be returned in queries.
    std::map<std::string, UserData> _functions; ///< User functions for values.
    geocoords::CoordSys* _cs; ///< Coordinate system
    int _querySize; ///< Number of values to be returned in queries.

    // NOT IMPLEMENTED //////////////////////////////////////////////////////
private:

    UserFunctionDB(const UserFunctionDB&); ///< Not implemented
    const UserFunctionDB& operator=(const UserFunctionDB&); ///< Not implemented

}; // UserFunctionDB

#endif // spatialdata_spatialdb_userfunctiondb_hh

// End of file
