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

#include "SpatialDB.hh" // ISA SpatialDB

#include <string> // HASA std::string
#include <map> // HASA std::map

class spatialdata::spatialdb::UserFunctionDB : public SpatialDB
{ // UserFunctionDB
  friend class TestUserFunctionDB; // unit testing
 
 public :
  // PUBLIC TYPEDEF//////////////////////////////////////////////////////

  /** User function prototype.
   *
   * @param value Return value of function.
   * @param coords Coordinates of point.
   * @param dim Spatial dimension of coordinate system.
   * @returns 0 if successful, 1 on failure.
   */
  typedef int (*queryfn_type)(double* value, const double* coords, const int dim);

  // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :
 
  /// Constructor
  UserFunctionDB(void);
 
  /// Destructor
  ~UserFunctionDB(void);

  /** Add function/value to database.
   *
   * @param name Name of value for function.
   * @param fn User function for value.
   * @param units Units associated with function value.
   */
  void addValue(const char* name,
		queryfn_type fn,
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
		 const int numVals);
 
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
	    const int numVals,
	    const double* coords,
	    const int numDims,
	    const spatialdata::geocoords::CoordSys* pCSQuery);
 
  /** Set coordinate system associated with user functions.
   *
   * @param cs Coordinate system.
   */
  void coordsys(const geocoords::CoordSys& cs);
 
// PRIVATE STRUCTS //////////////////////////////////////////////////////
private :

  /// Structure for holding user data
  struct UserData {
    queryfn_type fn; ///< User function for query.
    double scale; ///< Scale to convert to SI units.
  }; // UserData
    
// PRIVATE METHODS //////////////////////////////////////////////////////
private :

  /// Check compatibility of spatial database parameters.
  void _checkCompatibility(void) const;

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :
  
  UserData* _queryFunctions; ///< Array of values to be returned in queries.
  std::map<std::string, UserData> _functions; ///< User functions for values
  geocoords::CoordSys* _cs; ///< Coordinate system
  int _querySize; ///< Number of values to be returned in queries.

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :
 
  UserFunctionDB(const UserFunctionDB&); ///< Not implemented
  const UserFunctionDB& operator=(const UserFunctionDB&); ///< Not implemented
 
}; // UserFunctionDB

#endif // spatialdata_spatialdb_userfunctiondb_hh


// End of file 
