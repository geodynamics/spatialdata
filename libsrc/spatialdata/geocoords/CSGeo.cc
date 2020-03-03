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

#include "Converter.hh" // USES Converter
#include "spatialdata/utils/LineParser.hh" // USES LineParser

extern "C" {
#include "proj.h" // USES PROJ
}

#include <cmath> // USES M_PI, cos(), sin()
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
    setCSType(GEOGRAPHIC);
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
    assert( (0 < numLocs && dir) || (0 == numLocs && !dir) );
    assert( (0 < numLocs && coords) || (0 == numLocs && !coords) );

    if (numDims != getSpaceDim()) {
        std::ostringstream msg;
        msg
            << "Number of spatial dimensions of coordinates ("
            << numDims << ") does not match number of spatial dimensions ("
            << getSpaceDim() << ") of coordinate system.";
        throw std::runtime_error(msg.str());
    } // if

    if (numDims > 2) {
        PJ_CONTEXT* const context = NULL;
        PJ* const proj = proj_create(context, _string.c_str());
        const PJ_TYPE projType = proj_get_type(proj);
        proj_destroy(proj);
        switch (projType) {
        case PJ_TYPE_GEOGRAPHIC_2D_CRS:
        case PJ_TYPE_GEOGRAPHIC_3D_CRS:
        case PJ_TYPE_GEODETIC_CRS:
        case PJ_TYPE_PROJECTED_CRS:
            for (size_t i = 0; i < numLocs; ++i) {
                dir[i*numDims+0] = +0.0;
                dir[i*numDims+1] = +0.0;
                dir[i*numDims+2] = +1.0;
            } // for
            break;
        case PJ_TYPE_GEOCENTRIC_CRS: {
            // Surface normal is associated with geodetic lon/lat
            CSGeo csLL;
            csLL.setString("EPSG:4326"); // WGS84
            double* coordsLL = (numLocs*numDims > 0) ? new double[numLocs*numDims] : NULL;
            memcpy(coordsLL, coords, numLocs*numDims*sizeof(double));
            Converter::convert(coordsLL, numLocs, numDims, &csLL, this);
            for (size_t i = 0; i < numLocs; ++i) {
                const double latRad = coordsLL[i*numDims+0] * M_PI/180.0;
                const double lonRad = coordsLL[i*numDims+1] * M_PI/180.0;
                dir[i*numDims+0] = cos(latRad) * cos(lonRad);
                dir[i*numDims+1] = cos(latRad) * sin(lonRad);
                dir[i*numDims+2] = sin(latRad);
            } // for
            delete[] coordsLL;coordsLL = NULL;
            break;
        } // PJ_TYPE_GEOCENTRIC_CRS
        default: {
            std::ostringstream msg;
            msg << "Unknown coordinate system type (" << projType << ") for coordinate system '" << _string << "'.";
            throw std::logic_error(msg.str());
        } // default

        } // switch
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
      << "  space-dim = " << getSpaceDim() << "\n"
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
