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

/** @file libsrc/geocoords/CSGeoLocal.hh
 *
 * @brief C++ CSGeoLocal object
 *
 * C++ object for managing parameters defining geographic coordinate systems.
 */

#if !defined(spatialdata_geocoords_csgeoLocallocal_hh)
#define spatialdata_geocoords_csgeoLocallocal_hh

#include "CSGeo.hh" // ISA CSGeo

#include "spatialdata/geocoords/geocoordsfwd.hh" // HOLDSA Converter

#include <string> // HASA std::string

/// C++ object for managing parameters defining geographic coordinate systems
class spatialdata::geocoords::CSGeoLocal : public CSGeo {
    friend class TestCSGeoLocal;

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////

    /// Default constructor
    CSGeoLocal(void);

    /// Default destructor
    ~CSGeoLocal(void);

    /** Clone coordinate system.
     *
     * @returns Pointer to copy
     */
    CoordSys* clone(void) const override;

    /** Set parameters specifying local coordinate system.
     *
     * @param[in] originX X coordinate of local origin.
     * @param[in] originY Y coordinate of local origin.
     * @param[in] yAzimuth Azimuth (degrees) of y axis.
     */
    void setLocal(const double originX,
                  const double originY,
                  const double yAzimuth);

    /** Get parameters specifying local coordinate system.
     *
     * @param[out] originX X coordinate of local origin.
     * @param[out] originY Y coordinate of local origin.
     * @param[out] yAzimuth Azimuth (degrees) of y axis.
     */
    void getLocal(double* originX,
                  double* originY,
                  double* yAzimuth) const;

    /** Convert coordinates from local coordinate system to geographic coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     */
    void localToGeographic(double* coords,
                           const size_t numLocs,
                           const size_t numDims) const override;

    /** Convert coordinates from geographic coordinate system to local coordinate system.
     *
     * @param[inout] coords Array of coordinates
     * @param[in] numLocs Number of location
     * @param[in] numDims Number of spatial dimensions in coordinates
     */
    void geographicToLocal(double* coords,
                           const size_t numLocs,
                           const size_t numDims) const override;

    /** Pickle coordinate system to ascii stream.
     *
     * @param s Output stream
     */
    void pickle(std::ostream& s) const override;

    /** Unpickle coordinate system from ascii stream.
     *
     * @param s Input stream
     */
    void unpickle(std::istream& s) override;

protected:

    // PROTECTED METHODS //////////////////////////////////////////////////

    /** Copy constructor
     *
     * @param cs Coordinate system to copy
     */
    CSGeoLocal(const CSGeoLocal& cs);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    double _originX; ///< X coordinate of local origin.
    double _originY; ///< Y coordinate of local origin.
    double _yAzimuth; ///< Azimuth (degrees) of y axis.

}; // class CSGeoLocal

#endif // spatialdata_geocoords_csgeoLocallocal_hh

// End of file
