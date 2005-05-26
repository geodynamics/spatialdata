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

/** @file pkgs/geocoords/lib/GeoCoordSys.h
 *
 * @brief C++ GeoCoordSys object
 *
 * C++ object for managing parameters defining a coordinate system.
 */

#if !defined(spatialdata_geocoordsys_h)
#define spatialdata_geocoordsys_h

namespace spatialdata {
  class GeoCoordSys;
  bool operator==(const GeoCoordSys&,
		  const GeoCoordSys&); // forward declaration
}; // namespace spatialdata

#include "proj4fwd.h" // Proj4 forward declaration

/// C++ object for managing parameters defining a coordinate system
class spatialdata::GeoCoordSys
{ // class GeoCoordSys
 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  GeoCoordSys(void);

  /// Default destructor
  ~GeoCoordSys(void);

  /** Copy constructor.
   *
   * @param cs Coordinate system to copy
   */
  GeoCoordSys(const GeoCoordSys& cs);

  /** operator=
   *
   * @param cs Coordinate system to copy
   *
   * @param returns Reference to this
   */
  const GeoCoordSys& operator=(const GeoCoordSys& cs);  

  /** Set projection.
   *
   * @param projection Name of projection
   */
  void projection(const char* name);

  /** Get name of projection.
   *
   * @returns Name of projection
   */
  const char* projection(void) const;

  /** Set reference ellipsoid.
   *
   * @param name Name of reference ellipsoid
   */
  void ellipsoid(const char* name);

  /** Get reference ellipsoid.
   *
   * @returns Name of reference ellipsoid
   */
  const char* ellipsoid(void) const;

  /** Set datum.
   *
   * @param name Name of datum
   */
  void datum(const char* name);

  /** Get datum.
   *
   * @returns Name of datum
   */
  const char* datum(void) const;

  /** Set units of coordinate system.
   *
   * @param name Name of units
   */
  void units(const char* name);

  /** Get units of coordinate system.
   *
   * @returns Name of units
   */
  const char* units(void) const;

  /// Initialize projector.
  void initialize(void);

  /** Get coordinate system.
   *
   * @returns Coordinate system
   */
  const projPJ coordsys(void) const;

  /** Are coordinate systems the same?
   *
   * @returns True if coordinate systems are the same, false otherwise
   */
  friend bool spatialdata::operator==(const GeoCoordSys& a,
				      const GeoCoordSys& b);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  const char* _projection; ///< Name of projection
  const char* _ellipsoid; ///< Name of reference ellipsoid
  const char* _datum; ///< Name of geographic datum
  const char* _units; ///< Name of units in projection
  
  projPJ _pCS; ///< Pointer to coordinate system
  
}; // class GeoCoordSys

#include "GeoCoordSys.icc" // inline methods

#endif // spatialdata_geocoordsys_h

// version
// $Id: GeoCoordSys.h,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
