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

/** @file libsrc/geocoords/CSPicklerAscii.hh
 *
 * @brief C++ CSPicklerAscii object
 *
 * C++ object for pickling/unpickling coordinate systems for ascii streams.
 */

#if !defined(spatialdata_geocoords_cspicklerascii_hh)
#define spatialdata_geocoords_cspickerascii_hh

#include <iosfwd> // USES std::istream, std::ostream

namespace spatialdata {
  namespace geocoords {
    class CSPicklerAscii;
    class CoordSys;
  } // geocoords
} // spatialdata

/// C++ object for pickling/unpickling coordinate systems for ascii streams.
class spatialdata::geocoords::CSPicklerAscii
{ // class CoordSys
public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Pickle coordinate system.
   *
   * @param s Ouput stream
   * @param pCS Pointer to coordinate system
   */
  static void pickle(std::ostream& s,
		     const CoordSys* pCS);

  /** Unpickle coordinate system.
   *
   * @param s Input stream
   * @param ppCS Pointer to pointer to coordinate system
   */
  static void unpickle(std::istream& s,
			CoordSys** ppCS);

}; // class CSPicklerAscii

#endif // spatialdata_geocoords_cspicklerascii_hh

// version
// $Id$

// End of file 