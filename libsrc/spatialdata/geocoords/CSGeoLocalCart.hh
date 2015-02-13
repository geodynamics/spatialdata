// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/geocoords/CSGeoLocalCart.hh
 *
 * @brief C++ CSGeoLocalCart object
 *
 * C++ object for defining a local cartesian coordinate system.
 */

#if !defined(spatialdata_geocoords_csgeolocalcart_hh)
#define spatialdata_geocoords_csgeolocalcart_hh

#include "CSGeo.hh" // ISA CSGeo

/// C++ object for defining a local cartesian coordinate system
class spatialdata::geocoords::CSGeoLocalCart : public CSGeo
{ // class CSGeoLocalCart
  friend class TestCSGeoLocalCart;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Default constructor
   *
   * @param cs Source coordinate system
   */
  CSGeoLocalCart(void);

  /// Default destructor
  ~CSGeoLocalCart(void);

  /** Clone coordinate system.
   *
   * @returns Pointer to copy
   */
  virtual CoordSys* clone(void) const;

  /// Initialize the coordinate system.
  void initialize(void);

  /** Set origin of local cartesian coordinate system.
   *
   * Units of elevation should be consistent with conversion factor to
   * meters.
   *
   * @param lon Longitude of origin (degrees)
   * @param lat Latitude of origin (degrees)
   * @param elev Elevation (wrt vertical datum) of origin
   */
  void origin(const double lon,
	      const double lat,
	      const double elev);

  /** Get origin of local cartesian coordinate system.
   *
   * @param pLon Pointer to longitude of origin (degrees)
   * @param pLat Pointer to latitude of origin (degrees)
   * @param pElev Pointer to elevation (wrt vertical datum) of origin
   */
  void origin(double* pLon,
	      double* pLat,
	      double* pElev);

  /** Get proj form vertical datum.
   *
   * @returns Name of datum
   */
  const char* projDatumVert(void) const;

  /** Convert coordinates to PROJ4 useable form.
   *
   * @param coords Array of coordinates [numLocs*numDims]
   * @param numLocs Number of locations
   * @param numDims Number of spatial dimensions
   */
  void toProjForm(double* coords,
		  const int numLocs,
		  const int numDims) const;
  
  /** Convert coordinates from PROJ4 form to form associated w/coordsys.
   *
   * @param coords Array of coordinates [numLocs*numDims]
   * @param numLocs Number of locations
   * @param numDims Number of spatial dimensions
   */
  void fromProjForm(double* coords,
		    const int numLocs,
		    const int numDims) const;
  
  /** Get radial outward direction.
   *
   * dir and coords
   *   size = numLocs * numDims
   *   index = iLoc*numDims + iDim
   *
   * @param dir Array of direction cosines for outward radial direction.
   * @param coords Array of coordinates for locations.
   * @param numLocs Number of locations.
   * @param numDims Number of dimensions in coordinates.
   */
  void radialDir(double* dir,
		 const double* coords,
		 const int numLocs,
		 const int numDims) const;

  /** Pickle coordinate system to ascii stream.
   *
   * @param s Output stream
   */
  virtual void pickle(std::ostream& s) const;

  /** Unpickle coordinate system from ascii stream.
   *
   * @param s Input stream
   */
  virtual void unpickle(std::istream& s);

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Copy constructor
   *
   * @param cs Coordinate system to copy
   */
  CSGeoLocalCart(const CSGeoLocalCart& cs);

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
  // PRIVATE METHODS ///////////////////////////////////////////////////

  void isGecentric(const bool isGeocentric); ///< Not implemented
  void setSpaceDim(const int dim); ///< Not implemented

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _originLon; ///< Longitude of origin
  double _originLat; ///< Latitude of origin
  double _originElev; ///< Elevation of origin

  double _originX; ///< X coordinate of origin in rotated ECEF (meters)
  double _originY; ///< Y coordinate of origin in rotated ECEF (meters)
  double _originZ; ///< Z coordinate of origin in rotated ECEF (meters)
  double _localOrientation[9]; ///< Direction cosines for local orientation

}; // class CSGeoLocalCart

#include "CSGeoLocalCart.icc" // inline methods

#endif // spatialdata_geocoords_csgeolocalcart_hh


// End of file 
