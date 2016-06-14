// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

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
	(const double* time,
	 const int nptsT)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* amplitude,
	 const int nptsA)
	  };
      static
      void write(const double* time,
		 const int nptsT,
		 const double* amplitude,
		 const int nptsA,
		 const char* timeUnits,
		 const char* filename);
      %clear(const double* time, const int nptsT);
      %clear(const double* amplitude, const int nptsA);

    }; // class TimeHistoryIO

  } // spatialdb
} // spatialdata


// End of file 
