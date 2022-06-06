// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/geocoords/CSCart.i
 *
 * @brief SWIG interface to C++ CSCart object.
 */

namespace spatialdata {
  namespace geocoords {
    
    class CSCart : public CoordSys {

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

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
      
    }; // class CSCart
    
  } // geocoords
} // spatialdata


// End of file 
