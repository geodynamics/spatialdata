// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/GravityField.hh
 *
 * @brief C++ manager for simple spatial database.
 */

#if !defined(spatialdata_spatialdb_gravityfield_hh)
#define spatialdata_spatialdb_gravityfield_hh

#include "SpatialDB.hh"

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::GravityField : public SpatialDB
{ // class GravityField
  friend class TestGravityField; // unit testing

 public :
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
  void gravityDir(const double x,
		  const double y,
		  const double z);

  /** Set gravitational acceleration.
   *
   * @param acceleration Gravitational acceleration.
   */
  void gravAcceleration(const double acceleration);

  /// Open the database and prepare for querying.
  void open(void);

  /// Close the database.
  void close(void);

  /** Set values to be returned by queries.
   *
   * Valid values for use in names are {'x', 'y', 'z'}.
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
	    const int numVals,
	    const double* coords,
	    const int numDims,
	    const spatialdata::geocoords::CoordSys* cs);

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  GravityField(const GravityField& data); ///< Not implemented
  const GravityField& operator=(const GravityField& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS /////////////////////////////////////////////////////

  double _gravityDir[3]; ///< Direction of gravitational body force.
  double _acceleration; ///< Acceleration due to gravity.
  geocoords::CSGeo* _csECEF; ///< Earth-centered/Earth-fixed coordinate system.
  int* _queryVals; ///< Indices of values to be returned in queries.
  int _querySize; ///< Number of values requested to be returned in queries.
}; // class GravityField

#include "GravityField.icc"

#endif // spatialdata_spatialdb_gravityfield_hh


// End of file 
