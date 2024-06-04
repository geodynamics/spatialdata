// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
// SWIG interface
%module geocoords

// Header files for module C++ code
%{
#include <iosfwd>
#include <string> // USES std::string

// Headers for interfaces
#include "spatialdata/geocoords/CoordSys.hh"
#include "spatialdata/geocoords/CSCart.hh"
#include "spatialdata/geocoords/CSGeo.hh"
#include "spatialdata/geocoords/CSGeoLocal.hh"
#include "spatialdata/geocoords/Converter.hh"
%}

%include "exception.i"
%exception {
  try {
    $action
  } catch (const std::exception& err) {
    SWIG_exception(SWIG_RuntimeError, err.what());
  } // try/catch
 } // exception

%include "typemaps.i"

// Numpy interface stuff
%{
#define SWIG_FILE_WITH_INIT
%}
%include "../include/numpy.i"
%init %{
import_array();
%}

// Interfaces
%include "CoordSys.i"
%include "CSCart.i"
%include "CSGeo.i"
%include "CSGeoLocal.i"
%include "Converter.i"

// End of file
