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

#if !defined(spatialdata_geocoords_projector_h)
#define spatialdata_geocoords_projector_h

#include <string> // HASA std::string
#include "proj4fwd.h" // Proj4 forward declaration
#include <iosfwd> // USES std::istream, std::ostream

namespace spatialdata {
  namespace geocoords {
    class Projector;
    class CSGeo;
  } // geocoords
} // spatialdata

/// C++ object for projecting to/from geographic projections
class spatialdata::geocoords::Projector
{ // class Projector

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  Projector(void);

  /// Default destructor
  ~Projector(void);

  /// Copy constructor
  Projector(const Projector& p);

  /** Set projection.
   *
   * @param projection Name of projection
   */
  void projection(const char* name);

  /** Get projection.
   *
   * @returns Name of projection
   */
  const char* projection(void) const;

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

  /** Set proj options.
   *
   * @param options
   */
  void projOptions(const char* options);

  /** Get proj options.
   *
   * @returns Proj options
   */
  const char* projOptions(void) const;

  /** Initialize projector.
   *
   * @param csGeo Geographic coordinate system
   */
  void initialize(const CSGeo& csGeo);

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

  /** Pickle coordinate system to ascii stream.
   *
   * @param s Output stream
   */
  void pickle(std::ostream& s) const;

  /** Unpickle coordinate system from ascii stream.
   *
   * @param s Input stream
   */
  void unpickle(std::istream& s);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  std::string _projection; ///< Name of projection
  std::string _units; ///< Name of units in projection
  std::string _projOptions; ///< options for proj
  
  projPJ _pProj; ///< Pointer to projection
  
}; // class Projector

#include "Projector.icc" // inline methods

#endif // spatialdata_geocoords_projector_h

// version
// $Id: Projector.h,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
