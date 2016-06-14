// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/units/Nondimensional.i
 *
 * @brief SWIG interface for C++ Nondimensional object.
 */

namespace spatialdata {
  namespace units {

    class Nondimensional
    { // class Nondimensional
    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      Nondimensional(void);

      /// Default destructor
      ~Nondimensional(void);

      /** Set value to nondimensionalize length scale in meters (SI
       * units).
       *
       * @param value Length scale in meters (SI units).
       */
      void lengthScale(const double value);
      
      /** Get value to nondimensionalize length scale in meters (SI
       * units).
       *
       * @returns Length scale in meters (SI units).
       */
      double lengthScale(void) const;
      
      /** Set value to nondimensionalize pressure scale in Pascals (SI
       * units).
       *
       * @param value Pressure scale in Pascals (SI units).
       */
      void pressureScale(const double value);
      
      /** Get value to nondimensionalize pressure scale in Pascals (SI
       * units).
       *
       * @returns Pressure scale in Pascals (SI units).
       */
      double pressureScale(void) const;
      
      /** Set value to nondimensionalize time scale in seconds (SI
       * units).
       *
       * @param value Time scale in seconds (SI units).
       */
      void timeScale(const double value);
      
      /** Get value to nondimensionalize time scale in seconds (SI
       * units).
       *
       * @returns Time scale in seconds (SI units).
       */
      double timeScale(void) const;
      
      /** Set value to nondimensionalize density scale in kg/m^3 (SI
       * units).
       *
       * @param value Density scale in kg/m^3 (SI units).
       */
      void densityScale(const double value);
      
      /** Get value to nondimensionalize density scale in kg/m^3 (SI
       * units).
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
      
    }; // class Nondimensional
    
  } // units
} // spatialdata


// End of file 
