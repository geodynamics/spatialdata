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

#include "CSCart.hh" // implementation of class methods

#include <iostream> // USES std::istream, std::ostream

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSCart::CSCart(void) :
  _toMeters(1.0),
  _spaceDim(3)
{ // constructor
  csType(CARTESIAN);
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSCart::~CSCart(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Copy constructor
spatialdata::geocoords::CSCart::CSCart(const CSCart& cs) :
  CoordSys(cs),
  _toMeters(cs._toMeters),
  _spaceDim(cs._spaceDim)
{ // copy constructor
} // copy constructor

// ----------------------------------------------------------------------
// Initialize coordinate system.
void 
spatialdata::geocoords::CSCart::initialize(void)
{ // initialize
} // initialize

// ----------------------------------------------------------------------
// Set factor to convert coordinates to meters.
void
spatialdata::geocoords::CSCart::toMeters(const double scale)
{ // toMeters
  if (scale <= 0.0) {
    std::ostringstream msg;
    msg
      << "Factor to convert coordinates to meters (" << scale
      << ") must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  _toMeters = scale;
} // toMeters

// ----------------------------------------------------------------------
// Set number of spatial dimensions in coordinate system.
void
spatialdata::geocoords::CSCart::spaceDim(const int ndims)
{ // spaceDim
  if (ndims < 1 || ndims > 3) {
    std::ostringstream msg;
    msg
      << "Number of spatial dimensions (" << ndims
      << ") must be >= 1 and <= 3.";
    throw std::runtime_error(msg.str());
  } // if
  _spaceDim = ndims;
} // spaceDim

// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSCart::pickle(std::ostream& s) const
{ // pickle
  s << "cartesian {\n"
    << "  to-meters = " << _toMeters << "\n"
    << "  space-dim = " << _spaceDim << "\n"
    << "}\n";
} // pickle

// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void 
spatialdata::geocoords::CSCart::unpickle(std::istream& s)
{ // unpickle
  std::string token;
  const int maxIgnore = 128;

  s.ignore(maxIgnore, '{');
  s >> token;
  while (s.good() && token != "}") {
    s.ignore(maxIgnore, '=');
    if (0 == strcasecmp(token.c_str(), "to-meters")) {
      s >> _toMeters;
    } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
      s >> _spaceDim;
    } else {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into a CSCart token.\n"
	  << "Known CSCart tokens:\n"
	  << "  to-meters"
	  << "  space-dim";
      throw std::runtime_error(msg.str().c_str());
    } // else
    s >> token;
  } // while
  if (!s.good())
    throw std::runtime_error("I/O error while parsing CSCart settings.");
} // unpickle


// End of file 
