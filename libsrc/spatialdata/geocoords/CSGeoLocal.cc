// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "CSGeoLocal.hh" // implementation of class methods

#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <cmath> // USES M_PI, cos(), sin()
#include <sstream> // USES std::ostringsgream
#include <iostream> // USES std::istream, std::ostream

#include <strings.h> // USES strcasecmp()
#include <stdexcept> // USES std::runtime_error, std::exception
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CSGeoLocal::CSGeoLocal(void) :
    _originX(0.0),
    _originY(0.0),
    _yAzimuth(0.0) {}


// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CSGeoLocal::~CSGeoLocal(void) {}


// ----------------------------------------------------------------------
// Clone coordinate system.
spatialdata::geocoords::CoordSys*
spatialdata::geocoords::CSGeoLocal::clone(void) const {
    return new CSGeoLocal(*this);
}


// ----------------------------------------------------------------------
// Copy constructor
spatialdata::geocoords::CSGeoLocal::CSGeoLocal(const CSGeoLocal& cs) :
    CSGeo(cs),
    _originX(cs._originX),
    _originY(cs._originY),
    _yAzimuth(cs._yAzimuth) {}


// ----------------------------------------------------------------------
// Set parameters specifying local coordinate system.
void
spatialdata::geocoords::CSGeoLocal::setLocal(const double originX,
                                             const double originY,
                                             const double yAzimuth) {
    _originX = originX;
    _originY = originY;
    _yAzimuth = yAzimuth;
}


// ----------------------------------------------------------------------
// Get parameters specifying local coordinate system.
void
spatialdata::geocoords::CSGeoLocal::getLocal(double* originX,
                                             double* originY,
                                             double* yAzimuth) const {
    if (originX) { *originX = _originX; }
    if (originY) { *originY = _originY; }
    if (yAzimuth) { *yAzimuth = _yAzimuth; }
}


// ----------------------------------------------------------------------
// Convert coordinates from local coordinate system to geographic coordinate system.
void
spatialdata::geocoords::CSGeoLocal::localToGeographic(double* coords,
                                                      const size_t numLocs,
                                                      const size_t numDims) const {
    const double yAzimuthR = _yAzimuth * M_PI / 180.0;
    const double cosTheta = cos(yAzimuthR);
    const double sinTheta = sin(yAzimuthR);
    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        const double localX = coords[iLoc*numDims+0];
        const double localY = coords[iLoc*numDims+1];
        const double unrotX = cosTheta * localX + sinTheta * localY;
        const double unrotY = -sinTheta * localX + cosTheta * localY;
        coords[iLoc*numDims + 0] = _originX + unrotX;
        coords[iLoc*numDims + 1] = _originY + unrotY;
    } // for
}


// ----------------------------------------------------------------------
// Convert coordinates from geographic coordinate system to local coordinate system.
void
spatialdata::geocoords::CSGeoLocal::geographicToLocal(double* coords,
                                                      const size_t numLocs,
                                                      const size_t numDims) const {
    const double yAzimuthR = _yAzimuth * M_PI / 180.0;
    const double cosTheta = cos(yAzimuthR);
    const double sinTheta = sin(yAzimuthR);
    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        const double unrotX = coords[iLoc*numDims + 0] - _originX;
        const double unrotY = coords[iLoc*numDims + 1] - _originY;
        coords[iLoc*numDims + 0] = cosTheta * unrotX - sinTheta * unrotY;
        coords[iLoc*numDims + 1] = sinTheta * unrotX + cosTheta * unrotY;
    } // for
}


// ----------------------------------------------------------------------
// Pickle coordinate system to ascii stream.
void
spatialdata::geocoords::CSGeoLocal::pickle(std::ostream& s) const {
    s << "local-geographic {\n"
      << "  crs-string = " << getString() << "\n"
      << "  space-dim = " << getSpaceDim() << "\n"
      << "  origin-x = " << _originX << "\n"
      << "  origin-y = " << _originY << "\n"
      << "  y-azimuth = " << _yAzimuth << "\n"
      << "}\n";
} // pickle


// ----------------------------------------------------------------------
// Unpickle coordinate system from ascii stream.
void
spatialdata::geocoords::CSGeoLocal::unpickle(std::istream& s) {
    utils::LineParser parser(s, "//");
    parser.eatwhitespace(true);

    std::string token;
    std::istringstream buffer;
    const int maxIgnore = 512;
    const int maxBuffer = 1024;
    char cbuffer[maxBuffer];

    // Set parameters to empty values.
    setSpaceDim(3);

    parser.ignore('{');
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
        buffer.ignore(maxIgnore, '=');
        if (0 == strcasecmp(token.c_str(), "crs-string")) {
            buffer >> std::ws;
            buffer.get(cbuffer, maxBuffer, '\n');
            this->setString(cbuffer);
        } else if (0 == strcasecmp(token.c_str(), "space-dim")) {
            int ndims;
            buffer >> ndims;
            this->setSpaceDim(ndims);
        } else if (0 == strcasecmp(token.c_str(), "origin-x")) {
            buffer >> _originX;
        } else if (0 == strcasecmp(token.c_str(), "origin-y")) {
            buffer >> _originY;
        } else if (0 == strcasecmp(token.c_str(), "y-azimuth")) {
            buffer >> _yAzimuth;
        } else {
            std::ostringstream msg;
            msg << "Could not parse '" << token << "' into a CSGeoLocal token.\n"
                << "Known CSGeoLocal tokens:\n"
                << "  crs-string, space-dim, origin-x, origin-y, y-azimuth";
            throw std::runtime_error(msg.str().c_str());
        } // else
        buffer.str(parser.next());
        buffer.clear();
        buffer >> token;
    } // while
    if (token != "}") {
        throw std::runtime_error("I/O error while parsing CSGeoLocal settings.");
    }
} // unpickle


// End of file
