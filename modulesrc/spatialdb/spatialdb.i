// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

// SWIG interface
%module spatialdb

// Header files for module C++ code
%{
#include <iosfwd>
#include <string> // USES std::string

#include "spatialdata/geocoords/CoordSys.hh"

#include "spatialdata/spatialdb/SpatialDB.hh"
#include "spatialdata/spatialdb/SimpleDB.hh"
#include "spatialdata/spatialdb/SimpleDBData.hh"
#include "spatialdata/spatialdb/SimpleIO.hh"
#include "spatialdata/spatialdb/SimpleIOAscii.hh"
#include "spatialdata/spatialdb/UniformDB.hh"
#include "spatialdata/spatialdb/AnalyticDB.hh"
#include "spatialdata/spatialdb/SimpleGridDB.hh"
#include "spatialdata/spatialdb/SimpleGridAscii.hh"
#include "spatialdata/spatialdb/UserFunctionDB.hh"
#include "spatialdata/spatialdb/CompositeDB.hh"
#include "spatialdata/spatialdb/SCECCVMH.hh"
#include "spatialdata/spatialdb/GravityField.hh"
#include "spatialdata/spatialdb/TimeHistory.hh"
#include "spatialdata/spatialdb/TimeHistoryIO.hh"

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
%include "../include/chararray.i"

// Numpy interface stuff
%{
#define SWIG_FILE_WITH_INIT
%}
%include "../include/numpy.i"
%init %{
import_array();
%}

// Interfaces

%include "SpatialDBObj.i"
%include "SimpleDB.i"
%include "SimpleDBData.i"
%include "SimpleIO.i"
%include "SimpleIOAscii.i"
%include "UniformDB.i"
%include "AnalyticDB.i"
%include "SimpleGridDB.i"
%include "SimpleGridAscii.i"
%include "UserFunctionDB.i"
%include "CompositeDB.i"
%include "SCECCVMH.i"
%include "GravityField.i"
%include "TimeHistory.i"
%include "TimeHistoryIO.i"


// End of file
