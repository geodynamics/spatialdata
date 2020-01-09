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

#include "Converter.hh" // implementation of class methods

#include "CoordSys.hh" // USES CoordSys
#include "CSGeo.hh" // USES CSGeo
#include "CSCart.hh" // USES CSCart

extern "C" {
#include "proj.h" // USES PROJ
}

#include <strings.h> // USES strcasecmp()
#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
// Convert coordinates from source coordinate system to destination
// coordinate system.
void
spatialdata::geocoords::Converter::convert(double* coords,
                                           const size_t numLocs,
                                           const size_t numDims,
                                           const CoordSys* csDest,
                                           const CoordSys* csSrc) {
    assert( (0 < numLocs && 0 != coords) ||
            (0 == numLocs && 0 == coords));
    assert(csDest);
    assert(csSrc);

    if (csSrc->csType() != csDest->csType()) {
        throw std::runtime_error("Cannot convert between coordinate systems "
                                 "of different types.");
    } // if
    if (csSrc->spaceDim() != csDest->spaceDim()) {
        std::ostringstream msg;
        msg << "Cannot convert between coordinate systems with different "
            << "spatial dimensions.\n"
            << "Source and destination coordinate systems have "
            << csSrc->spaceDim() << " and " << csDest->spaceDim()
            << " dimensions, respectively.";
        throw std::runtime_error(msg.str());
    } // if

    switch (csSrc->csType()) {
    case spatialdata::geocoords::CoordSys::GEOGRAPHIC:
    { // GEOGRAPHIC
        const CSGeo* csGeoDest = dynamic_cast<const CSGeo*>(csDest);
        const CSGeo* csGeoSrc = dynamic_cast<const CSGeo*>(csSrc);
        _convert(coords, numLocs, numDims, csGeoDest, csGeoSrc);
        break;
    } // GEOGRAPHIC
    case spatialdata::geocoords::CoordSys::CARTESIAN:
    { // CARTESIAN
        const CSCart* csCartDest = dynamic_cast<const CSCart*>(csDest);
        const CSCart* csCartSrc = dynamic_cast<const CSCart*>(csSrc);
        _convert(coords, numLocs, numDims, csCartDest, csCartSrc);
        break;
    } // CARTESIAN
    default:
        throw std::runtime_error("Could not parse coordinate system type.");
    } // switch
} // convert


// ----------------------------------------------------------------------
// Convert coordinates from source geographic coordinate system to
// destination geographic coordinate system.
void
spatialdata::geocoords::Converter::_convert(double* coords,
                                            const size_t numLocs,
                                            const size_t numDims,
                                            const CSGeo* csDest,
                                            const CSGeo* csSrc) {
    assert(csDest);
    assert(csSrc);
    assert( (0 < numLocs && 0 != coords) ||
            (0 == numLocs && 0 == coords));

    double* const x = (numDims >= 2) ? coords + 0 : NULL;
    double* const y = (numDims >= 2) ? coords + 1 : NULL;
    double* const z = (numDims >= 3) ? coords + 2 : NULL;
    const size_t stride = numDims * sizeof(double);

    PJ* proj = proj_create_crs_to_crs(NULL, csSrc->getString(), csDest->getString(), NULL);
    if (!proj) {
        std::stringstream msg;
        msg << "Error creating projection from '" << csSrc->getString() << "' to '" << csDest->getString() << "'.\n"
            << proj_errno_string(proj_errno(proj));
        throw std::runtime_error(msg.str());
    } // if

    const size_t numSuccessful =
        proj_trans_generic(proj, PJ_FWD,
                           x, stride, numLocs,
                           y, stride, numLocs,
                           z, stride, numLocs,
                           NULL, 0, 0);
    if (numSuccessful < numLocs) {
        std::ostringstream msg;
        msg << "Error while converting coordinates:\n"
            << "  " << proj_errno_string(proj_errno(proj));
        proj_destroy(proj);
        throw std::runtime_error(msg.str());
    } // if

    proj_destroy(proj);
} // convert


// ----------------------------------------------------------------------
// Convert coordinates from source Cartesian coordinate system to
// destination Cartesian coordinate system.
void
spatialdata::geocoords::Converter::_convert(double* coords,
                                            const size_t numLocs,
                                            const size_t numDims,
                                            const CSCart* csDest,
                                            const CSCart* csSrc) {
    assert(csDest);
    assert(csSrc);
    assert( (0 < numLocs && 0 != coords) ||
            (0 == numLocs && 0 == coords));

    const int size = numLocs*numDims;
    const double scale = csSrc->toMeters() / csDest->toMeters();
    for (int i = 0; i < size; ++i) {
        coords[i] *= scale;
    } // for
} // convert


// End of file
