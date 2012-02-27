// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SpatialDB.h
 *
 * @brief C++ manager for spatial database.
 */

#if !defined(spatialdata_spatialdb_spatialdb_hh)
#define spatialdata_spatialdb_spatialdb_hh

#include "spatialdbfwd.hh"
#include "spatialdata/geocoords/geocoordsfwd.hh"

#include <string> // USES std::string

/// C++ manager for spatial database.
class spatialdata::spatialdb::SpatialDB
{ // class SpatialDB

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////
  
  /// Default constructor.
  SpatialDB(void);
  
  /** Constructor with label.
   *
   * @param label Label for database
   */
  SpatialDB(const char* label);
  
  /// Default destructor.
  virtual
  ~SpatialDB(void);

  /** Set label of spatial database.
   *
   * @param label Label for database
   */
  void label(const char* label);
  
  /** Get label of spatial database.
   *
   * @returns Label for database
   */
  const char* label(void) const;

  /// Open the database and prepare for querying.
  virtual
  void open(void) = 0;

  /// Close the database.
  virtual
  void close(void) = 0;

  /** Set values to be returned by queries.
   *
   * @pre Must call open() before queryVals()
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  virtual
  void queryVals(const char* const* names,
		 const int numVals) = 0;

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
	    const int numVals,
	    const double* coords,
	    const int numDims,
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
	    const int numVals,
	    const float* coords,
	    const int numDims,
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
		  const int numLocsV,
		  const int numValsV,
		  int* err,
		  const int numLocsE,
		  const double* coords,
		  const int numLocsC,
		  const int numDimsC,
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
		  const int numLocsV,
		  const int numValsV,
		  int* err,
		  const int numLocsE,
		  const float* coords,
		  const int numLocsC,
		  const int numDimsC,
		  const spatialdata::geocoords::CoordSys* csQuery);

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////
  
  SpatialDB(const SpatialDB& data); ///< Not implemented
  const SpatialDB& operator=(const SpatialDB& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////
  
  /** Label of spatial database */
  std::string _label;

}; // class SpatialDB

#include "SpatialDB.icc" // inline methods

#endif // spatialdata_spatialdb_spatialdb_hh


// End of file 
