// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file libsrc/muparser/muparserfwd.hh
 *
 * @brief Forward declarations for mu::parser object.
 *
 * Including this header file eliminates the need to use separate
 * forward declarations.
 */

#if !defined(spatialdata_muparser_muparserfwd_hh)
#define spatialdata_muparser_muparserfwd_hh

#define MUP_BASETYPE double

namespace mu {
    class Parser;

    typedef MUP_BASETYPE value_type;

} // mu

#endif // spatialdata_muparser_muparserfwd_hh

// End of file
