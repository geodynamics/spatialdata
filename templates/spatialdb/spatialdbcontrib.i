// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

// Define the spatialdatacontrib SWIG interface module.

// Set module name
%module spatialdbcontrib

// Header files for module C++ code.
%{
#include "UniformVelModel.hh"
%}

// Convert standard C++ exceptions to Python exceptions.
%include "exception.i"
%exception {
  try {
    $action
  } catch (const std::exception& err) {
    SWIG_exception(SWIG_RuntimeError, err.what());
  } // try/catch
} // exception

%include "typemaps.i"
%include "spatialdata/swig/chararray.i"

// Numpy interface stuff
%{
#define SWIG_FILE_WITH_INIT
%}
%include "spatialdata/swig/numpy.i"
%init %{
import_array();
%}


// Interface files.
%include "spatialdata/spatialdb/swig/SpatialDBObj.i"
%include "UniformVelModel.i"


// End of file
