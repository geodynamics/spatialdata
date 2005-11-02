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

#include "CSPicklerAscii.h" // implementation of class methods
#include "CoordSys.h" // USES CoordSys

#include "CSCart.h" // USES CSCart
#include "CSGeo.h" // USES CSGeo
#include "CSGeoLocalCart.h" // USES CSGeoLocalCart
#include "CSGeoProj.h" // USES CSGeoProj

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
// Pickle coordinate system.
void
spatialdata::geocoords::CSPicklerAscii::pickle(std::ostream& s,
					       const CoordSys* pCS)
{ // pickle
  pCS->pickle(s);
} // pickle

// ----------------------------------------------------------------------
// Unpickle coordinate system.
void
spatialdata::geocoords::CSPicklerAscii::unpickle(std::istream& s,
						 CoordSys** ppCS)
{ // unpickle
  FIREWALL(0 != ppCS);

  const int maxIgnore = 128;
  std::string objname;
  s.ignore(maxIgnore, '=');
  s >> objname;
  if (0 == strcasecmp(objname.c_str(), "cartesian")) 
    *ppCS = new CSCart;
  else if (0 == strcasecmp(objname.c_str(), "geographic"))
    *ppCS = new CSGeo;
  else if (0 == strcasecmp(objname.c_str(), "geo-local-cartesian"))
    *ppCS = new CSGeoLocalCart;
  else if (0 == strcasecmp(objname.c_str(), "geo-projected"))
    *ppCS = new CSGeoProj;
  else {
    std::ostringstream msg;
    msg << "Could not parse coordinate system object name '" 
	<< objname << "'\n"
	<< "into a known type of coordinate system object.\n"
	<< "Known types of coordinate systems:\n"
	<< "  cartesian, geographic, geo-local-cartesian, geo-projected";
    throw std::runtime_error(msg.str().c_str());
  } // else
  (*ppCS)->unpickle(s);
} // unpickle

// version
// $Id$

// End of file 