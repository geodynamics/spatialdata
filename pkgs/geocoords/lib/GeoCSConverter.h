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

/** @file pkgs/geocoords/lib/GeoCSConverter.h
 *
 * @brief C++ GeoCSConverter object
 *
 * C++ object for converting between coordinate systems.
 */

#if !defined(spatialdata_geocsconverter_h)
#define spatialdata_geocsconverter_h

namespace spatialdata {
  class GeoCSConverter;
  class GeoCoordSys; // forward declaration
}; // namespace spatialdata

/// C++ object for converting between coordinate systems.
class spatialdata::GeoCSConverter
{ // class GeoCSConverter

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Default constructor.
   *
   * @param dest Destination coordinate system
   * @param src Source coordinate system
   */
  GeoCSConverter(const GeoCoordSys& dest,
		 const GeoCoordSys& src);

  /// Default destructor
  ~GeoCSConverter(void);

  /** Convert coordinates from source coordinate system to destination
   * coordinate system. Source coordinates are overwritten by
   * destination coordinates.
   *
   * @param ppDest Pointer to array of destination locations
   * @param numLocs Number of locations
   * @param isDeg True if coordinates are in degrees, false otherwise
   * @param is2D True if coordinates are 2-D, false if 3-D
   */
  void convert(double** ppDest,
	       const int numLocs,
	       const bool isDeg =true,
	       const bool is2D =false) const;

private :
 // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Convert vertical datum b/t elevation wrt WGS ellipsoid and mean
   *  sea level.
   *
   * @param ppDest Pointer to array of destination locations
   * @param numLocs Number of locations
   */
  void GeoCSConverter::_elevToGeoidHt(double** ppDest,
				      const int numLocs) const;

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  const GeoCoordSys& _csDest; ///< Pointer to destination coordinate system
  const GeoCoordSys& _csSrc; ///< Pointer to source coordinate system
  
}; // class GeoCSConverter

#endif // spatialdata_geocsconverter_h

// version
// $Id: GeoCSConverter.h,v 1.3 2005/07/02 00:23:25 baagaard Exp $

// End of file 
