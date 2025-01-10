// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "unitsfwd.hh"

#include <stddef.h> // USES size_t

/// C++ object for managing parameters defining a coordinate system
class spatialdata::units::Nondimensional { // class Nondimensional
    friend class TestNondimensional; // Unit testing

public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    /// Default constructor
    Nondimensional(void);

    /// Default destructor
    ~Nondimensional(void);

    /** Copy constructor.
     *
     * @param dim Object to copy.
     */
    Nondimensional(const Nondimensional& dim);

    /** Assignment operator.
     *
     * @param dim Object to copy.
     * @returns Copy of this.
     */
    const Nondimensional& operator=(const Nondimensional& dim);

    /** Set value to nondimensionalize length scale in meters (SI units).
     *
     * @param value Length scale in meters (SI units).
     */
    void setLengthScale(const double value);

    /** Get value to nondimensionalize length scale in meters (SI units).
     *
     * @returns Length scale in meters (SI units).
     */
    double getLengthScale(void) const;

    /** Set value to nondimensionalize pressure scale in Pascals (SI units).
     *
     * @param value Pressure scale in Pascals (SI units).
     */
    void setPressureScale(const double value);

    /** Get value to nondimensionalize pressure scale in Pascals (SI units).
     *
     * @returns Pressure scale in Pascals (SI units).
     */
    double getPressureScale(void) const;

    /** Set value to nondimensionalize time scale in seconds (SI units).
     *
     * @param value Time scale in seconds (SI units).
     */
    void setTimeScale(const double value);

    /** Get value to nondimensionalize time scale in seconds (SI units).
     *
     * @returns Time scale in seconds (SI units).
     */
    double getTimeScale(void) const;

    /** Set value to nondimensionalize density scale in kg/m^3 (SI units).
     *
     * @param value Density scale in kg/m^3 (SI units).
     */
    void setDensityScale(const double value);

    /** Get value to nondimensionalize density scale in kg/m^3 (SI units).
     *
     * @returns Density scale in kg/m^3 (SI units).
     */
    double getDensityScale(void) const;

    /** Set value to nondimensionalize temperature scale in Kelvin (SI units).
     *
     * @param value Temperature scale in Kelvin (SI units).
     */
    void setTemperatureScale(const double value);

    /** Get value to nondimensionalize temperature scale in Kelvin (SI units).
     *
     * @returns Temperature scale in Kelvin (SI units).
     */
    double getTemperatureScale(void) const;

    /** Set density scale from length, time, and pressure scales.
     *
     * D = P * (T / L)**2
     */
    void computeDensityScale(void);

    /** Compute pressure scale from length, time, and density scales.
     *
     * P = D * (L / T)**2
     */
    void computePressureScale(void);

    /** Make value dimensionless.
     *
     * @param value Value with dimensions in SI units.
     * @param scale Scale used to nondimensionalize value.
     * @returns Dimensionless value.
     */
    double nondimensionalize(const double value,
                             const double scale) const;

    /** Make value dimensionless.
     *
     * @param value Dimensionless value.
     * @param value Value with dimensions in SI units.
     * @returns Scale used to nondimensionalize value.
     */
    double dimensionalize(const double value,
                          const double scale) const;

    /** Make values dimensionless.
     *
     * @param values Array of values with dimensions in SI units.
     * @param nvalues Number of values.
     * @param scale Scale used to nondimensionalize value.
     */
    void nondimensionalize(double* const values,
                           const size_t nvalues,
                           const double scale) const;

    /** Make values dimensionless.
     *
     * @param values Array of values with dimensions in SI units.
     * @param nvalues Number of values.
     * @param scale Scale used to nondimensionalize value.
     */
    void nondimensionalize(float* const values,
                           const size_t nvalues,
                           const double scale) const;

    /** Make value dimensionless.
     *
     * @param values Array of dimensionless values.
     * @param nvalues Number of values.
     * @param scale Scale used to nondimensionalize value.
     */
    void dimensionalize(double* const values,
                        const size_t nvalues,
                        const double scale) const;

    /** Make value dimensionless.
     *
     * @param values Array of dimensionless values.
     * @param nvalues Number of values.
     * @param scale Scale used to nondimensionalize value.
     */
    void dimensionalize(float* const values,
                        const size_t nvalues,
                        const double scale) const;

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    double _length; ///< Length scale
    double _pressure; ///< Pressure scale
    double _time; ///< Time scale
    double _density; ///< Density scale
    double _temperature; ///< Temperature scale

}; // class Nondimensional

#include "Nondimensional.icc" // inline methods

// End of file
