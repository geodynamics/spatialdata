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

/** @file libsrc/geocoords/Converter.hh
 *
 * @brief C++ Converter object
 *
 * C++ object for converting between coordinate systems.
 */

#if !defined(spatialdata_geocoords_converter_hh)
#define spatialdata_geocoords_converter_hh

#include "geocoordsfwd.hh"

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
   * @param numDims Number of spatial dimensions in coordinates
   * @param pCSDest Pointer to destination coordinate system
   * @param pCSSrc Pointer to source coordinate system
   */
  static void convert(double* coords,
		      const int numLocs,
		      const int numDims,
		      const CoordSys* pCSDest,
		      const CoordSys* pCSSrc);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Convert coordinates from source geographic coordinate system to
   * destination geographic coordinate system.
   *
   * @param coords Array of coordinates
   * @param numLocs Number of location
   * @param numDims Number of spatial dimensions in coordinates
   * @param csDest Destination coordinate system
   * @param csSrc Source coordinate system
   */
  static void _convert(double* coords,
		       const int numLocs,
		       const int numDims,
		       const CSGeo* csDest,
		       const CSGeo* csSrc);

  /** Convert coordinates from source Cartesian coordinate system to
   * destination Cartesian coordinate system.
   *
   * @param coords Array of coordinates
   * @param numLocs Number of location
   * @param numDims Number of spatial dimensions in coordinates
   * @param csDest Destination coordinate system
   * @param csSrc Source coordinate system
   */
  static void _convert(double* coords,
		       const int numLocs,
		       const int numDims,
		       const CSCart* csDest,
		       const CSCart* csSrc);

}; // class Converter

#endif // spatialdata_geocoords_converter_hh


// End of file 
