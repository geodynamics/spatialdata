// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "CoordSys.hh" // ISA CoordSys

#include "spatialdata/geocoords/geocoordsfwd.hh" // HOLDSA Converter

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
    CoordSys* clone(void) const override;

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
    void setSpaceDim(const int ndims) override;

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

    /** Convert coordinates from local coordinate system to geographic coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     */
    virtual
    void localToGeographic(double* coords,
                           const size_t numLocs,
                           const size_t numDims) const;

    /** Convert coordinates from geographic coordinate system to local coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     */
    virtual
    void geographicToLocal(double* coords,
                           const size_t numLocs,
                           const size_t numDims) const;

    /** Pickle coordinate system to ascii stream.
     *
     * @param s Output stream
     */
    virtual
    void pickle(std::ostream& s) const override;

    /** Unpickle coordinate system from ascii stream.
     *
     * @param s Input stream
     */
    virtual
    void unpickle(std::istream& s) override;

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
    spatialdata::geocoords::Converter* _converter; ///< Converter for coordinate transformations.

}; // class CSGeo

// End of file
