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

/** @file libsrc/geocoords/Converter.hh
 *
 * @brief C++ Converter object
 *
 * C++ object for converting between coordinate systems.
 */

#if !defined(spatialdata_geocoords_converter_hh)
#define spatialdata_geocoords_converter_hh

namespace spatialdata {
  namespace geocoords {
    class Converter;
    class CoordSys; // forward declaration
    class CSGeo; // forward declaration
    class CSCart; // forward declaration
  } // geocoords
} // spatialdata

/// C++ object for converting between coordinate systems.
class spatialdata::geocoords::Converter
{ // class Converter
 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Convert coordinates from source coordinate system to destination
   * coordinate system.
   *
   * @param coords Array of coordinates
   * @param numLocs Number of location
   * @param pCSDest Pointer to destination coordinate system
   * @param pCSSrc Pointer to source coordinate system
   * @param is2D True if 2D, false if 3D
   */
  static void convert(double* coords,
		      const int numLocs,
		      const CoordSys* pCSDest,
		      const CoordSys* pCSSrc,
		      bool is2D =false);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Convert coordinates from source geographic coordinate system to
   * destination geographic coordinate system.
   *
   * @param coords Array of coordinates
   * @param numLocs Number of location
   * @param csDest Destination coordinate system
   * @param csSrc Source coordinate system
   * @param is2D True if 2D, false if 3D
   */
  static void _convert(double* coords,
		       const int numLocs,
		       const CSGeo& csDest,
		       const CSGeo& csSrc,
		       bool is2D =false);

  /** Convert coordinates from source Cartesian coordinate system to
   * destination Cartesian coordinate system.
   *
   * @param coords Array of coordinates
   * @param numLocs Number of location
   * @param csDest Destination coordinate system
   * @param csSrc Source coordinate system
   * @param is2D True if 2D, false if 3D
   */
  static void _convert(double* coords,
		       const int numLocs,
		       const CSCart& csDest,
		       const CSCart& csSrc,
		       bool is2D =false);

}; // class Converter

#endif // spatialdata_geocoords_converter_hh

// version
// $Id$

// End of file 
