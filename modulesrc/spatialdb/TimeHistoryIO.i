// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/spatialdb/TimeHistory.i
 *
 * @brief SWIG interface to C++ TimeHistory object.
 */

namespace spatialdata {
  namespace spatialdb {

    class TimeHistoryIO
    { // class TimeHistoryIO

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////
  
      /** Read time history file. Number of time history points given by
       * nptsT must equal nptsA.
       *
       * @param time Time stamps.
       * @param nptsT Number of points in time history.
       * @param amplitude Amplitude values in time history.
       * @param nptsA Number of points in time history.
       * @param timeUnits Units associated with time stamps.
       * @param filename Filename for time history.
       */
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* time, const size_t nptsT)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* amplitude, const size_t nptsA)
	  };
      static
      void write(const double* time,
		 const size_t nptsT,
		 const double* amplitude,
		 const size_t nptsA,
		 const char* timeUnits,
		 const char* filename);
      %clear(const double* time, const size_t nptsT);
      %clear(const double* amplitude, const size_t nptsA);

    }; // class TimeHistoryIO

  } // spatialdb
} // spatialdata


// End of file 
