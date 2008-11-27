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

#include <portinfo>

#include "NondimElastic.hh" // implementation of class methods

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::units::NondimElastic::NondimElastic(void) :
  _length(1.0),
  _pressure(1.0),
  _time(1.0),
  _density(1.0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::units::NondimElastic::~NondimElastic(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Copy constructor.
spatialdata::units::NondimElastic::NondimElastic(const NondimElastic& dim) :
  _length(dim._length),
  _pressure(dim._pressure),
  _time(dim._time),
  _density(dim._density)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Assignment operator.
const spatialdata::units::NondimElastic& 
spatialdata::units::NondimElastic::operator=(const NondimElastic& dim)
{ // operator=
  if (this != &dim) {
    _length = dim._length;
    _pressure = dim._pressure;
    _time = dim._time;
    _density = dim._density;
  } // if

  return *this;
} // operator=

// ----------------------------------------------------------------------
// Set value to nondimensionalize length scale in meters (SI units).
void
spatialdata::units::NondimElastic::lengthScale(const double value)
{ // lengthScale
  if (value <= 0.0) {
    std::ostringstream msg;
    msg << "Length scale (" << value << ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  _length = value;
} // lengthScale

// ----------------------------------------------------------------------
// Set value to nondimensionalize pressure scale in Pascals (SI units).
void
spatialdata::units::NondimElastic::pressureScale(const double value)
{ // pressureScale
  if (value <= 0.0) {
    std::ostringstream msg;
    msg << "Pressure scale (" << value << ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  _pressure = value;
} // pressureScale

// ----------------------------------------------------------------------
// Set value to nondimensionalize time scale in seconds (SI units).
void
spatialdata::units::NondimElastic::timeScale(const double value)
{ // timeScale
  if (value <= 0.0) {
    std::ostringstream msg;
    msg << "Time scale (" << value << ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  _time = value;
} // timeScale

// ----------------------------------------------------------------------
// Set value to nondimensionalize density scale in kg/m^3 (SI units).
void
spatialdata::units::NondimElastic::densityScale(const double value)
{ // densityScale
  if (value <= 0.0) {
    std::ostringstream msg;
    msg << "Density scale (" << value << ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  _density = value;
} // densityScale

// ----------------------------------------------------------------------
// Make length scales dimensionless.
void
spatialdata::units::NondimElastic::utonLength(double* const values,
					      const int nvalues) const
{ // utonLength
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] /= _length;
} // utonLength

// ----------------------------------------------------------------------
// Add dimensions to length scale.
void
spatialdata::units::NondimElastic::ntouLength(double* const values,
					      const int nvalues) const
{ // ntouLength
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] *= _length;
} // ntouLength

// ----------------------------------------------------------------------
// Make pressure scales dimensionless.
void
spatialdata::units::NondimElastic::utonPressure(double* const values,
						const int nvalues) const
{ // utonPressure
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] /= _pressure;
} // utonPressure

// ----------------------------------------------------------------------
// Add dimensions to pressure scale.
void
spatialdata::units::NondimElastic::ntouPressure(double* const values,
						const int nvalues) const
{ // ntouPressure
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] *= _pressure;
} // ntouPressure

// ----------------------------------------------------------------------
// Make time scales dimensionless.
void
spatialdata::units::NondimElastic::utonTime(double* const values,
					    const int nvalues) const
{ // utonTime
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] /= _time;
} // utonTime

// ----------------------------------------------------------------------
// Add dimensions to time scale.
void
spatialdata::units::NondimElastic::ntouTime(double* const values,
					    const int nvalues) const
{ // ntouTime
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] *= _time;
} // ntouTime

// ----------------------------------------------------------------------
// Make density scales dimensionless.
void
spatialdata::units::NondimElastic::utonDensity(double* const values,
					       const int nvalues) const
{ // utonDensity
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] /= _density;
} // utonDensity

// ----------------------------------------------------------------------
// Add dimensions to density scale.
void
spatialdata::units::NondimElastic::ntouDensity(double* const values,
					       const int nvalues) const
{ // ntouDensity
  assert( (0 < nvalues && 0 != values) ||
	  (0 == nvalues && 0 == values) );

  for (int i=0; i < nvalues; ++i)
    values[i] *= _density;
} // ntouDensity


// End of file 
