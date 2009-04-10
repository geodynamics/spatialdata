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

/** @file libsrc/units/Parser.hh
 *
 * @brief C++ interface to Pyre units parser.
 */

#if !defined(spatialdata_units_parser_hh)
#define spatialdata_units_parser_hh

#include "unitsfwd.hh"

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


}; // class Parser

#endif // spatialdata_units_parser_hh


// End of file 
