// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
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
      
      /** Allocate room for data.
       *
       * @param numX Number of locations along x-axis.
       * @param numY Number of locations along y-axis.
       * @param numZ Number of locations along z-axis.
       * @param numValues Number of values at each location.
       * @param spaceDim Spatial dimension.
       * @param dataDim Spatial dimension of topology.
       */
      void allocate(const int numX,
		    const int numY,
		    const int numZ,
		    const int numValues,
		    const int spaceDim,
		    const int dataDim);
      
      /** Set coordinates along x-axis;
       *
       * @param values Values along x-axis.
       * @param size Number of values along x-axis.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values,
	 const int size)
	  };
      void x(const double* values,
	     const int size);
      %clear(double* values, const int size);
      
      /** Set coordinates along y-axis;
       *
       * @param values Values along y-axis.
       * @param size Number of values along y-axis.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values,
	 const int size)
	  };
      void y(const double* values,
	     const int size);
      %clear(double* values, const int size);
      
      /** Set coordinates along z-axis;
       *
       * @param values Values along z-axis.
       * @param size Number of values along z-axis.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values,
	 const int size)
	  };
      void z(const double* values,
	     const int size);
      %clear(double* values, const int size);
      
      /** Set data values.
       *
       * @param coords Coordinates of locations.
       * @param numLocs Number of locations.
       * @param spaceDim Coordinate dimension.
       * @param values Data values.
       * @param numLocs2 Number of locations.
       * @param numValues Number of values per location.
       */
      %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
	(const double* coords,
	 const int numLocs,
	 const int spaceDim)
	  };
      %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
	(const double* values,
	 const int numLocs2,
	 const int numValues)
	  };
      void data(const double* coords,
		const int numLocs,
		const int spaceDim,
		const double* values,
		const int numLocs2,
		const int numValues);
      %clear(double* coords, const int size, const int spaceDim);
      %clear(double* values, const int numLocs2, const int numValues);
      
      /** Set names of data values.
       *
       * @param values Names of values.
       * @param numValues Number of values.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* values,
	 const int numValues)
	  };
      void names(const char* const* values,
		 const int numValues);
      %clear(const char* const* values, const int numValues);
      
      /** Set units of data values.
       *
       * @param values Units of values.
       * @param numValues Number of values.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* values,
	 const int numValues)
	  };
      void units(const char* const* values,
		 const int numValues);
      %clear(const char* const* values, const int numValues);
      
      /** Set filename containing data.
       *
       * @param dir Directory containing data files.
       */
      void coordsys(const spatialdata::geocoords::CoordSys& cs);
 
    }; // class SimpleGridDB
    
  } // spatialdb
} // spatialdata


// End of file 
