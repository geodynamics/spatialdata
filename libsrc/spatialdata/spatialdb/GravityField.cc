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

#include "GravityField.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <cmath> // USES sqrt()
#include <strings.h> // USES strcasecmp()
#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::GravityField::GravityField(void) :
    SpatialDB("Gravity field"),
    _acceleration(9.80665), // m/s^2
    _querySize(3) {
    _queryVals[0] = 0;
    _queryVals[1] = 1;
    _queryVals[2] = 2;
} // constructor


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::GravityField::~GravityField(void) {
    _querySize = 0;
} // destructor


// ----------------------------------------------------------------------
// Set direction of gravitational body force.
void
spatialdata::spatialdb::GravityField::gravityDir(const double x,
                                                 const double y,
                                                 const double z) {
    const double mag = std::max(1.0e-8, sqrt(x*x + y*y + z*z));
    _gravityDir[0] = x / mag;
    _gravityDir[1] = y / mag;
    _gravityDir[2] = z / mag;
} // gravityDir


// ----------------------------------------------------------------------
// Set gravitational acceleration.
void
spatialdata::spatialdb::GravityField::gravityAcc(const double acceleration) {
    _acceleration = acceleration;
} // gravityAcc


// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::GravityField::open(void) {}


// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::GravityField::close(void) {}


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::GravityField::queryVals(const char* const* names,
                                                const int numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values (" << numVals << ") for query of gravity field spatial database " << label()
            << "\n must be positive.\n";
        throw std::runtime_error(msg.str());
    } else if (numVals > 3) {
        std::ostringstream msg;
        msg << "Number of values (" << numVals << ") for query of gravity field spatial database " << label()
            << "\n must be 1, 2, or 3.\n";
        throw std::runtime_error(msg.str());
    } // if/else
    assert(names && 0 < numVals);

    _querySize = numVals;
    for (int iVal = 0; iVal < numVals; ++iVal) {
        if (0 == strcasecmp(names[iVal], "gravity_field_x")) {
            _queryVals[iVal] = 0;
        } else if (0 == strcasecmp(names[iVal], "gravity_field_y")) {
            _queryVals[iVal] = 1;
        } else if (0 == strcasecmp(names[iVal], "gravity_field_z")) {
            _queryVals[iVal] = 2;
        } else {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << label() << "'. Available values are: 'gravity_field_x', 'gravity_field_y', 'gravity_field_z'.";
            throw std::runtime_error(msg.str());
        } // if
    } // for
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::GravityField::query(double* vals,
                                            const int numVals,
                                            const double* coords,
                                            const int numDims,
                                            const spatialdata::geocoords::CoordSys* cs) {
    assert(cs);

    if (0 == _querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << label() << "\n"
            << "have not been set. Please call queryVals() before query().\n";
        throw std::runtime_error(msg.str());
    } else if (numVals != _querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << label() << "\n"
            << "(" << _querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::runtime_error(msg.str());
    } // if

    if (geocoords::CoordSys::CARTESIAN == cs->csType()) {
        for (int i = 0; i < _querySize; ++i) {
            vals[i] = _acceleration*_gravityDir[_queryVals[i]];
        } // for
    } else {
        const geocoords::CSGeo* csGeo = dynamic_cast<const geocoords::CSGeo*>(cs);
        double surfaceNormal[3];
        const int numLocs = 1;
        csGeo->computeSurfaceNormal(surfaceNormal, coords, numLocs, numDims);
        for (int i = 0; i < _querySize; ++i) {
            vals[i] = -_acceleration * surfaceNormal[_queryVals[i]];
        } // for
    } // if/else

    return 0;
} // query


// End of file
