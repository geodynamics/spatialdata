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

/** @file modulesrc/geocoords/CSGeo.i
 *
 * @brief SWIG interface to C++ CSGeo object.
 */

namespace spatialdata {
  namespace geocoords {

  class Geoid;

    class CSGeo : public CoordSys
    { // class CSGeo
      friend class TestCSGeo;

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor
      CSGeo(void);

      /// Default destructor
      virtual
      ~CSGeo(void);

      /** Clone coordinate system.
       *
       * @returns Pointer to copy
       */
      virtual
      CoordSys* clone(void) const;
      
      /// Initialize the coordinate system.
      virtual
      void initialize(void);
      
      /** Set reference ellipsoid.
       *
       * @param name Name of reference ellipsoid
       */
      void ellipsoid(const char* name);

      /** Get reference ellipsoid.
       *
       * @returns Name of reference ellipsoid
       */
      const char* ellipsoid(void) const;

      /** Set horizontal datum.
       *
       * @param name Name of horizontal datum
       */
      void datumHoriz(const char* name);

      /** Get horizontal datum.
       *
       * @returns Name of datum
       */
      const char* datumHoriz(void) const;

      /** Set vertical datum.
       *
       * @param name Name of vertical datum
       */
      void datumVert(const char* name);

      /** Get vertical datum.
       *
       * @returns Name of datum
       */
      const char* datumVert(void) const;

      /** Set geocentric flag.
       *
       * @param geocentric True if geocentric, false if lon/lat
       */
      virtual
      void isGeocentric(bool geocentric);

      /** Get geocentric flag.
       *
       * @returns True if geocentric, false if lon/lat
       */
      bool isGeocentric(void) const;

      /** Set factor to convert Cartesian coordinates to meters.
       *
       * @param factor Factor to convert Cartesian coordinates to meters.
       */
      void toMeters(const double factor);

      /** Get factor to convert Cartesian coordinates to meters.
       *
       * @returns Factor to convert Cartesian coordinates to meters.
       */
      double toMeters(void) const;

      /** Set number of spatial dimensions in coordinate system.
       *
       * @param ndims Number of dimensions
       */
      virtual
      void setSpaceDim(const int ndims);

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
      virtual
      void radialDir(double* dir,
		     const double* coords,
		     const int numLocs,
		     const int numDims) const;

      /** Get geoid.
       *
       * @returns Geoid
       */
      static Geoid& geoid(void);
  
    }; // class CSGeo

  } // geocoords
} // spatialdata


// End of file 
