// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

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
        class AnalyticDB;
        class SimpleGridDB;
        class SimpleGridAscii;
        class UserFunctionDB;
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
