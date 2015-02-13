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

/** @file libsrc/units/Parser.hh
 *
 * @brief C++ interface to Pyre units parser.
 */

#if !defined(spatialdata_units_parser_hh)
#define spatialdata_units_parser_hh

#include "unitsfwd.hh"

#include <Python.h>

/// C++ interface to Pyre units parser.
class spatialdata::units::Parser
{ // class Parser
  friend class TestParser; // Unit testing

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /* MATT- I am not sure if we want just a single static method or we
   *   want an object so that any setup/teardown is done once per
   *   instantiation rather than each call to parse.
   */

  /// Default constructor
  Parser(void);

  /// Default destructor
  ~Parser(void);

  /** Get SI scaling factor for units given by string. To get value in
   * SI units, multiple value given by units by scaling factor.
   *
   * @returns Scaling factor to convert to SI units.
   */
  double parse(const char* units);

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  PyObject* _parser;
  bool _alreadyInitialized;

}; // class Parser

#endif // spatialdata_units_parser_hh


// End of file 
