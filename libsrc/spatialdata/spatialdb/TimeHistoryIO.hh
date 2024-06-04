// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "spatialdbfwd.hh"

#include <cstdlib> // USES size_t

/// C++ object for reading/writing time history files.
class spatialdata::spatialdb::TimeHistoryIO { // class TimeHistoryIO
public:

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
              size_t* npts,
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
               const size_t nptsT,
               const double* amplitude,
               const size_t nptsA,
               const char* timeUnits,
               const char* filename);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    static const char* HEADER; ///< Header for time history files.

}; // class TimeHistoryIO

// End of file
