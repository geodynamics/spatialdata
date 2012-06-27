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

/** @file libsrc/geocoords/CSGeoProj.hh
 *
 * @brief C++ CSGeoProj object
 *
 * C++ object for defining a projected geographic coordinate system.
 */

#if !defined(spatialdata_geocoords_csgeoproj_hh)
#define spatialdata_geocoords_csgeoproj_hh

#include "CSGeo.hh" // ISA CSGeo

/// C++ object for defining a local cartesian coordinate system
class spatialdata::geocoords::CSGeoProj : public CSGeo
{ // class CSGeoProj
  friend class TestCSGeoProj;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Default constructor
   *
   * @param cs Source coordinate system
   */
  CSGeoProj(void);

  /// Default destructor
  ~CSGeoProj(void);

  /** Clone coordinate system.
   *
   * @returns Pointer to copy
   */
  virtual CoordSys* clone(void) const;

  /** Set projector.
   *
   * @param projector Geographic coordinate projector
   */
  void projector(const Projector& projector);

  /** Set origin of local projected coordinate system.
   *
   * @param lon Longitude of origin (degrees, WGS84)
   * @param lat Latitude of origin (degrees, WGS84)
   */
  void origin(const double lon,
	      const double lat);

  /** Get origin of local projected coordinate system.
   *
   * @param pLon Pointer to longitude of origin (degrees, WGS84)
   * @param pLat Pointer to latitude of origin (degrees, WGS84)
   */
  void origin(double* pLon,
	      double* pLat);  

  /** Set rotation angle (CCW from east) of local x axis.
   *
   * @param angle Rotation angle.
   */
  void rotationAngle(const double angle);

  /** Get rotation angle (CCW from east) of local x axis.
   *
   * @returns Rotation angle.
   */
  double rotationAngle(void) const;

  /// Initialize the coordinate system.
  void initialize(void);

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
  CSGeoProj(const CSGeoProj& cs);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _originLon;
  double _originLat;
  double _originX;
  double _originY;
  double _rotAngle;

  Projector* _pProjector; ///< Pointer to Projector

}; // class CSGeoProj

#include "CSGeoProj.icc" // inline methods

#endif // spatialdata_geocoords_csgeoproj_hh


// End of file 
