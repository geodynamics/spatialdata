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

/** @file modulesrc/geocoords/CoordSys.i
 *
 * @brief SWIG interface to C++ CoordSys object.
 */

namespace spatialdata {
  namespace geocoords {

    class CoordSys {
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
      int getSpaceDim(void) const;

      /// Get type of coordinate system
      CSTypeEnum getCSType(void) const;

    /** Pickle coordinate system to ascii stream.
     *
     * @param s Output stream
     */
    virtual void pickle(std::ostream& s) const = 0;

    /** Unpickle coordinate system from ascii stream.
     *
     * @param s Input stream
     */
    virtual void unpickle(std::istream& s) = 0;

    }; // class CoordSys

  } // geocoords
} // spatialdata


// End of file 
