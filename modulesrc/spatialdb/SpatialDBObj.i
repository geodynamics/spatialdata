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

/** @file modulesrc/spatialdb/SpatialDBObj.i
 *
 * @brief SWIG interface to C++ SpatialDB object.
 */

namespace spatialdata {
  namespace geocoords {
    class CoordSys; // forward declaration
  } // geocoords

  namespace spatialdb {

    class SpatialDB
    { // class SpatialDB

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////
  
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
      %apply(const char* const* string_list, const int list_len){
	(const char* const* names,
	 const int numVals)
	  };
      virtual
      void queryVals(const char* const* names,
		     const int numVals) = 0;
      %clear(const char* const* names, const int numVals);

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
      %apply(double* INPLACE_ARRAY1, int DIM1) {
	(double* vals,
	 const int numVals)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* coords,
	 const int numDims)
	  };
      virtual
      int query(double* vals,
		const int numVals,
		const double* coords,
		const int numDims,
		const spatialdata::geocoords::CoordSys* csQuery) = 0;
      %clear(double* vals, const int numVals);
      %clear(const double* coords, const int numDims);
      
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
      %apply(double* INPLACE_ARRAY2, int DIM1, int DIM2) {
	(double* vals,
	 const int numLocsV,
	 const int numValsV)
	  };
      %apply(int* INPLACE_ARRAY1, int DIM1) {
	(int* err,
	 const int numLocsE)
	  };
      %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
	(const double* coords,
	 const int numLocsC,
	 const int numDimsC)
	  };
      void multiquery(double* vals,
		      const int numLocsV,
		      const int numValsV,
		      int* err,
		      const int numLocsE,
		      const double* coords,
		      const int numLocsC,
		      const int numDimsC,
		      const spatialdata::geocoords::CoordSys* csQuery);
      %clear(double* vals, const int numLocsV, const int numValsV);
      %clear(int* err, const int numLocsE);
      %clear(const double* coords, const int numLocsC, const int numDimsC);
      
    }; // class SpatialDB
    
  } // spatialdb
} // spatialdata


// End of file 
