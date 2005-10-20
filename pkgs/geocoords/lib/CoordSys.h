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

/** @file pkgs/geocoords/lib/GeoCoordSys.h
 *
 * @brief C++ GeoCoordSys object
 *
 * C++ object for managing parameters defining a coordinate system.
 */

#if !defined(spatialdata_geocoords_coordsys_h)
#define spatialdata_geocoords_coordsys_h

namespace spatialdata {
  namespace geocoords {
    class CoordSys;
  } // geocoords
} // spatialdata

#include "proj4fwd.h" // Proj4 forward declaration
#include <string> // USES std::string

/// C++ object for managing parameters defining a coordinate system
class spatialdata::geocoords::CoordSys
{ // class CoordSys
 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  CoordSys(void);

  /// Default destructor
  virtual ~CoordSys(void);

  /** Get PROJ coordinate system.
   *
   * @returns Coordinate system
   */
  const projPJ projCoordSys(void) const;

  /// Initialize the PROJ4 coordinate system.
  void initialize(void);

  /** Get vertical datum.
   *
   * @returns Name of datum
   */
  virtual const char* datumVert(void) const = 0;

  /** Get conversion of elevation to meters.
   *
   * @returns Conversion factor to convert elevation to meters
   */
  virtual double elevToMeters(void) const = 0;

  /** Get proj form vertical datum.
   *
   * @returns Name of datum
   */
  virtual const char* projDatumVert(void) const = 0;

  /** Convert coordinates to PROJ4 useable form.
   *
   * @param ppCoords Pointer to array of coordinates [#locs*3]
   * @param numLocs Number of locations
   * @param is2D True if coordinates are 2D, false if 3D
   */
  virtual void toProjForm(double** ppCoords,
			  const int numLocs,
			  bool is2D =false) const = 0;
  
  /** Convert coordinates from PROJ4 form to form associated w/coordsys.
   *
   * @param ppCoords Pointer to array of coordinates [#locs*3]
   * @param numLocs Number of locations
   * @param is2D True if coordinates are 2D, false if 3D
   */
  virtual void fromProjForm(double** ppCoords,
			    const int numLocs,
			    bool is2D =false) const = 0;
  
protected :
  // PROTECTED MEMBERS /////////////////////////////////////////////////

  /** Get the PROJ4 string associated with the coordinate system.
   *
   * @returns string
   */
  virtual std::string _projCSString(void) const = 0;
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  projPJ _pCS; ///< Pointer to coordinate system
  
}; // class CoordSys

#include "CoordSys.icc" // inline methods

#endif // spatialdata_geocoords_coordsys_h

// version
// $Id$

// End of file 
