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

#include "CoordSys.h" // implementation of class methods

extern "C" {
#include "proj_api.h" // USES PROJ4
};

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CoordSys::CoordSys(void) :
  _pCS(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CoordSys::~CoordSys(void)
{ // destructor
  pj_free(_pCS);
  _pCS = 0;
} // destructor

// ----------------------------------------------------------------------
// Initialize coordinate system.
void 
spatialdata::geocoords::CoordSys::initialize(void)
{ // initialize
  pj_free(_pCS);
  std::string csString = _projCSString();
  _pCS = pj_init_plus(csString.c_str());
  if (0 == _pCS) {
    std::ostringstream msg;
    msg << "Error while initializing coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n"
	<< "  proj string: " << csString << "\n";
    throw std::runtime_error(msg.str());
  } // if
} // initialize

// version
// $Id$

// End of file 
