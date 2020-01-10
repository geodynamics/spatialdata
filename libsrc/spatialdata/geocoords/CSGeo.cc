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

#include "CSGeo.hh" // implementation of class methods

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <math.h> // USES M_PI
#include <sstream> // USES std::ostringsgream
#include <iostream> // USES std::istream, std::ostream

#include <strings.h> // USES strcasecmp()
#include <stdexcept> // USES std::runtime_error, std::exception
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSGeo::CSGeo(void) :
    _string("EPSG:4326" /* WGS84 */) {
    setSpaceDim(3);
    csType(GEOGRAPHIC);
} // constructor


// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSGeo::~CSGeo(void) {}


// ----------------------------------------------------------------------
// Clone coordinate system.
spatialdata::geocoords::CoordSys*
spatialdata::geocoords::CSGeo::clone(void) const {
    return new CSGeo(*this);
}


// ----------------------------------------------------------------------
// Copy constructor
spatialdata::geocoords::CSGeo::CSGeo(const CSGeo& cs) :
    CoordSys(cs),
    _string(cs._string) {}


// ----------------------------------------------------------------------
// Set string specifying coordinate system.
void
spatialdata::geocoords::CSGeo::setString(const char* value) {
    _string = value;
} // setString


// ----------------------------------------------------------------------
// Get string specifying coordinate system.
const char*
spatialdata::geocoords::CSGeo::getString(void) const {
    return _string.c_str();
} // getString


// ----------------------------------------------------------------------
// Set number of spatial dimensions in coordinate system.
void
spatialdata::geocoords::CSGeo::setSpaceDim(const int ndims) {
    if (( ndims < 2) || ( ndims > 3) ) {
        std::ostringstream msg;
        msg
            << "Number of spatial dimensions (" << ndims
            << ") must be >= 2 and <= 3.";
        throw std::runtime_error(msg.str());
    } // if
    CoordSys::setSpaceDim(ndims);
} // setSpaceDim


// ----------------------------------------------------------------------
// Get outward surface normal.
void
spatialdata::geocoords::CSGeo::computeSurfaceNormal(double* dir,
                                                    const double* coords,
                                                    const size_t numLocs,
                                                    const size_t numDims,
                                                    const double dx) const {
    assert( (0 < numLocs && 0 != dir) ||
            (0 == numLocs && 0 == dir) );
    assert( (0 < numLocs && 0 != coords) ||
            (0 == numLocs && 0 == coords) );

    if (numDims != spaceDim()) {
        std::ostringstream msg;
        msg
            << "Number of spatial dimensions of coordinates ("
            << numDims << ") does not match number of spatial dimensions ("
            << spaceDim() << ") of coordinate system.";
        throw std::runtime_error(msg.str());
    } // if

    if (numDims > 2) {
        // Compute approximate outward surface normal by computing local tangent.
        // Outward surface normal = Cross Product(tx, ty)
        throw std::logic_error(":TODO: @brad CSGeo::radialDir() not yet implemented.");
    } else {
        throw std::runtime_error("Outward surface normal not defined for 2-D geographic coordinates.");
    } // if/else

} // computeSurfaceNormal


// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSGeo::pickle(std::ostream& s) const {
    s << "geographic {\n"
      << "  cs-string = " << _string << "\n"
      << "  space-dim = " << spaceDim() << "\n"
      << "}\n";
} // pickle


// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void
spatialdata::geocoords::CSGeo::unpickle(std::istream& s) {
    utils::LineParser parser(s, "//");
    parser.eatwhitespace(true);

    std::string token;
    std::istringstream buffer;
    const int maxIgnore = 256;
    char cbuffer[maxIgnore];

    // Set parameters to empty values.
    _string = "EPSG:4326"; // WGS84
    setSpaceDim(3);

    parser.ignore('{');
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
        buffer.ignore(maxIgnore, '=');
        if (0 == strcasecmp(token.c_str(), "cs-string")) {
            buffer >> std::ws;
            buffer.get(cbuffer, maxIgnore, '\n');
            setString(cbuffer);
        } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
            int ndims;
            buffer >> ndims;
            setSpaceDim(ndims);
        } else {
            std::ostringstream msg;
            msg << "Could not parse '" << token << "' into a CSGeo token.\n"
                << "Known CSGeo tokens:\n"
                << "  cs-string, space-dim";
            throw std::runtime_error(msg.str().c_str());
        } // else
        buffer.str(parser.next());
        buffer.clear();
        buffer >> token;
    } // while
    if (token != "}") {
        throw std::runtime_error("I/O error while parsing CSGeo settings.");
    }
} // unpickle


// End of file
