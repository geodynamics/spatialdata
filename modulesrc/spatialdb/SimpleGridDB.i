// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

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
      void setFilename(const char* value);

      /** Set query type.
       *
       * @pre Must call open() before setQueryType()
       *
       * @param queryType Set type of query
       */
      void setQueryType(const SimpleGridDB::QueryEnum queryType);

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
	(const double* coords, const size_t numDims)
	  };
      int query(double* vals,
		const size_t numVals,
		const double* coords,
		const size_t numDims,
		const spatialdata::geocoords::CoordSys* pCSQuery);
      %clear(double* vals, const size_t numVals);
      %clear(const double* coords, const size_t numDims);

      /** Allocate room for data.
       *
       * @param numX Number of locations along x-axis.
       * @param numY Number of locations along y-axis.
       * @param numZ Number of locations along z-axis.
       * @param numValues Number of values at each location.
       * @param spaceDim Spatial dimension.
       * @param dataDim Spatial dimension of topology.
       */
      void allocate(const size_t numX,
		    const size_t numY,
		    const size_t numZ,
		    const size_t numValues,
		    const size_t spaceDim,
		    const size_t dataDim);

      /** Set coordinates along x-axis;
       *
       * @param values Values along x-axis.
       * @param size Number of values along x-axis.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values, const size_t size)
	  };
      void setX(const double* values,
	     const size_t size);
      %clear(double* values, const size_t size);

      /** Set coordinates along y-axis;
       *
       * @param values Values along y-axis.
       * @param size Number of values along y-axis.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values, const size_t size)
	  };
      void setY(const double* values,
	     const size_t size);
      %clear(double* values, const size_t size);

      /** Set coordinates along z-axis;
       *
       * @param values Values along z-axis.
       * @param size Number of values along z-axis.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values,
	 const size_t size)
	  };
      void setZ(const double* values,
	     const size_t size);
      %clear(double* values, const size_t size);

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
	(const double* coords, const size_t numLocs, const size_t spaceDim)
	  };
      %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
	(const double* values, const size_t numLocs2, const size_t numValues)
	  };
      void setData(const double* coords,
		const size_t numLocs,
		const size_t spaceDim,
		const double* values,
		const size_t numLocs2,
		const size_t numValues);
      %clear(double* coords, const size_t size, const size_t spaceDim);
      %clear(double* values, const size_t numLocs2, const size_t numValues);

      /** Set names of data values.
       *
       * @param values Names of values.
       * @param numValues Number of values.
       */
      %apply(const char* const* string_list, const int list_len){
	     (const char* const* values, const size_t numValues)
	      };
      void setNames(const char* const* values,
                    const size_t numValues);
      %clear(const char* const* values, const size_t numValues);

      /** Set units of data values.
       *
       * @param values Units of values.
       * @param numValues Number of values.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* values, const size_t numValues)
	  };
      void setUnits(const char* const* values,
		                const size_t numValues);
      %clear(const char* const* values, const size_t numValues);

      /** Set filename containing data.
       *
       * @param dir Directory containing data files.
       */
      void setCoordSys(const spatialdata::geocoords::CoordSys& cs);

    }; // class SimpleGridDB

  } // spatialdb
} // spatialdata


// End of file
