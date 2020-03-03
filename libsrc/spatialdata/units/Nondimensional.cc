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

#include <portinfo>

#include "Nondimensional.hh" // implementation of class methods

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::units::Nondimensional::Nondimensional(void) :
    _length(1.0),
    _pressure(1.0),
    _time(1.0),
    _density(1.0),
    _temperature(1.0)
{}


// ----------------------------------------------------------------------
// Default destructor
spatialdata::units::Nondimensional::~Nondimensional(void)
{}


// ----------------------------------------------------------------------
// Copy constructor.
spatialdata::units::Nondimensional::Nondimensional(const Nondimensional& dim) :
    _length(dim._length),
    _pressure(dim._pressure),
    _time(dim._time),
    _density(dim._density),
    _temperature(dim._temperature)
{}


// ----------------------------------------------------------------------
// Assignment operator.
const spatialdata::units::Nondimensional&
spatialdata::units::Nondimensional::operator=(const Nondimensional& dim) {
    if (this != &dim) {
        _length = dim._length;
        _pressure = dim._pressure;
        _time = dim._time;
        _density = dim._density;
        _temperature = dim._temperature;
    } // if

    return *this;
} // operator=


// ----------------------------------------------------------------------
// Set value to nondimensionalize length scale in meters (SI units).
void
spatialdata::units::Nondimensional::setLengthScale(const double value) {
    if (value <= 0.0) {
        std::ostringstream msg;
        msg << "Length scale (" << value << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    _length = value;
} // setLengthScale


// ----------------------------------------------------------------------
// Set value to nondimensionalize pressure scale in Pascals (SI units).
void
spatialdata::units::Nondimensional::setPressureScale(const double value) {
    if (value <= 0.0) {
        std::ostringstream msg;
        msg << "Pressure scale (" << value << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    _pressure = value;
} // setPressureScale


// ----------------------------------------------------------------------
// Set value to nondimensionalize time scale in seconds (SI units).
void
spatialdata::units::Nondimensional::setTimeScale(const double value) {
    if (value <= 0.0) {
        std::ostringstream msg;
        msg << "Time scale (" << value << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    _time = value;
} // setTimeScale


// ----------------------------------------------------------------------
// Set value to nondimensionalize density scale in kg/m^3 (SI units).
void
spatialdata::units::Nondimensional::setDensityScale(const double value) {
    if (value <= 0.0) {
        std::ostringstream msg;
        msg << "Density scale (" << value << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    _density = value;
} // setDensityScale


// ----------------------------------------------------------------------
// Set value to nondimensionalize temperature scale in Kelvin (SI units).
void
spatialdata::units::Nondimensional::setTemperatureScale(const double value) {
    if (value <= 0.0) {
        std::ostringstream msg;
        msg << "Temperature scale (" << value << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    _temperature = value;
} // setTemperatureScale


// ----------------------------------------------------------------------
// Set density scale from length, time, and pressure scales.
void
spatialdata::units::Nondimensional::computeDensityScale(void) {
    const double velocityScale = _length / _time;
    _density = _pressure / (velocityScale * velocityScale);
} // computeDensityScale


// ----------------------------------------------------------------------
// Compute pressure scale from length, time, and density scales.
void
spatialdata::units::Nondimensional::computePressureScale(void) {
    const double velocityScale = _length / _time;
    _pressure = _density * velocityScale * velocityScale;
} // computePressureScale


// End of file
