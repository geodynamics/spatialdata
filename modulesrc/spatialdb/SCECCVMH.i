// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/spatialdb/SCECCVMH.i
 *
 * @brief SWIG interface to C++ SCECCVMH object.
 */

namespace spatialdata {
  namespace geocoords {
    class CSGeoProj; // HASA CSGeoProj
  } // geocoords

  namespace spatialdb {

    class SCECCVMH : public SpatialDB
    { // SCECCVMH
 
    public :
      // PUBLIC MEMBERS /////////////////////////////////////////////////
 
      /// Constructor
      SCECCVMH(void);
 
      /// Destructor
      ~SCECCVMH(void);
      
      /** Set directory containing SCEC CVM-H data files.
       *
       * @param dir Directory containing data files.
       */
      void dataDir(const char* dir);
      
      /** Set minimum shear wave speed. Corresponding minima for Vp and
       * density are enforced using nominal Vp->Vs relation and
       * Vp->density relations.
       *
       * @param value Minimum shear wave speed.
       */
      void minVs(const double value);
      
      /** Set squashed topography/bathymetry flag and minimum
       * elevation of squashing.
       *
       * @param flag True if squashing, false otherwise.
       * @param limit Minimum elevation for squashing.
       */
      void squash(const bool flag,
		  const double limit =-2000.0);
      
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
      int query(double* vals,
		const int numVals,
		const double* coords,
		const int numDims,
		const spatialdata::geocoords::CoordSys* pCSQuery);
      %clear(double* vals, const int numVals);
      %clear(const double* coords, const int numDims); 
      
    }; // SCECCVMH
    
  } // spatialdb
} // spatialdata


// End of file 
