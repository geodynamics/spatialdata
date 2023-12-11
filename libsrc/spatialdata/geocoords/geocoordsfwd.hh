// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file libsrc/geocoords/geocoordsfwd.hh
 *
 * @brief Forward declarations for spatialdata::geocoords objects.
 *
 * Including this header file eliminates the need to use separate
 * forward declarations.
 */

#if !defined(spatialdata_geocoords_geocoordsfwd_hh)
#define spatialdata_geocoords_geocoordsfwd_hh

namespace spatialdata {
    namespace geocoords {
        class CoordSys;
        class CSCart;
        class CSGeo;
        class CSGeoLocal;
        class Converter;
        class CSPicklerAscii;
    } // geocoords
} // spatialdata

#endif // spatialdata_geocoords_geocoordsfwd_hh

// End of file
