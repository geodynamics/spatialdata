// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2013 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/geocoords/CoordSys.i
 *
 * @brief SWIG interface to C++ CoordSys object.
 */

namespace spatialdata {
  namespace geocoords {

    class CoordSys
    { // class CoordSys
    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Type of coordinate system
      enum CSTypeEnum {
	CARTESIAN, ///< Cartesian coordinate system
	GEOGRAPHIC ///< Geographic coordinate system
      };

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      CoordSys(void);

      /// Default destructor
      virtual
      ~CoordSys(void);

      /** Clone coordinate system.
       *
       * @returns Copy of *this
       */
      virtual
      CoordSys* clone(void) const = 0;

      /** Set number of spatial dimensions in coordinate system.
       *
       * @param ndims Number of dimensions
       */
      virtual
      void setSpaceDim(const int ndims);

      /** Get number of spatial dimensions in coordinate system.
       *
       * @returns Number of dimensions
       */
      int spaceDim(void) const;

      /// Initialize the coordinate system.
      virtual
      void initialize(void) = 0;

      /// Get type of coordinate system
      CSTypeEnum csType(void) const;

    }; // class CoordSys

  } // geocoords
} // spatialdata


// End of file 
