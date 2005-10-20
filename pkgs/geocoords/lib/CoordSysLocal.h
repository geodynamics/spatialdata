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

/** @file pkgs/geocoords/lib/CoordSysLocal.h
 *
 * @brief C++ CoordSysLocal object
 *
 * C++ object for defining a local cartesian coordinate system.
 */

#if !defined(spatialdata_geocoords_coordsyslocal_h)
#define spatialdata_geocoords_coordsyslocal_h

namespace spatialdata {
  namespace geocoords {
    class CoordSysLocal;
    class testCoordsysLoc; // forward declaration
  } // geocoords
} // spatialdata

/// C++ object for defining a local cartesian coordinate system
class spatialdata::geocoords::CoordSysLocal : public CoordSys
{ // class CoordSysLocal
  friend class TestCoordSysLocal;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Default constructor
   *
   * @param cs Source coordinate system
   */
  CoordSysLocal(void);

  /// Default destructor
  ~CoordSysLocal(void);

  /** Set origin of local cartesian coordinate system.
   *
   * @param lon Longitude of origin (degrees)
   * @param lat Latitude of origin (degrees)
   * @param elev Elevation (wrt vertical datum) of origin (meters)
   * @param ellipsoid Name of reference ellipsoid
   * @param datumHoriz Name of horizontal datum
   * @param datumVert Name of vertical datum
   */
  void localOrigin(const double lon,
		   const double lat,
		   const double elev,
		   const std::string& ellipsoid,
		   const std::string& datumHoriz,
		   const std::string& datumVert);

  /** Get vertical datum.
   *
   * @returns Name of datum
   */
  const char* datumVert(void) const;

  /** Set factor to convert coordinates to meters.
   *
   * @param factor Factor to convert coordinates to meters.
   */
  void xyzToMeters(const double factor);

  /** Get factor to convert elevation to meters.
   *
   * @returns Factor to convert elevation to meters.
   */
  double elevToMeters(void) const;

  /** Get proj form vertical datum.
   *
   * @returns Name of datum
   */
  const char* projDatumVert(void) const;

  /** Convert coordinates to PROJ4 useable form.
   *
   * @param ppCoords Pointer to array of coordinates [#locs*3]
   * @param numLocs Number of locations
   * @param is2D True if coordinates are 2D, false if 3D
   */
  void toProjForm(double** ppCoords,
		  const int numLocs,
		  bool is2D =false) const;
  
  /** Convert coordinates from PROJ4 form to form associated w/coordsys.
   *
   * @param ppCoords Pointer to array of coordinates [#locs*3]
   * @param numLocs Number of locations
   * @param is2D True if coordinates are 2D, false if 3D
   */
  void fromProjForm(double** ppCoords,
		    const int numLocs,
		    bool is2D =false) const;
  
protected :
  // PROTECTED METHODS /////////////////////////////////////////////////

  /** Get the PROJ4 string associated with the coordinate system.
   *
   * @returns string
   */
  std::string _projCSString(void) const;
  
private :
  // PRIVATE METHODS ///////////////////////////////////////////////////

  /** Convert coordinates to WGS84.
   *
   * @param pLonWGS84 Pointer to longitude in WGS84
   * @param pLatWGS84 Pointer to latitude in WGS84
   * @param lon Longitude in original coordinate system in radians
   * @param lat Latitude in original coordinate system in radians
   * @param ellipsoid Name of reference ellipsoid
   * @param datumHoriz Name of horizontal datum
   */
  void _geoToWGS84(double* pLonWGS84,
		   double* pLatWGS84,
		   const double lon,
		   const double lat,
		   const char* ellipsoid,
		   const char* datumHoriz) const;
  
  /** Convert coordinates from WGS84 to ECEF.
   *
   * @param pECEFX Pointer to ECEF X coordinate
   * @param pECEFY Pointer to ECEF Y coordinate
   * @param pECEFZ Pointer to ECEF Z coordinate
   * @param lonWGS84 Longitude in WGS84 in radians
   * @param latWGS84 Latitude in WGS84 in radians
   * @param elevWGS84 Elevation wrt WGS84 ellipsoid
   */
  void _wgs84ToECEF(double* pECEFX,
		    double* pECEFY,
		    double* pECEFZ,
		    const double lonWGS84,
		    const double latWGS84,
		    const double elevWGS84) const;

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _originLon; ///< Longitude of origin
  double _originLat; ///< Latitude of origin
  double _originElev; ///< Elevation of origin
  double _originX; ///< X coordinate of origin in rotated ECEF
  double _originY; ///< Y coordinate of origin in rotated ECEF
  double _originZ; ///< Z coordinate of origin in rotated ECEF
  double _xyzToMeters; ///< Factor to convert coordinates to meters
  double* _localOrientation; ///< Direction cosines for local orientation 
  std::string _ellipsoid; ///< Name of reference ellipsoid
  std::string _datumHoriz; ///< Name of horizontal geographic datum
  std::string _datumVert; ///< Name of vertical datum

}; // class CoordSysLocal

#include "CoordSysLocal.icc" // inline methods

#endif // spatialdata_geocoords_coordsyslocal_h

// version
// $Id$

// End of file 
