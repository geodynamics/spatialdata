// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/geocoords/Projector.i
 *
 * @brief SWIG interface to C++ Projector object.
 */

namespace spatialdata {
  namespace geocoords {

    class Projector
    { // class Projector

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      Projector(void);

      /// Default destructor
      ~Projector(void);

      /** Set projection.
       *
       * @param projection Name of projection
       */
      void projection(const char* name);

      /** Get projection.
       *
       * @returns Name of projection
       */
      const char* projection(void) const;

      /** Set units of projection.
       *
       * @param name Name of units
       */
      void units(const char* name);

      /** Get units of projection.
       *
       * @returns Name of units
       */
      const char* units(void) const;

      /** Set proj options.
       *
       * @param options
       */
      void projOptions(const char* options);

      /** Get proj options.
       *
       * @returns Proj options
       */
      const char* projOptions(void) const;

      /** Initialize projector.
       *
       * @param csGeo Geographic coordinate system
       */
      void initialize(const CSGeo& csGeo);

    }; // class Projector

  } // geocoords
} // spatialdata


// End of file 
