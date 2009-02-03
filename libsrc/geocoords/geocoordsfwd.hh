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

/** @file libsrc/geocoords/geocoordsfwd.hh
 *
 * @brief Forward declarations for spatialdata::geocoords objects.
 *
 * Including this header file eliminates the need to use separate
 * forward declarations.
 */

#if !defined(spatialdata_geocoords_geocoordsfwd_hh)
#define spatialdata_geocoords_geocoordsfwd_hh

namespace spatialdata {
  namespace geocoords {
    class CoordSys;
    class CSCart;
    class CSGeo;
    class CSGeoLocalCart;
    class CSGeoProj;

    class Projector;

    class Geoid;

    class Converter;

    class CSPicklerAscii;
  } // geocoords
} // spatialdata


#endif // spatialdata_geocoords_geocoordsfwd_hh


// End of file 
