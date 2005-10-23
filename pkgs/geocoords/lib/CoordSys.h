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

/** @file pkgs/geocoords/lib/CoordSys.h
 *
 * @brief C++ CoordSys object
 *
 * C++ object for managing parameters defining a coordinate system.
 */

#if !defined(spatialdata_geocoords_coordsys_h)
#define spatialdata_geocoords_coordsys_h

namespace spatialdata {
  namespace geocoords {
    class CoordSys;
  } // geocoords
} // spatialdata

/// C++ object for managing parameters defining a coordinate system
class spatialdata::geocoords::CoordSys
{ // class CoordSys
public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Type of coordinate system
  enum CSTypeEnum {
    CARTESIAN, ///< Cartesian coordinate system
    GEOGRAPHIC ///< Geographic coordinate system
  };

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  CoordSys(void);

  /// Default destructor
  virtual ~CoordSys(void);

  /// Initialize the coordinate system.
  virtual void initialize(void) = 0;

  /// Get type of coordinate system
  CSTypeEnum csType(void) const;

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Set type of coordinate system.
   *
   * @param cs Type of coordinate system
   */
  void csType(const CSTypeEnum cs);

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  CSTypeEnum _csType; ///< Type of coordinate system

}; // class CoordSys

#include "CoordSys.icc" // inline methods

#endif // spatialdata_geocoords_coordsys_h

// version
// $Id$

// End of file 
