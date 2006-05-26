// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/Exception.hh
 *
 * @brief C++ exceptions for spatial database.
 */

#if !defined(spatialdata_spatialdb_exception_hh)
#define spatialdata_spatialdb_exception_hh

#include <stdexcept> // ISA std::runtime_error

namespace spatialdata {
  namespace spatialdb {
    class OutOfBounds;
  } // spatialdb
} // spatialdata

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
