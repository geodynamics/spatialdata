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

/** @file pkgs/geocoords/lib/Converter.h
 *
 * @brief C++ Converter object
 *
 * C++ object for converting between coordinate systems.
 */

#if !defined(spatialdata_geocoords_converter_h)
#define spatialdata_geocoords_converter_h

namespace spatialdata {
  namespace geocoords {
    class Converter;
    class CoordSys; // forward declaration
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
   * @param ppCoords Pointer to array of coordinates
   * @param numLocs Number of location
   * @param csDest Destination coordinate system
   * @param csSrc Source coordinate system
   * @param is2D True if 2D, false if 3D
   */
  static void convert(double** ppCoords,
		      const int numLocs,
		      const CoordSys& csDest,
		      const CoordSys& csSrc,
		      bool is2D =false);

}; // class Converter

#endif // spatialdata_geocoords_converter_h

// version
// $Id$

// End of file 
