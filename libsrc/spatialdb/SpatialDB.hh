// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SpatialDB.h
 *
 * @brief C++ manager for spatial database.
 */

#if !defined(spatialdata_spatialdb_spatialdb_hh)
#define spatialdata_spatialdb_spatialdb_hh

namespace spatialdata {
  namespace spatialdb {
    class SpatialDB;
  } // spatialdb
  namespace geocoords {
    class CoordSys; // forward declaration
  } // geocoords
} // spatialdata

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
  virtual ~SpatialDB(void);

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
  virtual void open(void) = 0;

  /// Close the database.
  virtual void close(void) = 0;

  /** Set values to be returned by queries.
   *
   * @pre Must call open() before queryVals()
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  virtual void queryVals(const char** names,
			 const int numVals) = 0;

  /** Query the database.
   *
   * @note pVals should be preallocated to accommodate numVals values.
   *
   * @pre Must call open() before query()
   *
   * @param vals Array for computed values (output from query), must be
   *   allocated BEFORE calling query().
   * @param numVals Number of values expected (size of pVals array)
   * @param x X coordinate of location for query
   * @param y Y coordinate of location for query
   * @param z Z coordinate of location for query
   * @param pCSQuery Coordinate system of coordinates
   *
   * @returns 0 on success, 1 on failure (i.e., could not interpolate)
   */
  virtual int query(double* vals,
		    const int numVals,
		    const double x,
		    const double y,
		    const double z,
		    const spatialdata::geocoords::CoordSys* pCSQuery) = 0;

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////
  
  SpatialDB(const SpatialDB& data); ///< Not implemented
  const SpatialDB& operator=(const SpatialDB& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////
  
  /** Label of spatial database */
  const char* _label;

}; // class SpatialDB

#include "SpatialDB.icc" // inline methods

#endif // spatialdata_spatialdb_spatialdb_hh

// version
// $Id$

// End of file 
