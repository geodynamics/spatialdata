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

/** @file pkgs/geocoords/lib/Geoid.h
 *
 * @brief C++ Geoid object
 *
 * C++ object for converting difference between elevation relative to
 * mean seal level (MSL) and elevation relative to WGS ellipsoid.
 */

#if !defined(spatialdata_geoid_h)
#define spatialdata_geoid_h

namespace spatialdata {
  namespace geocoords {
    class Geoid;
  } // geocoords
} // spatialdata

/// C++ object for converting difference between elevation relative to
/// mean seal level (MSL) and elevation relative to WGS ellipsoid.
class spatialdata::geocoords::Geoid
{ // class Geoid

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  Geoid(void);

  /// Default destructor
  ~Geoid(void);

  /// Initialize
  void initialize(void);

  /** Compute elevation with respect to WGS ellipsoid relative to
   *  elevation with respect to MSL.
   *
   * To convert from elevation wrt MSL to elevation wrt WGS ellipsoid,
   * add return value to elevation wrt MSL.
   *
   * @param lon Longitude in radians in WGS84 datum
   * @param lat Latitude in radians in WGS84 datum
   *
   * @returns Different in elevation b/t MSL and WGS84 ellipsoid
   */
  double elevation(const double lon,
		   const double lat) const;

private :
 // PRIVATE METHODS ////////////////////////////////////////////////////
  
  double _calcElev(const double* pLegCoef,
		   const double* pSinML,
		   const double* pCosML,
		   const double radiusGeocent,
		   const double normalGrav) const;

  void _geocentricLat(double* pLatGeocent,
		      double* pRadiusGeocent,
		      double* pNormalGrav,
		      const double lon,
		      const double lat) const;

  void _calcML(double** ppSinML,
	       double** ppCosML,
	       const double lon) const;

  void _calcLegFn(double** pLegFn,
		  const int order,
		  const double latGeocent) const;

  void _setCCCS(void);
  void _setHCHS(void);
  void _calcRoots(void);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double* _pHC;
  double* _pHS;
  double* _pCC;
  double* _pCS;
  double* _pRoots;
  double* _pInvRoots;

  static const double _EGM96[];
  static const double _CORRCOEF[];
  static const int _NUMMODES;

}; // class Geoid

#endif // spatialdata_geocoords_geoid_h

// version
// $Id: Geoid.h,v 1.1 2005/06/19 19:23:22 baagaard Exp $

// End of file 
