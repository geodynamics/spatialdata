// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "unitsfwd.hh"

#include <Python.h>

/// C++ interface to Pyre units parser.
class spatialdata::units::Parser { // class Parser
    friend class TestParser; // Unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /* MATT- I am not sure if we want just a single static method or we
     *   want an object so that any setup/teardown is done once per
     *   instantiation rather than each call to parse.
     */

    /// Default constructor
    Parser(void);

    /// Default destructor
    ~Parser(void);

    /** Get SI scaling factor for units given by string. To get value in
     * SI units, multiple value given by units by scaling factor.
     *
     * @returns Scaling factor to convert to SI units.
     */
    double parse(const char* units);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    PyObject* _parser;
    bool _alreadyInitialized;

}; // class Parser

// End of file
