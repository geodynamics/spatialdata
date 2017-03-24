// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
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

      /** Set projector.
       *
       * @param projector Geographic coordinate projector
       */
      void projector(const Projector& projector);

      /** Set origin of local projected coordinate system.
       *
       * @param lon Longitude of origin (degrees)
       * @param lat Latitude of origin (degrees)
       */
      void origin(const double lon,
		  const double lat);
      
      /** Get origin of local projected coordinate system.
       *
       * @param pLon Pointer to longitude of origin (degrees)
       * @param pLat Pointer to latitude of origin (degrees)
       */
      %apply double* OUTPUT { double* pLon, double* pLat };
      void origin(double* pLon,
		  double* pLat);  
      
      /** Set rotation angle (CCW from east) of local x axis.
       *
       * @param angle Rotation angle.
       */
      void rotationAngle(const double angle);
      
      /** Get rotation angle (CCW from east) of local x axis.
       *
       * @returns Rotation angle.
       */
      double rotationAngle(void) const;
      
      /// Initialize the coordinate system.
      void initialize(void);

    }; // class CSGeoProj

  } // geocoords
} // spatialdata


// End of file 
