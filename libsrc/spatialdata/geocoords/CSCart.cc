// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "CSCart.hh" // implementation of class methods

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <iostream> // USES std::istream, std::ostream

#include <strings.h> // USES strcasecmp
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSCart::CSCart(void) :
    _toMeters(1.0) {
    setCSType(CARTESIAN);
} // constructor


// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSCart::~CSCart(void) {} // destructor


// ----------------------------------------------------------------------
// Copy constructor
spatialdata::geocoords::CSCart::CSCart(const CSCart& cs) :
    CoordSys(cs),
    _toMeters(cs._toMeters) {}


// ----------------------------------------------------------------------
// Clone coordinate system.
spatialdata::geocoords::CoordSys*
spatialdata::geocoords::CSCart::clone(void) const {
    return new CSCart(*this);
} // clone


// ----------------------------------------------------------------------
// Get factor to convert coordinates to meters.
double
spatialdata::geocoords::CSCart::getToMeters(void) const {
    return _toMeters;
} // getToMeters


// ----------------------------------------------------------------------
// Set factor to convert coordinates to meters.
void
spatialdata::geocoords::CSCart::setToMeters(const double scale) {
    if (scale <= 0.0) {
        std::ostringstream msg;
        msg << "Factor to convert coordinates to meters (" << scale << ") must be positive.";
        throw std::invalid_argument(msg.str());
    } // if
    _toMeters = scale;
} // setToMeters


// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSCart::pickle(std::ostream& s) const {
    s << "cartesian {\n"
      << "  to-meters = " << _toMeters << "\n"
      << "  space-dim = " << getSpaceDim() << "\n"
      << "}\n";
} // pickle


// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void
spatialdata::geocoords::CSCart::unpickle(std::istream& s) {
    utils::LineParser parser(s, "//");
    parser.eatwhitespace(true);

    std::string token;
    std::istringstream buffer;
    const int maxIgnore = 256;

    parser.ignore('{');
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
        buffer.ignore(maxIgnore, '=');
        if (0 == strcasecmp(token.c_str(), "to-meters")) {
            buffer >> _toMeters;
        } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
            int dim;
            buffer >> dim;
            setSpaceDim(dim);
        } else {
            std::ostringstream msg;
            msg << "Could not parse '" << token << "' into a CSCart token.\n"
                << "Known CSCart tokens:\n"
                << "  to-meters"
                << "  space-dim";
            throw std::runtime_error(msg.str().c_str());
        } // else
        buffer.str(parser.next());
        buffer.clear();
        buffer >> token;
    } // while
    if (token != "}") {
        throw std::runtime_error("I/O error while parsing CSCart settings.");
    }
} // unpickle


// End of file
