// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
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

#include <cstddef> // USES size_t

class spatialdata::geocoords::Converter {
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /** Convert coordinates from source coordinate system to destination
     * coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     * @param[in] csDest Pointer to destination coordinate system
     * @param[in] csSrc Pointer to source coordinate system
     */
    static void convert(double* coords,
                        const size_t numLocs,
                        const size_t numDims,
                        const CoordSys* csDest,
                        const CoordSys* csSrc);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    /** Convert coordinates from source geographic coordinate system to
     * destination geographic coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     * @param[in] csDest Destination coordinate system
     * @param[in] csSrc Source coordinate system
     */
    static void _convert(double* coords,
                         const size_t numLocs,
                         const size_t numDims,
                         const CSGeo* csDest,
                         const CSGeo* csSrc);

    /** Convert coordinates from source Cartesian coordinate system to
     * destination Cartesian coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     * @param[in] csDest Destination coordinate system
     * @param[in] csSrc Source coordinate system
     */
    static void _convert(double* coords,
                         const size_t numLocs,
                         const size_t numDims,
                         const CSCart* csDest,
                         const CSCart* csSrc);

}; // class Converter

#endif // spatialdata_geocoords_converter_hh

// End of file
