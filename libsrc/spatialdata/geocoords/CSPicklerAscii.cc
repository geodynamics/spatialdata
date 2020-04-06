// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "CSPicklerAscii.hh" // implementation of class methods
#include "CoordSys.hh" // USES CoordSys

#include "CSCart.hh" // USES CSCart
#include "CSGeo.hh" // USES CSGeo

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
