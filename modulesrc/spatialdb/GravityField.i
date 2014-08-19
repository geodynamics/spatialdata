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

/** @file modulesrc/spatialdb/GravityField.i
 *
 * @brief SWIG interface to C++ GravityField object.
 */

namespace spatialdata {
  namespace geocoords {
    class CSGeo; // USES CSGeo
  } // geocoords

  namespace spatialdb {

    class GravityField : public SpatialDB
    { // class GravityField

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor.
      GravityField(void);
  
      /// Default destructor.
      ~GravityField(void);
      
      /** Set direction of gravitational body force. Used only with
       * Cartesian coordinate system.
       *
       * @param x X component of direction
       * @param y Y component of direction
       * @param z Z component of direction
       */
      void gravityDir(const double x,
		      const double y,
		      const double z);
      
      /** Set gravitational acceleration.
       *
       * @param acceleration Gravitational acceleration.
       */
      void gravAcceleration(const double acceleration);
      
      /// Open the database and prepare for querying.
      void open(void);
      
      /// Close the database.
      void close(void);
      
      /** Set values to be returned by queries.
       *
       * Valid values for use in names are {'x', 'y', 'z'}.
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
       * @param cs Coordinate system of coordinates
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
		const spatialdata::geocoords::CoordSys* cs);
      %clear(double* vals, const int numVals);
      %clear(const double* coords, const int numDims);
      
    }; // class GravityField
    
  } // spatialdb
} // spatialdata


// End of file 
