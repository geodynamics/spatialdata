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

/** @file libsrc/units/NondimElastic.hh
 *
 * @brief C++ Nondimensionalization for elasticity.
 *
 * C++ object for managing scales associated with elasticity.
 */

#if !defined(spatialdata_units_nondimelastic_hh)
#define spatialdata_units_nondimelastic_hh

namespace spatialdata {
  namespace units {
    class NondimElastic;

    class TestNondimElastic; // Unit testing
  } // units
} // spatialdata

/// C++ object for managing parameters defining a coordinate system
class spatialdata::units::NondimElastic
{ // class NondimElastic
  friend class TestNondimElastic; // Unit testing

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  NondimElastic(void);

  /// Default destructor
  ~NondimElastic(void);

  /** Copy constructor.
   *
   * @param dim Object to copy.
   */
  NondimElastic(const NondimElastic& dim);

  /** Assignment operator.
   *
   * @param dim Object to copy.
   * @returns Copy of this.
   */
  const NondimElastic& operator=(const NondimElastic& dim);

  /** Set value to nondimensionalize length scale in meters (SI units).
   *
   * @param value Length scale in meters (SI units).
   */
  void lengthScale(const double value);

  /** Set value to nondimensionalize pressure scale in Pascals (SI units).
   *
   * @param value Pressure scale in Pascals (SI units).
   */
  void pressureScale(const double value);

  /** Set value to nondimensionalize time scale in seconds (SI units).
   *
   * @param value Time scale in seconds (SI units).
   */
  void timeScale(const double value);

  /** Set value to nondimensionalize density scale in kg/m^3 (SI units).
   *
   * @param value Density scale in kg/m^3 (SI units).
   */
  void densityScale(const double value);

  /** Make length scale dimensionless.
   *
   * @param value Length in meters (SI units).
   * @returns Dimensionless length.
   */
  double utonLength(const double value) const;

  /** Make length scales dimensionless.
   *
   * @param values Array of lengths in meters (SI units).
   * @param int Number of values.
   */
  void utonLength(double* const values,
		  const int nvalues) const;

  /** Add dimensions to length scale.
   *
   * @param value Dimensionless length.
   * @returns Length in meters (SI units).
   */
  double ntouLength(const double value) const;

  /** Add dimensions to length scale.
   *
   * @param values Array of dimensionless lengths.
   * @param int Number of values.
   */
  void ntouLength(double* const values,
		  const int nvalues) const;

  /** Make pressure scale dimensionless.
   *
   * @param value Pressure in Pascals (SI units).
   * @returns Dimensionless pressure.
   */
  double utonPressure(const double value) const;

  /** Make pressure scales dimensionless.
   *
   * @param values Array of pressures in Pascals (SI units).
   * @param int Number of values.
   */
  void utonPressure(double* const values,
		    const int nvalues) const;

  /** Add dimensions to pressure scale.
   *
   * @param value Dimensionless pressure.
   * @returns Pressure in meters (SI units).
   */
  double ntouPressure(const double value) const;

  /** Add dimensions to pressure scale.
   *
   * @param values Array of dimensionless pressures.
   * @param int Number of values.
   */
  void ntouPressure(double* const values,
		  const int nvalues) const;

  /** Make time scale dimensionless.
   *
   * @param value Time in seconds (SI units).
   * @returns Dimensionless time.
   */
  double utonTime(const double value) const;

  /** Make time scales dimensionless.
   *
   * @param values Array of times in seconds (SI units).
   * @param int Number of values.
   */
  void utonTime(double* const values,
		const int nvalues) const;

  /** Add dimensions to time scale.
   *
   * @param value Dimensionless time.
   * @returns Time in meters (SI units).
   */
  double ntouTime(const double value) const;

  /** Add dimensions to time scale.
   *
   * @param values Array of dimensionless times.
   * @param int Number of values.
   */
  void ntouTime(double* const values,
		const int nvalues) const;

  /** Make density scale dimensionless.
   *
   * @param value Density in kg/m^3 (SI units).
   * @returns Dimensionless density.
   */
  double utonDensity(const double value) const;

  /** Make density scales dimensionless.
   *
   * @param values Array of densities in kg/m^3 (SI units).
   * @param int Number of values.
   */
  void utonDensity(double* const values,
		   const int nvalues) const;

  /** Add dimensions to density scale.
   *
   * @param value Dimensionless density.
   * @returns Density in meters (SI units).
   */
  double ntouDensity(const double value) const;

  /** Add dimensions to density scale.
   *
   * @param values Array of dimensionless densities.
   * @param int Number of values.
   */
  void ntouDensity(double* const values,
		   const int nvalues) const;

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _length; ///< Length scale
  double _pressure; ///< Pressure scale
  double _time; ///< Time scale
  double _density; ///< Density scale

}; // class NondimElastic

#include "NondimElastic.icc" // inline methods

#endif // spatialdata_units_nondimelastic_hh


// End of file 
