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

  /// Initialize the coordinate system.
  void initialize(void);

  /** Set projector.
   *
   * @param projector Geographic coordinate projector
   */
  void projector(const Projector& projector);

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

  Projector* _pProjector; ///< Pointer to Projector

}; // class CSGeoProj

#include "CSGeoProj.icc" // inline methods

#endif // spatialdata_geocoords_csgeoproj_hh


// End of file 
