// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "CSPicklerAscii.hh" // implementation of class methods
#include "CoordSys.hh" // USES CoordSys

#include "CSCart.hh" // USES CSCart
#include "CSGeo.hh" // USES CSGeo
#include "CSGeoLocal.hh" // USES CSGeoLocal

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Pickle coordinate system.
void
spatialdata::geocoords::CSPicklerAscii::pickle(std::ostream& s,
                                               const CoordSys* cs) {
    assert(cs);

    cs->pickle(s);
} // pickle


// ----------------------------------------------------------------------
// Unpickle coordinate system.
void
spatialdata::geocoords::CSPicklerAscii::unpickle(std::istream& s,
                                                 CoordSys** cs) {
    assert(cs);

    delete *cs;*cs = 0;

    const int maxIgnore = 128;
    std::string objname;
    s.ignore(maxIgnore, '=');
    s >> objname;
    if (0 == strcasecmp(objname.c_str(), "cartesian")) {
        *cs = new CSCart;
    } else if (0 == strcasecmp(objname.c_str(), "geographic")) {
        *cs = new CSGeo;
    } else if (0 == strcasecmp(objname.c_str(), "local-geographic")) {
        *cs = new CSGeoLocal;
    } else {
        std::ostringstream msg;
        msg << "Could not parse coordinate system object name '"
            << objname << "'\n"
            << "into a known type of coordinate system object.\n"
            << "Known types of coordinate systems:\n"
            << "  'cartesian' and 'geographic'";
        throw std::runtime_error(msg.str().c_str());
    } // else
    (*cs)->unpickle(s);
} // unpickle


// End of file
