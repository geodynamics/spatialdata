// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

// SWIG interface to C++ UniformVelModel object.

/* This is nearly identical to the C++ UniformVelModel header
 * file. There are a few important differences required by SWIG:
 *
 * (1) Instead of forward declaring the UniformVelModel class, we
 * embed the class definition within the namespace declarations.
 *
 * (2) We only include public members and methods, because this is an
 * interface file.
 */

namespace contrib {
  namespace spatialdb {
    
    class UniformVelModel : public spatialdata::spatialdb::SpatialDB
    { // UniformVelModel
 
      // PUBLIC MEMBERS ///////////////////////////////////////////////////
    public :
 
      /// Constructor
      UniformVelModel(void);
      
      /// Destructor
      ~UniformVelModel(void);
      
      // PUBLIC METHODS ///////////////////////////////////////////////////
    public :
      
      // Functions required to satisfy the SpatialDB interface.
      
      /// Open the database and prepare for querying.
      void open(void);
      
      /// Close the database.
      void close(void);
      
      /** Set values to be returned by queries. Queries may not want all
       * of the values available.
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
       * @note pVals should be preallocated to accommodate numVals values.
       *
       * @pre Must call open() before query()
       *
       * @param vals Array for computed values (output from query), must be
       *   allocated BEFORE calling query().
       * @param numVals Number of values expected (size of pVals array)
       * @param coords Coordinates of point for query
       * @param numDims Number of dimensions for coordinates
       * @param csQuery Coordinate system of coordinates
       *
       * @returns 0 on success, 1 on failure (e.g., query location outside
       * region associated with the velocity model).
       */
      int query(double* vals,
		const int numVals,
		const double* coords,
		const int numDims,
		const spatialdata::geocoords::CoordSys* csQuery);
      
      // PUBLIC METHODS ///////////////////////////////////////////////////
    public :
      
      // Functions specific to this type of spatial database.
      
      /** Set the P wave speed.
       *
       * @param value P wave speed in m/s.
       */
      void vp(const double value);
      
      /** Set the S wave speed.
       *
       * @param value S wave speed in m/s.
       */
      void vs(const double value);
      
      /** Set the density.
       *
       * @param value Density in kg/m**3.
       */
      void density(const double value);
      
    }; // UniformVelModel

  } // spatialdb
} // contrib


// End of file
