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

/** @file pkgs/geocoords/lib/GeoLocalConverter.h
 *
 * @brief C++ GeoLocalConverter object
 *
 * C++ object for converting between geographic coordinate systems and
 * a local cartesian coordinate system.
 */

#if !defined(spatialdata_geolocalconverter_h)
#define spatialdata_geolocalconverter_h

namespace spatialdata {
  class GeoLocalConverter;
  class GeoCoordSys; // forward declaration
  class TestGeoLocalConverter; // regression testing
}; // namespace spatialdata

/// C++ object for converting between geographic coordinate systems
/// and a local cartesian coordinate system
class spatialdata::GeoLocalConverter
{ // class GeoLocalConverter
  friend class TestGeoLocalConverter;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Default constructor
   *
   * @param cs Source coordinate system
   */
  GeoLocalConverter(const GeoCoordSys& cs);

  /// Default destructor
  ~GeoLocalConverter(void);

  /** Set origin of local cartesian coordinate system.
   *
   * @param lon Longitude of origin (degrees)
   * @param lat Latitude of origin (degrees)
   * @param elev Elevation (wrt mean sea level) of origin (meters)
   * @param coordsys Coordinate system
   */
  void localOrigin(const double lon,
		   const double lat,
		   const double elev);

  /** Convert coordinates from geographic coordinate system to local
   * cartesian coordinate system.
   *
   * @param ppDest Pointer to array of destination locations
   * @param numLocs Number of locations
   * @param elevToMeters Factor to multiply by to convert elev to meters
   * @param invert Invert conversion for local to geo coordinate conversion
   */
  void convert(double** ppDest,
	       const int numLocs,
	       const double elevToMeters =1.0,
	       const bool invert =false) const;

private :
 // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Convert geographic coordinates to lat/lon with WGS64 datum and
   *  ellipsoid.
   *
   * @warning Transformed coordinates replace original coordinates
   *
   * @param ppCoords Pointer to array of destination locations
   * @param numLocs Number of locations
   * @param pCS Pointer to current coordinate system
   * @param invert Invert conversion for local to geo coordinate conversion
   */
  void _geoToWGS84(double** const ppCoords,
		   const int numLocs,
		   GeoCoordSys* pCS,
		   const bool invert =false) const;

  /** Convert elevation to height above WGS84 reference ellipsoid
   *
   * @warning Transformed coordinates replace original coordinates
   *
   * @param ppCoords Pointer to array of destination locations
   * @param numLocs Number of locations
   * @param pCS Pointer to current coordinate system
   * @param invert Invert conversion for local to geo coordinate conversion
   */
  void _elevToGeoidHt(double** const ppCoords,
		      const int numLocs,
		      GeoCoordSys* pCS,
		      const bool invert =false) const;

  /** Convert geographic coordinates in lat/lon with WGS64 datum and
   *  ellipsoid to ECEF cartesian coordinates.
   *
   * @warning Transformed coordinates replace original coordinates
   *
   * @param ppCoords Pointer to array of destination locations
   * @param numLocs Number of locations
   * @param pCS Pointer to current coordinate system
   * @param invert Invert conversion for local to geo coordinate conversion
   */
  void _wgs84ToECEF(double** const ppCoords,
		    const int numLocs,
		    GeoCoordSys* pCS,
		    const bool invert =false) const;

  /** Convert ECEF cartesian coordinates to local cartesian coordinates.
   *
   * @warning Transformed coordinates replace original coordinates
   *
   * @param ppCoords Pointer to array of destination locations
   * @param numLocs Number of locations
   * @param pCS Pointer to current coordinate system
   * @param invert Invert conversion for local to geo coordinate conversion
   */
  void _ecefToLocal(double** const ppCoords,
		    const int numLocs,
		    GeoCoordSys* pCS,
		    const bool invert =false) const;

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _originLon; ///< Longitude of origin
  double _originLat; ///< Latitude of origin
  double _originElev; ///< Elevation of origin
  double _originX; ///< X coordinate of origin in rotated ECEF
  double _originY; ///< Y coordinate of origin in rotated ECEF
  double _originZ; ///< Z coordinate of origin in rotated ECEF
  double* _localOrientation; ///< Direction cosines for local orientation 
  const GeoCoordSys& _csSrc; ///< Source coordinate system

}; // class GeoLocalConverter

#endif // spatialdata_geolocalconverter_h

// version
// $Id: GeoLocalConverter.h,v 1.3 2005/06/02 21:35:01 baagaard Exp $

// End of file 
