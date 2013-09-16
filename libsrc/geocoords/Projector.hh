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

/** @file libsrc/geocoords/Projector.hh
 *
 * @brief C++ Projector object
 *
 * C++ object for projecting to/from geographic projections.
 */

#if !defined(spatialdata_geocoords_projector_hh)
#define spatialdata_geocoords_projector_hh

#include "geocoordsfwd.hh"

#include "proj4fwd.h" // Proj4 forward declaration
#include <string> // HASA std::string
#include <iosfwd> // USES std::istream, std::ostream

/// C++ object for projecting to/from geographic projections
class spatialdata::geocoords::Projector
{ // class Projector

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  Projector(void);

  /// Default destructor
  ~Projector(void);

  /// Copy constructor
  Projector(const Projector& p);

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

  /** Project geographic coordinates.
   *
   * @param coords Array of coordinates (input/output).
   * @param numLocs Number of location.
   * @param numDims Number of spatial dimensions in coordinates.
   */
  void project(double* coords,
	       const int numLocs,
	       const int numDims);

  /** Get geographic coordinates of projected location.
   *
   * @param coords Array of coordinates (input/output).
   * @param numLocs Number of location.
   * @param numDims Number of spatial dimensions in coordinates.
   */
  void invproject(double* coords,
		  const int numLocs,
		  const int numDims);

  /** Pickle coordinate system to ascii stream.
   *
   * @param s Output stream
   */
  void pickle(std::ostream& s) const;

  /** Unpickle coordinate system from ascii stream.
   *
   * @param s Input stream
   */
  void unpickle(std::istream& s);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  std::string _projection; ///< Name of projection
  std::string _units; ///< Name of units in projection
  std::string _projOptions; ///< options for proj
  
  projPJ _pProj; ///< Pointer to projection
  
}; // class Projector

#include "Projector.icc" // inline methods

#endif // spatialdata_geocoords_projector_hh


// End of file 
