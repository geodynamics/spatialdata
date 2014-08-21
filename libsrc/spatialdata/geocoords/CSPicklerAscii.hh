// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/geocoords/CSPicklerAscii.hh
 *
 * @brief C++ CSPicklerAscii object
 *
 * C++ object for pickling/unpickling coordinate systems for ascii streams.
 */

#if !defined(spatialdata_geocoords_cspicklerascii_hh)
#define spatialdata_geocoords_cspickerascii_hh

#include "geocoordsfwd.hh"

#include <iosfwd> // USES std::istream, std::ostream

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
  static
  void pickle(std::ostream& s,
	      const CoordSys* pCS);

  /** Unpickle coordinate system.
   *
   * @param s Input stream
   * @param ppCS Pointer to pointer to coordinate system
   */
  static
  void unpickle(std::istream& s,
		CoordSys** ppCS);

}; // class CSPicklerAscii

#endif // spatialdata_geocoords_cspicklerascii_hh


// End of file 
