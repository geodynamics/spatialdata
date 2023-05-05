// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
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

namespace spatialdata {
    namespace geocoords {
        namespace _converter {
            class Cache;
        } // _Converter
    } // geocoords
} // spatialdata

class spatialdata::geocoords::Converter {
    friend class TestConverter; // unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor
    Converter(void);

    /// Default destructor
    ~Converter(void);

    /** Convert coordinates from source coordinate system to destination
     * coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     * @param[in] csDest Pointer to destination coordinate system
     * @param[in] csSrc Pointer to source coordinate system
     */
    void convert(double* coords,
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
    void _convert(double* coords,
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
    void _convert(double* coords,
                  const size_t numLocs,
                  const size_t numDims,
                  const CSCart* csDest,
                  const CSCart* csSrc);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    _converter::Cache* _cache;

}; // class Converter

#endif // spatialdata_geocoords_converter_hh

// End of file
