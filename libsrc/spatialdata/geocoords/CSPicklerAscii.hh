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

#include "geocoordsfwd.hh"

#include <iosfwd> // USES std::istream, std::ostream

class spatialdata::geocoords::CSPicklerAscii {
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /** Pickle coordinate system.
     *
     * @param s Ouput stream
     * @param cs Pointer to coordinate system
     */
    static
    void pickle(std::ostream& s,
                const CoordSys* cs);

    /** Unpickle coordinate system.
     *
     * @param s Input stream
     * @param cs Pointer to pointer to coordinate system
     */
    static
    void unpickle(std::istream& s,
                  CoordSys** cs);

}; // class CSPicklerAscii

// End of file
