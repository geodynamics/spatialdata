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

/** @file lib/SpatialDB.h
 *
 * @brief C++ manager for spatial database.
 */

#if !defined(_spatial_spatialdb_h)
#define _spatial_spatialdb_h

namespace spatial {
  class SpatialDB;
}; // namespace spatial

/// C++ manager for spatial database.
class spatial::SpatialDB
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
  void Label(const char* label);
  
  /// Open the database and prepare for querying.
  virtual void Open(void) = 0;

  /// Close the database.
  virtual void Close(void) = 0;

  /** Set values to be returned by queries.
   *
   * @pre Must call Open() before QueryVals()
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  virtual void QueryVals(const char** names,
			 const int numVals) = 0;

  /** Query the database.
   *
   * @pre Must call Open() before Query()
   *
   * @param pVals Pointer to computed values (output from query)
   * @param x X coordinate of location for query
   * @param y Y coordinate of location for query
   * @param z Z coordinate of location for query
   */
  virtual void Query(double** pVals,
		     const double x,
		     const double y,
		     const double z) = 0;

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Get label of spatial database.
   *
   * @returns Label of spatial database
   */
  const char* Label(void) const;
  
 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////
  
  SpatialDB(const SpatialDB& data); ///< Not implemented
  const SpatialDB& operator=(const SpatialDB& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////
  
  /** Label of spatial database */
  const char* mLabel;

}; // class SpatialDB

#include "SpatialDB.icc" // inline methods

#endif // _spatial_spatialdb_h

// version
// $Id: SpatialDB.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
