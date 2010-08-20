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

/** @file modulesrc/geocoords/CSGeoProj.i
 *
 * @brief SWIG interface to C++ CSGeoProj object
 */

namespace spatialdata {
  namespace geocoords {
    class Projector; // foward declaration
    
    class CSGeoProj : public CSGeo
    { // class CSGeoProj

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      CSGeoProj(void);

      /// Default destructor
      ~CSGeoProj(void);

      /** Clone coordinate system.
       *
       * @returns Pointer to copy
       */
      virtual
      CoordSys* clone(void) const;

      /// Initialize the coordinate system.
      void initialize(void);

      /** Set projector.
       *
       * @param projector Geographic coordinate projector
       */
      void projector(const Projector& projector);

    }; // class CSGeoProj

  } // geocoords
} // spatialdata


// End of file 
