// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

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
#include "spatialdata/spatialdb/SimpleGridDB.hh"
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
%include "SimpleGridDB.i"
%include "CompositeDB.i"
%include "SCECCVMH.i"
%include "GravityField.i"
%include "TimeHistory.i"
%include "TimeHistoryIO.i"


// End of file
