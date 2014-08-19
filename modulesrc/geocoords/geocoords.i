// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

// SWIG interface
%module geocoords

// Header files for module C++ code
%{
#include <iosfwd>
#include <string> // USES std::string
#include "spatialdata/geocoords/proj4fwd.h" // Proj4 forward declaration

// Headers for interfaces
#include "spatialdata/geocoords/CoordSys.hh"
#include "spatialdata/geocoords/CSCart.hh"
#include "spatialdata/geocoords/CSGeo.hh"
#include "spatialdata/geocoords/CSGeoProj.hh"
#include "spatialdata/geocoords/CSGeoLocalCart.hh"

#include "spatialdata/geocoords/Projector.hh"
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
%include "CSGeoProj.i"
%include "CSGeoLocalCart.i"

%include "Projector.i"
%include "Converter.i"

// End of file
