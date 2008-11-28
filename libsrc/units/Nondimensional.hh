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

/** @file libsrc/units/Nondimensional.hh
 *
 * @brief C++ Manager for nondimensionalization of problems.
 *
 * C++ object for managing nondimensionalization of problems.
 */

#if !defined(spatialdata_units_nondimensional_hh)
#define spatialdata_units_nondimensional_hh

namespace spatialdata {
  namespace units {
    class Nondimensional;

    class TestNondimensional; // Unit testing
  } // units
} // spatialdata

/// C++ object for managing parameters defining a coordinate system
class spatialdata::units::Nondimensional
{ // class Nondimensional
  friend class TestNondimensional; // Unit testing

public :
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
  void lengthScale(const double value);

  /** Get value to nondimensionalize length scale in meters (SI units).
   *
   * @returns Length scale in meters (SI units).
   */
  double lengthScale(void) const;

  /** Set value to nondimensionalize pressure scale in Pascals (SI units).
   *
   * @param value Pressure scale in Pascals (SI units).
   */
  void pressureScale(const double value);

  /** Get value to nondimensionalize pressure scale in Pascals (SI units).
   *
   * @returns Pressure scale in Pascals (SI units).
   */
  double pressureScale(void) const;

  /** Set value to nondimensionalize time scale in seconds (SI units).
   *
   * @param value Time scale in seconds (SI units).
   */
  void timeScale(const double value);

  /** Get value to nondimensionalize time scale in seconds (SI units).
   *
   * @returns Time scale in seconds (SI units).
   */
  double timeScale(void) const;

  /** Set value to nondimensionalize density scale in kg/m^3 (SI units).
   *
   * @param value Density scale in kg/m^3 (SI units).
   */
  void densityScale(const double value);

  /** Get value to nondimensionalize density scale in kg/m^3 (SI units).
   *
   * @returns Density scale in kg/m^3 (SI units).
   */
  double densityScale(void) const;

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
			 const int nvalues,
			 const double scale) const;

  /** Make value dimensionless.
   *
   * @param values Array of dimensionless values.
   * @param nvalues Number of values.
   * @param scale Scale used to nondimensionalize value.
   */
  void dimensionalize(double* const values,
		      const int nvalues,
		      const double scale) const;

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _length; ///< Length scale
  double _pressure; ///< Pressure scale
  double _time; ///< Time scale
  double _density; ///< Density scale

}; // class Nondimensional

#include "Nondimensional.icc" // inline methods

#endif // spatialdata_units_nondimensional_hh


// End of file 
