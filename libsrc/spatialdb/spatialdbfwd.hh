// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/spatialdbfwd.hh
 *
 * @brief Forward declarations for spatialdata::spatialdb objects.
 *
 * Including this header file eliminates the need to use separate
 * forward declarations.
 */

#if !defined(spatialdata_spatialdb_spatialdbfwd_hh)
#define spatialdata_spatialdb_spatialdbfwd_hh

namespace spatialdata {
  namespace spatialdb {
    class OutOfBounds;

    class SpatialDB;
    class SimpleDB;
    class SimpleDBData;
    class SimpleDBQuery;
    class SimpleIO;
    class SimpleIOAscii;
    class UniformDB;
    class CompositeDB;
    class SCECCVMH;
    class GocadVoxet;

    class GravityField;

    class TimeHistory;
    class TimeHistoryIO;
    
  } // spatialdb
} // spatialdata


#endif // spatialdata_spatialdb_spatialdbfwd_hh


// End of file 
