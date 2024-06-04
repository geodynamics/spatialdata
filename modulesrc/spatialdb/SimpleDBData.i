// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/spatialdb/SimpleDBData.i
 *
 * @brief SWIG interface to C++ SimpleDBData object.
 */

namespace spatialdata {
  namespace spatialdb {

    class SimpleDBData
    { // SimpleDBData

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      SimpleDBData(void);

      /// Default destructor
      ~SimpleDBData(void);
      
      /** Allocate data structues.
       *
       * @param numLocs Number of locations.
       * @param numValues Number of values.
       * @param spaceDim Spatial dimension of domain.
       * @param dataDim Spatial dimension of data distribution.
       */
      void allocate(const int numLocs,
		    const int numValues,
		    const int spaceDim,
		    const int dataDim);
      
      /** Set data values.
       *
       * @pre Must call allocate() before setData().
       *
       * @param values Array of data values [numLocs*numValues].
       * @param numLocs Number of locations.
       * @param numValues Number of values.
       */
      %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
	(const double* values,
	 const size_t numLocs,
	 const size_t numValues)
	  };
      void setData(const double* values,
		   const size_t numLocs,
		const size_t numValues);
      %clear(const double* values, const size_t numLocs, const size_t numValues);
      
      /** Set coordinates of locations.
       *
       * @pre Must call allocate() before setLocations().
       *
       * @param values Array of coordinates of locations [numLocs*spaceDim].
       * @param numLocs Number of locations.
       * @param spaceDim Spatial dimension of coordinates.
       */
      %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
	(const double* values,
	 const size_t numLocs,
	 const size_t spaceDim)
	  };
      void setCoordinates(const double* values,
		       const size_t numLocs,
		       const size_t spaceDim);
      %clear(const double* values, const size_t numLocs, const size_t numValues);
      
      /** Set names of values.
       *
       * @pre Must call allocate() before setNames().
       *
       * @param values Array of names of values [numValues].
       * @param numValues Number of values.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* values, const size_t numValues)
	  };
      void setNames(const char* const* values,
		 const size_t numValues);
      %clear(const char* const* values, const size_t numValues);
      
      /** Set units of values.
       *
       * @pre Must call allocate() before setUnits().
       *
       * @param values Array of units of values [numValues].
       * @param numValues Number of values.
       */
      %apply(const char* const* string_list, const int list_len){
	(const char* const* values, const int numValues)
	  };
      void setUnits(const char* const* values,
		 const int numValues);
      %clear(const char* const* values, const int numValues);
      
      /** Get number of locations for data.
       *
       * @returns Number of locations.
       */
      size_t getNumLocs(void) const;
      
      /** Get number of values for data.
       *
       * @returns Number of values.
       */
      size_t getNumValues(void) const;
      
      /** Get spatial dimension of data distribution.
       *
       * @returns Spatial dimension.
       */
      size_t getDataDim(void) const;
      
      /** Get spatial dimension of locations.
       *
       * @returns Spatial dimension.
       */
      size_t getSpaceDim(void) const;
      
    }; // class SpatialDBData

  } // spatialdb
} // spatialdata


// End of file 
