// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/spatialdb/CompositeDB.i
 *
 * @brief SWIG interface to C++ CompositeDB object.
 */

namespace spatialdata {
  namespace spatialdb {

    class CompositeDB : public SpatialDB
    { // class CompositeDB

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

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
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names, const size_t numNames)
	  };
      void setDBA(SpatialDB* db,
	       const char* const* names,
	       const size_t numNames);
      %clear(const char* const* names, const size_t numNames);

      /** Set database B.
       *
       * @param db Pointer to database.
       * @param names Array of names of values to use with database.
       * @param numNames Size of array of names.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names, const size_t numNames)
	  };
      void setDBB(SpatialDB* db,
	       const char* const* names,
	       const size_t numNames);
      %clear(const char* const* names, const size_t numNames);
      
      /// Open the database and prepare for querying.
      void open(void);
      
      /// Close the database.
      void close(void);
      
      /** Set values to be returned by queries.
       *
       * @pre Must call open() before setQueryValues()
       *
       * @param names Names of values to be returned in queries
       * @param numVals Number of values to be returned in queries
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names, const size_t numVals)
	  };
      void setQueryValues(const char* const* names,
		     const size_t numVals);
      %clear(const char* const* names, const size_t numVals);
      
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
      %apply(double* INPLACE_ARRAY1, int DIM1) {
	(double* vals, const size_t numVals)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* coords,
	 const size_t numDims)
	  };
      int query(double* vals,
		const size_t numVals,
		const double* coords,
		const size_t numDims,
		const spatialdata::geocoords::CoordSys* pCSQuery);
      %clear(double* vals, const size_t numVals);
      %clear(const double* coords, const size_t numDims);
      
    }; // class CompositeDB
    
  } // spatialdb
} // spatialdata


// End of file 
