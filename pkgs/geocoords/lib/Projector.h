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

/** @file pkgs/geocoords/lib/Projector.h
 *
 * @brief C++ Projector object
 *
 * C++ object for projecting to/from geographic projections.
 */

#if !defined(spatialdata_projector_h)
#define spatialdata_projector_h

namespace spatialdata {
  class Projector;
}; // namespace spatialdata

#include "proj4fwd.h" // Proj4 forward declaration

/// C++ object for projecting to/from geographic projections
class spatialdata::Projector
{ // class Projector

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  Projector(void);

  /// Default destructor
  ~Projector(void);

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

  /** Set units of projection.
   *
   * @param name Name of units
   */
  void units(const char* name);

  /** Get units of projection.
   *
   * @returns Name of units
   */
  const char* units(void) const;

  /// Initialize projector.
  void initialize(void);

  /** Project geographic coordinates.
   *
   * @param pX Pointer to x coordinate of location (output)
   * @param pY Pointer to y coordinate of location (output)
   * @param lon Longitude of location
   * @param lat Latitude of location
   */
  void project(double* pX,
	       double* pY,
	       const double lon,
	       const double lat);

  /** Get geographic coordinates of projected location.
   *
   * @param pLon Pointer to longitude of location (output)
   * @param pLat Pointer to latitude of location (output)
   * @param x X coordinate of location
   * @param y Y coordinate of location
   */
  void invproject(double* pLon,
		  double* pLat,
		  const double x,
		  const double y);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  const char* _projection; ///< Name of projection
  const char* _ellipsoid; ///< Name of reference ellipsoid
  const char* _datum; ///< Name of geographic datum
  const char* _units; ///< Name of units in projection
  
  projPJ _pProj; ///< Pointer to projection
  
}; // class Projector

#include "Projector.icc" // inline methods

#endif // spatialdata_projector_h

// version
// $Id: Projector.h,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
