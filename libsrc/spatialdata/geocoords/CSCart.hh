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

/** @file libsrc/geocoords/CSCart.hh
 *
 * @brief C++ CSCart object
 *
 * C++ object for managing parameters defining Cartesian coordinate systems.
 */

#if !defined(spatialdata_geocoords_cscart_hh)
#define spatialdata_geocoords_cscart_hh

#include "CoordSys.hh" // ISA CoordSys

class spatialdata::geocoords::CSCart : public CoordSys {
    friend class TestCSCart;

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor
    CSCart(void);

    /// Default destructor
    virtual ~CSCart(void);

    /** Clone coordinate system.
     *
     * @returns Pointer to copy
     */
    virtual CoordSys* clone(void) const;

    /** Set scale factor for converting coordinates to SI units (meters).
     *
     * @param scale Scale factor
     */
    void setToMeters(const double scale);

    /** Get scale factor to convert coordinates to SI units (meters).
     *
     * @returns Scale factor
     */
    double getToMeters(void) const;

    /** Pickle coordinate system to ascii stream.
     *
     * @param s Output stream
     */
    virtual void pickle(std::ostream& s) const;

    /** Unpickle coordinate system from ascii stream.
     *
     * @param s Input stream
     */
    virtual void unpickle(std::istream& s);

protected:

    // PROTECTED METHODS //////////////////////////////////////////////////

    /** Copy constructor
     *
     * @param cs Coordinate system to copy
     */
    CSCart(const CSCart& cs);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    double _toMeters; ///< Scale factor to convert coordinates to meters

}; // class CSCart

#endif // spatialdata_geocoodrs_cscart_hh

// End of file
