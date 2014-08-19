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

/** @file libsrc/spatialdb/Exception.hh
 *
 * @brief C++ exceptions for spatial database.
 */

#if !defined(spatialdata_spatialdb_exception_hh)
#define spatialdata_spatialdb_exception_hh

#include "spatialdbfwd.hh" // forward declarations

#include <stdexcept> // ISA std::runtime_error

/// C++ exceptions for spatial database.
class spatialdata::spatialdb::OutOfBounds : public std::runtime_error
{ // class OutOfBounds

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////
  
  /** Constructor.
   *
   * @msg Error message
   */
  OutOfBounds(const std::string& msg);
  
}; // class OutOfBounds

#include "Exception.icc" // inline methods

#endif // spatialdata_spatialdb_exception_hh

// version
// $Id$

// End of file 
