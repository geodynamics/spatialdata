// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

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
	(const char* const* names,
	 const int numNames)
	  };
      void dbA(SpatialDB* db,
	       const char* const* names,
	       const int numNames);
      %clear(const char* const* names, const int numNames);

      /** Set database B.
       *
       * @param db Pointer to database.
       * @param names Array of names of values to use with database.
       * @param numNames Size of array of names.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names,
	 const int numNames)
	  };
      void dbB(SpatialDB* db,
	       const char* const* names,
	       const int numNames);
      %clear(const char* const* names, const int numNames);
      
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
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names,
	 const int numVals)
	  };
      void queryVals(const char* const* names,
		     const int numVals);
      %clear(const char* const* names, const int numVals);
      
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
	(double* vals,
	 const int numVals)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* coords,
	 const int numDims)
	  };
      int query(double* vals,
		const int numVals,
		const double* coords,
		const int numDims,
		const spatialdata::geocoords::CoordSys* pCSQuery);
      %clear(double* vals, const int numVals);
      %clear(const double* coords, const int numDims);
      
    }; // class CompositeDB
    
  } // spatialdb
} // spatialdata


// End of file 
