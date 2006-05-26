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

/** @file libsrc/geocoords/GeoCoordSys.hh
 *
 * @brief C++ GeoCoordSys object
 *
 * C++ object for managing parameters defining a coordinate system.
 */

#if !defined(spatialdata_geocoordsys_hh)
#define spatialdata_geocoordsys_hh

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

  /** Set horizontal datum.
   *
   * @param name Name of horizontal datum
   */
  void datumHoriz(const char* name);

  /** Get horizontal datum.
   *
   * @returns Name of datum
   */
  const char* datumHoriz(void) const;

  /** Set vertical datum.
   *
   * @param name Name of vertical datum
   */
  void datumVert(const char* name);

  /** Get horizontal datum.
   *
   * @returns Name of datum
   */
  const char* datumVert(void) const;

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
  const char* _datumHoriz; ///< Name of horizontal geographic datum
  const char* _datumVert; ///< Name of vertical datum
  const char* _units; ///< Name of units in projection
  
  projPJ _pCS; ///< Pointer to coordinate system
  
}; // class GeoCoordSys

#include "GeoCoordSys.icc" // inline methods

#endif // spatialdata_geocoordsys_hh

// version
// $Id$

// End of file 
