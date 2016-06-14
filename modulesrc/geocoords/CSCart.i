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

/** @file modulesrc/geocoords/CSCart.i
 *
 * @brief SWIG interface to C++ CSCart object.
 */

namespace spatialdata {
  namespace geocoords {
    
    class CSCart : public CoordSys
    { // class CSCart

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

      /// Initialize the coordinate system.
      virtual void initialize(void);

      /** Set scale factor for converting coordinates to SI units
       * (meters).
       *
       * @param scale Scale factor
       */
      void toMeters(const double scale);

      /** Get scale factor to convert coordinates to SI units (meters).
       *
       * @returns Scale factor
       */
      double toMeters(void) const;
      
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
