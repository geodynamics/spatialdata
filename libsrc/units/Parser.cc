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

#include <portinfo>

#include "Parser.hh" // implementation of class methods

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::units::Parser::Parser(void)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::units::Parser::~Parser(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Get SI scaling factor for units given by string. To get value in
// SI units, multiple value given by units by scaling factor.
double
spatialdata::units::Parser::parse(const char* units)
{ // parse
  double scale = 1.0;

  /* Replicate Python functionality given by
   *
   * import pyre.units
   * p = pyre.units.parser()
   * x = p.parse(units) [units is a string]
   * scale = x.value
   *
   * Any nontrivial setup/teardown should be moved to
   * constructor/destructor.
   */

  return scale;
} // parser


// End of file 
