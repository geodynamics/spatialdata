// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

// Define the spatialdatacontrib SWIG interface module.

// Set module name
%module spatialdbcontrib

// Header files for module C++ code.
%{
#include "UniformVelModel.hh"
    %
}

// Convert standard C++ exceptions to Python exceptions.
%include "exception.i"
%exception {
    try {
        $ action
    } catch (const std::exception& err) {
        SWIG_exception (SWIG_RuntimeError, err.what ());
    } // try/catch
} // exception

%include "typemaps.i"
%include "include/chararray.i"

// Numpy interface stuff
%{
#define SWIG_FILE_WITH_INIT
    %
}
%include "include/numpy.i"
%init %{
    import_array();
    %
}

// Interface files.
%include "spatialdb/SpatialDBObj.i"
%include "UniformVelModel.i"

// End of file
