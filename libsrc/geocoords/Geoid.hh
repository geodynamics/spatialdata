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

/** @file libsrc/geocoords/Geoid.hh
 *
 * @brief C++ Geoid object
 *
 * C++ object for converting difference between elevation relative to
 * mean seal level (MSL) and elevation relative to WGS ellipsoid.
 */

#if !defined(spatialdata_geocoords_geoid_hh)
#define spatialdata_geocoords_geoid_hh

#include "geocoordsfwd.hh"

#include <inttypes.h>

/// C++ object for converting difference between elevation relative to
/// mean seal level (MSL) and elevation relative to WGS ellipsoid.
class spatialdata::geocoords::Geoid
{ // class Geoid

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  Geoid(void);

  /// Default destructor
  ~Geoid(void);

  /// Initialize
  void initialize(void);

  /** Compute elevation with respect to WGS ellipsoid relative to
   *  elevation with respect to MSL.
   *
   * To convert from elevation wrt MSL to elevation wrt WGS ellipsoid,
   * add return value to elevation wrt MSL.
   *
   * @param lon Longitude in radians in WGS84 datum
   * @param lat Latitude in radians in WGS84 datum
   *
   * @returns Different in elevation b/t MSL and WGS84 ellipsoid
   */
  double elevation(const double lon,
		   const double lat) const;

private :
 // PRIVATE METHODS ////////////////////////////////////////////////////
  
  /// Read grid values.
  void _readGrid(void);

  /** Interpolate using 1-D spline.
   *
   * @param coord Coordinate along spline
   * @param pVals Array of values
   * @param pMoments Array of moments
   *
   * @returns Value at coordinate
   */
  double _splineInterp(const double coord,
		       const double* pVals,
		       const double* pMoments) const;

  /** Compute the spline moments.
   *
   * @param pMom Array of moments
   * @param pVals Array of values
   */
  void _splineMoments(double* pMom,
		      const double* pVals) const;

  /** Compute fraction index.
   *
   * @param Value 
   *
   * @returns Fraction index
   */
  int _splineFrac(const double value) const;

  /** Convert array of int16_t values from big endian to native int16_t type.
   *
   * @param ppVals Pointer to array of values
   * @param numVals Number of values
   */
  static void _endianBigToNative(int16_t** ppVals,
				 const int numVals);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double* _pGridVals; ///< 2D array of grid values

  bool _initialized; ///< Flag to indicate object has been initialized

  static const double _south; ///< South limit of grid (radians)
  static const double _north; ///< North limit of grid (radians)
  static const double _east; ///< East limit of grid (radians)
  static const double _west; ///< West limit of grid (radians)
  static const double _dLat; ///< Grid interval in latitude (radians)
  static const double _dLon; ///< Grid interval in longitude (radians)

  static const int _numGridEW; ///< Number of grid values in east-west dir
  static const int _numGridNS; ///< Number of grid values in north-south dir
  static const int _numInterp; ///< Number of grid points in interpolation
  static const int _numExtraEdge; ///< Number of extra grid points on ew edges
  static const char* _filename; ///< Filename holding grid values

}; // class Geoid

#include "Geoid.icc" // inline methods

#endif // spatialdata_geocoords_geoid_hh


// End of file 
