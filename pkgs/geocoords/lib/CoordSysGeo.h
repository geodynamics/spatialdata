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

/** @file pkgs/geocoords/lib/CoordSysGeo.h
 *
 * @brief C++ CoordSysGeo object
 *
 * C++ object for managing parameters defining geographic coordinate systems.
 */

#if !defined(spatialdata_geocoords_coordsysgeo_h)
#define spatialdata_geocoords_coordsysgeo_h

namespace spatialdata {
  namespace geocoords {
    class CoordSysGeo;
    class TestCoordSysGeo; // forward declaration
  } // geocoords
} // spatialdata

#include "proj4fwd.h" // Proj4 forward declaration

/// C++ object for managing parameters defining geographic coordinate systems
class spatialdata::geocoords::CoordSysGeo : public CoordSys
{ // class CoordSysGeo
  friend class TestCoordSysGeo;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  CoordSysGeo(void);

  /// Default destructor
  ~CoordSysGeo(void);

  /** Set reference ellipsoid.
   *
   * @param name Name of reference ellipsoid
   */
  void ellipsoid(const std::string& name);

  /** Get reference ellipsoid.
   *
   * @returns Name of reference ellipsoid
   */
  const char* ellipsoid(void) const;

  /** Set horizontal datum.
   *
   * @param name Name of horizontal datum
   */
  void datumHoriz(const std::string& name);

  /** Get horizontal datum.
   *
   * @returns Name of datum
   */
  const char* datumHoriz(void) const;

  /** Set vertical datum.
   *
   * @param name Name of vertical datum
   */
  void datumVert(const std::string& name);

  /** Get vertical datum.
   *
   * @returns Name of datum
   */
  const char* datumVert(void) const;

  /** Set geocentric flag.
   *
   * @param geocentric True if geocentric, false if lon/lat
   */
  void isGeocentric(bool geocentric);

  /** Get geocentric flag.
   *
   * @returns True if geocentric, false if lon/lat
   */
  bool isGeocentric(void) const;

  /** Set factor to convert elevation to meters.
   *
   * @param factor Factor to convert elevation to meters.
   */
  void elevToMeters(const double factor);

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
		  bool is2D) const;
  
  /** Convert coordinates from PROJ4 form to form associated w/coordsys.
   *
   * @param ppCoords Pointer to array of coordinates [#locs*3]
   * @param numLocs Number of locations
   * @param is2D True if coordinates are 2D, false if 3D
   */
  void fromProjForm(double** ppCoords,
		    const int numLocs,
		    bool is2D) const;
  
protected :
  // PROTECTED MEMBERS /////////////////////////////////////////////////

  /** Get the PROJ4 string associated with the coordinate system.
   *
   * @returns string
   */
  std::string _projCSString(void) const;
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _elevToMeters; ///< Factor to convert elevation to meters
  std::string _ellipsoid; ///< Name of reference ellipsoid
  std::string _datumHoriz; ///< Name of horizontal geographic datum
  std::string _datumVert; ///< Name of vertical datum
  bool _isGeocentric; ///< True if geocentric, false if lat/lon
  
}; // class CoordSysGeo

#include "CoordSysGeo.icc" // inline methods

#endif // spatialdata_geocoodrs_coordsysgeo_h

// version
// $Id$

// End of file 
