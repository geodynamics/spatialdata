// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/geocoords/CSGeoLocalCart.i
 *
 * @brief SWIG interface to C++ CSGeoLocalCart object.
 */

namespace spatialdata {
  namespace geocoords {

    class CSGeoLocalCart : public CSGeo
    { // class CSGeoLocalCart

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      CSGeoLocalCart(void);

      /// Default destructor
      ~CSGeoLocalCart(void);

      /** Clone coordinate system.
       *
       * @returns Pointer to copy
       */
      virtual
      CoordSys* clone(void) const;

      /// Initialize the coordinate system.
      void initialize(void);

      /** Set origin of local cartesian coordinate system.
       *
       * Units of elevation should be consistent with conversion factor to
       * meters.
       *
       * @param lon Longitude of origin (degrees)
       * @param lat Latitude of origin (degrees)
       * @param elev Elevation (wrt vertical datum) of origin
       */
      void origin(const double lon,
		  const double lat,
		  const double elev);

      /** Get origin of local cartesian coordinate system.
       *
       * @param pLon Pointer to longitude of origin (degrees)
       * @param pLat Pointer to latitude of origin (degrees)
       * @param pElev Pointer to elevation (wrt vertical datum) of origin
       */
      %apply double* OUTPUT { double* pLon, double* pLat, double* pElev };
      void origin(double* pLon,
		  double* pLat,
		  double* pElev);
      
      /** Get radial outward direction.
       *
       * dir and coords
       *   size = numLocs * numDims
       *   index = iLoc*numDims + iDim
       *
       * @param dir Array of direction cosines for outward radial direction.
       * @param coords Array of coordinates for locations.
       * @param numLocs Number of locations.
       * @param numDims Number of dimensions in coordinates.
       */
      void radialDir(double* dir,
		     const double* coords,
		     const int numLocs,
		     const int numDims) const;
      
    }; // class CSGeoLocalCart
    
  } // geocoords
} // spatialdata


// End of file 
