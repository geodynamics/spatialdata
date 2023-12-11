// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file libsrc/spatialdb/Exception.hh
 *
 * @brief C++ exceptions for spatial database.
 */

#if !defined(spatialdata_spatialdb_exception_hh)
#define spatialdata_spatialdb_exception_hh

#include "spatialdbfwd.hh" // forward declarations

#include <stdexcept> // ISA std::runtime_error

/// C++ exceptions for spatial database.
class spatialdata::spatialdb::OutOfBounds : public std::runtime_error { // class OutOfBounds
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /** Constructor.
     *
     * @msg Error message
     */
    OutOfBounds(const std::string& msg);

}; // class OutOfBounds

#include "Exception.icc" // inline methods

#endif // spatialdata_spatialdb_exception_hh

// version
// $Id$

// End of file
