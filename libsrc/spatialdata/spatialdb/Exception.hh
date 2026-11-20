// -*- c++ -*-
// -*- coding: utf-8 -*-
//
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2026 The SpatialData authors and contributors
// SPDX-License-Identifier: MIT


#pragma once

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

// version
// $Id$


// End of file
