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
       * @note pVals should be preallocated to accommodate numVals values.
       *
       * @pre Must call open() before query()
       *
       * @param vals Array for computed values (output from query), must be
       *   allocated BEFORE calling query().
       * @param numVals Number of values expected (size of pVals array)
       * @param coords Coordinates of point for query
       * @param numDims Number of dimensions for coordinates
       * @param pCSQuery Coordinate system of coordinates
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
		const spatialdata::geocoords::CoordSys* pCSQuery) = 0;
      %clear(double* vals, const int numVals);
      %clear(const double* coords, const int numDims);
      
    }; // class SpatialDB
    
  } // spatialdb
} // spatialdata


// End of file 
