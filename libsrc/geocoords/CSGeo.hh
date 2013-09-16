// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/geocoords/CSGeo.hh
 *
 * @brief C++ CSGeo object
 *
 * C++ object for managing parameters defining geographic coordinate systems.
 */

#if !defined(spatialdata_geocoords_csgeo_hh)
#define spatialdata_geocoords_csgeo_hh

#include "CoordSys.hh" // ISA CoordSys

#include "proj4fwd.h" // Proj4 forward declaration
#include <string> // HASA std::string

/// C++ object for managing parameters defining geographic coordinate systems
class spatialdata::geocoords::CSGeo : public CoordSys
{ // class CSGeo
  friend class TestCSGeo;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  CSGeo(void);

  /// Default destructor
  virtual ~CSGeo(void);

  /** Clone coordinate system.
   *
   * @returns Pointer to copy
   */
  virtual CoordSys* clone(void) const;

  /// Initialize the coordinate system.
  virtual void initialize(void);

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

  /** Get vertical datum.
   *
   * @returns Name of datum
   */
  const char* datumVert(void) const;

  /** Set geocentric flag.
   *
   * @param geocentric True if geocentric, false if lon/lat
   */
  virtual void isGeocentric(bool geocentric);

  /** Get geocentric flag.
   *
   * @returns True if geocentric, false if lon/lat
   */
  bool isGeocentric(void) const;

  /** Set factor to convert Cartesian coordinates to meters.
   *
   * @param factor Factor to convert Cartesian coordinates to meters.
   */
  void toMeters(const double factor);

  /** Get factor to convert Cartesian coordinates to meters.
   *
   * @returns Factor to convert Cartesian coordinates to meters.
   */
  double toMeters(void) const;

  /** Set number of spatial dimensions in coordinate system.
   *
   * @param ndims Number of dimensions
   */
  virtual void setSpaceDim(const int ndims);

  /** Get proj form vertical datum.
   *
   * @returns Name of datum
   */
  virtual const char* projDatumVert(void) const;

  /** Get PROJ coordinate system.
   *
   * @returns Coordinate system
   */
  virtual projPJ projCoordSys(void) const;

  /** Convert coordinates to PROJ4 useable form.
   *
   * @param coords Array of coordinates [numLocs*numDims]
   * @param numLocs Number of locations
   * @param numDims Number of dimensions in coordinates
   */
  virtual void toProjForm(double* coords,
			  const int numLocs,
			  const int numDims) const;
  
  /** Convert coordinates from PROJ4 form to form associated w/coordsys.
   *
   * @param coords Array of coordinates [numLocs*numDims]
   * @param numLocs Number of locations
   * @param numDims Number of dimensions in coordinates
   */
  virtual void fromProjForm(double* coords,
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
  virtual void radialDir(double* dir,
			 const double* coords,
			 const int numLocs,
			 const int numDims) const;

  /** Get geoid.
   *
   * @returns Geoid
   */
  static Geoid& geoid(void);
  
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
  CSGeo(const CSGeo& cs);

  /** Get the PROJ4 string associated with the coordinate system.
   *
   * @returns string
   */
  virtual std::string _projCSString(void) const;

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _toMeters; ///< Factor to convert Cartesian coordinates to meters
  int _spaceDim; ///< Number of spatial dimensions in coordinate system
  std::string _ellipsoid; ///< Name of reference ellipsoid
  std::string _datumHoriz; ///< Name of horizontal geographic datum
  std::string _datumVert; ///< Name of vertical datum
  
  projPJ _pCS; ///< Pointer to coordinate system
  
  bool _isGeocentric; ///< True if geocentric, false if lat/lon
}; // class CSGeo

#include "CSGeo.icc" // inline methods

#endif // spatialdata_geocoodrs_csgeo_hh


// End of file 
