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

/** This is the C++ header file that describes the UniformVelModel
 *  object. It includes the functions and data structures associated
 *  with the object.
 */

#if !defined(contrib_uniformvelmodel_hh)
#define contrib_uniformvelmodel_hh

#include "spatialdata/spatialdb/SpatialDB.hh" // ISA SpatialDB

// Forward declaration of the C++ UniformVelModel object in the
// contrib/spatialdb namespace.
namespace contrib {
  namespace spatialdb {
    class UniformVelModel;
  } // spatialdb
} // contrib

class contrib::spatialdb::UniformVelModel : 
  public spatialdata::spatialdb::SpatialDB // inheritance from SpatialDB
{ // UniformVelModel
  // Allow the unit testing TestUniformVelModel object access to
  // private class methods and members.
  friend class TestUniformVelModel;
 
// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
 
  /// Constructor
  UniformVelModel(void);
 
  /// Destructor
  ~UniformVelModel(void);

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :
 
  // Functions required to satisfy the SpatialDB interface.
 
  /// Open the database and prepare for querying.
  void open(void);
 
  /// Close the database.
  void close(void);
 
  /** Set values to be returned by queries. Queries may not want all
   * of the values available.
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
   * @param csQuery Coordinate system of coordinates
   *
   * @returns 0 on success, 1 on failure (e.g., query location outside
   * region associated with the velocity model).
   */
  int query(double* vals,
	    const int numVals,
	    const double* coords,
	    const int numDims,
	    const spatialdata::geocoords::CoordSys* csQuery);
 
// PUBLIC METHODS ///////////////////////////////////////////////////////
public :

  // Functions specific to this type of spatial database.

  /** Set the P wave speed.
   *
   * @param value P wave speed in m/s.
   */
  void vp(const double value);

  /** Set the S wave speed.
   *
   * @param value S wave speed in m/s.
   */
  void vs(const double value);

  /** Set the density.
   *
   * @param value Density in kg/m**3.
   */
  void density(const double value);
 
// PRIVATE ENUMS ////////////////////////////////////////////////////////
private :
 
  // Indices of values in database (used in queryVals to indicate
  // which values to return in a query).
  enum QueryValsEnum {
    QUERY_VP=0, // vp
    QUERY_VS=1, // vs
    QUERY_DENSITY=2, // density
  }; // ValsEnum

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  // Physical property information (hardwired in this case). Replace
  // with data structures for holding the physical property
  // information.

  double _vp; ///< P wave speed
  double _vs; ///< S wave speed
  double _density; ///< Density
  
  /// Coordinate system for velocity model. When querying the velocity
  /// model for physical properties, the coordinates of the query are
  /// transformed into this coordinate system.
  spatialdata::geocoords::CSGeoProj* _cs;
  double _xyz[3]; ///< Array used in conversion of coordinates.

  int* _queryVals; ///< Indices of values to be returned in queries.
  int _querySize; ///< Number of values requested to be returned in queries.

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :
 
  UniformVelModel(const UniformVelModel&); ///< Not implemented
  const UniformVelModel& operator=(const UniformVelModel&); ///< Not implemented
 
}; // UniformVelModel

#endif // contrib_uniformvelmodel_hh


// End of file 
