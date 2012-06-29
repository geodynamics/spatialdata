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

/** @file modulesrc/spatialdb/SimpleGridDB.i
 *
 * @brief SWIG interface to C++ SimpleGridDB object.
 */

namespace spatialdata {
  namespace spatialdb {
    class SimpleIO; // USES SimpleIO

    class SimpleGridDB : public SpatialDB
    { // class SimpleGridDB

    public :
      // PUBLIC ENUM ////////////////////////////////////////////////////

      /** Type of query */
      enum QueryEnum {
	NEAREST=0,
	LINEAR=1
      };

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor.
      SimpleGridDB(void);
  
      /// Default destructor.
      ~SimpleGridDB(void);
      
      /** Set filename containing data.
       *
       * @param dir Directory containing data files.
       */
      void filename(const char* value);
 
      /// Open the database and prepare for querying.
      void open(void);
      
      /// Close the database.
      void close(void);
      
      /** Set query type.
       *
       * @pre Must call Open() before QueryType()
       *
       * @param queryType Set type of query
       */
      void queryType(const SimpleGridDB::QueryEnum queryType);
      
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
      
    }; // class SimpleGridDB
    
  } // spatialdb
} // spatialdata


// End of file 
