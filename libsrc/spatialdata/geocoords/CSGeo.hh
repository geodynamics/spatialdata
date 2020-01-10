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

/** @file libsrc/geocoords/CSGeo.hh
 *
 * @brief C++ CSGeo object
 *
 * C++ object for managing parameters defining geographic coordinate systems.
 */

#if !defined(spatialdata_geocoords_csgeo_hh)
#define spatialdata_geocoords_csgeo_hh

#include "CoordSys.hh" // ISA CoordSys

#include <string> // HASA std::string

/// C++ object for managing parameters defining geographic coordinate systems
class spatialdata::geocoords::CSGeo : public CoordSys {
    friend class TestCSGeo;

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor
    CSGeo(void);

    /// Default destructor
    ~CSGeo(void);

    /** Clone coordinate system.
     *
     * @returns Pointer to copy
     */
    CoordSys* clone(void) const;

    /** Set string specifying coordinate system.
     *
     * @param[in] value String specifying coordinate system (proj format, WKT, EPSG:XXXX).
     */
    void setString(const char* value);

    /** Get string specifying coordinate system.
     *
     * @returns String specifying coordinate system (proj format, WKT, EPSG:XXXX).
     */
    const char* getString(void) const;

    /** Set number of spatial dimensions in coordinate system.
     *
     * @param ndims Number of dimensions
     */
    void setSpaceDim(const int ndims);

    /** Get radial outward direction.
     *
     * dir and coords
     *   size = numLocs * numDims
     *   index = iLoc*numDims + iDim
     *
     * @param dir Array of direction cosines for outward radial direction.
     * @param coords Array of coordinates for locations.
     * @param numLocs Number of locations.
     * @param numDims Number of dimensions in coordinates.
     * @param dx Length scale for approximate surface tangent.
     */
    void computeSurfaceNormal(double* dir,
                              const double* coords,
                              const size_t numLocs,
                              const size_t numDims,
                              const double dx=1000.0) const;

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

protected:

    // PROTECTED METHODS //////////////////////////////////////////////////

    /** Copy constructor
     *
     * @param cs Coordinate system to copy
     */
    CSGeo(const CSGeo& cs);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    std::string _string; ///< String specifying coordinate system.
    int _spaceDim; ///< Number of spatial dimensions in coordinate system

}; // class CSGeo

#endif // spatialdata_geocoords_csgeo_hh

// End of file
