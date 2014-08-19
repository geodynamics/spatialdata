// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/CompositeDB.hh
 *
 * @brief C++ manager for simple spatial database.
 */

#if !defined(spatialdata_spatialdb_compositedb_hh)
#define spatialdata_spatialdb_compositedb_hh

#include "SpatialDB.hh"

#include <string> // HASA std::string

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::CompositeDB : public SpatialDB
{ // class CompositeDB
  friend class TestCompositeDB; // unit testing

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  CompositeDB(void);
  
  /** Constructor with label.
   *
   * @param label Label of database
   */
  CompositeDB(const char* label);
  
  /// Default destructor.
  ~CompositeDB(void);
  
  /** Set database A.
   *
   * @param db Pointer to database.
   * @param names Array of names of values to use with database.
   * @param numNames Size of array of names.
   */
  void dbA(SpatialDB* db,
	   const char* const* names,
	   const int numNames);

  /** Set database B.
   *
   * @param db Pointer to database.
   * @param names Array of names of values to use with database.
   * @param numNames Size of array of names.
   */
  void dbB(SpatialDB* db,
	   const char* const* names,
	   const int numNames);

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
   * @pre Must call open() before query()
   *
   * @param vals Array for computed values (output from query), vals
   *   must be allocated BEFORE calling query().
   * @param numVals Number of values expected (size of pVals array)
   * @param coords Coordinates of point for query
   * @param numDims Number of dimensions for coordinates
   * @param pCSQuery Coordinate system of coordinates
   *
   * @returns 0 on success, 1 on failure (i.e., could not interpolate
   *   so values set to 0)
   */
  int query(double* vals,
	    const int numVals,
	    const double* coords,
	    const int numDims,
	    const spatialdata::geocoords::CoordSys* pCSQuery);

private :
  // NOT IMPLEMENTED ////////////////////////////////////////////////////

  CompositeDB(const CompositeDB& data); ///< Not implemented
  const CompositeDB& operator=(const CompositeDB& data); ///< Not implemented
  
private :
  // PRIVATE STRUCTS ////////////////////////////////////////////////////

  struct dbinfo {
    double* query_buffer;
    int* query_indices;
    std::string* names_values;
    int query_size;
    int num_names;
  }; // dbinfo

private :
 // PRIVATE MEMBERS /////////////////////////////////////////////////////

  SpatialDB* _dbA; ///< Spatial database A
  SpatialDB* _dbB; ///< Spatial database B

  dbinfo* _infoA; ///< Information for database A
  dbinfo* _infoB; ///< Information for database B
}; // class CompositeDB

#endif // spatialdata_spatialdb_compositedb_hh


// End of file 
