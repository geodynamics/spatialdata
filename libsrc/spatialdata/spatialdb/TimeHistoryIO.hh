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

/** @file libsrc/spatialdb/TimeHistoryIO.h
 *
 * @brief C++ object for reading/writing time history files.
 */

#if !defined(spatialdata_spatialdb_timehistoryio_hh)
#define spatialdata_spatialdb_timehistoryio_hh

#include "spatialdbfwd.hh"

/// C++ object for reading/writing time history files.
class spatialdata::spatialdb::TimeHistoryIO
{ // class TimeHistoryIO

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////
  
  /** Read time history file.
   *
   * @param time Time stamps.
   * @param amplitude Amplitude values in time history.
   * @param npts Number of points in time history.
   * @param filename Filename for time history.
   */
  static
  void read(double** time,
	    double** amplitude,
	    int* npts,
	    const char* filename);
  
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
  static
  void write(const double* time,
	     const int nptsT,
	     const double* amplitude,
	     const int nptsA,
	     const char* timeUnits,
	     const char* filename);

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  static const char* HEADER; ///< Header for time history files.
  
}; // class TimeHistoryIO

#endif // spatialdata_spatialdb_timehistoryio_hh


// End of file 
