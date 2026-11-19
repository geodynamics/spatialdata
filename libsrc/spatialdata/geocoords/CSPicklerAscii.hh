// -*- c++ -*-
// -*- coding: utf-8 -*-
//
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2026 The SpatialData authors and contributors
// SPDX-License-Identifier: MIT


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
    static void pickle(std::ostream& s,
                       const CoordSys* cs);

    /** Unpickle coordinate system.
     *
     * @param s Input stream
     * @param cs Pointer to pointer to coordinate system
     */
    static void unpickle(std::istream& s,
                         CoordSys** cs);

}; // class CSPicklerAscii


// End of file
