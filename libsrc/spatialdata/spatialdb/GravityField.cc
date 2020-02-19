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
    _gravityDir[0] = +0.0;
    _gravityDir[1] = +0.0;
    _gravityDir[2] = -1.0;

    _queryValues[0] = 0;
    _queryValues[1] = 1;
    _queryValues[2] = 2;
} // constructor


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::GravityField::~GravityField(void) {
    _querySize = 0;
} // destructor


// ----------------------------------------------------------------------
// Set direction of gravitational body force.
void
spatialdata::spatialdb::GravityField::setGravityDir(const double x,
                                                    const double y,
                                                    const double z) {
    const double mag = std::max(1.0e-8, sqrt(x*x + y*y + z*z));
    _gravityDir[0] = x / mag;
    _gravityDir[1] = y / mag;
    _gravityDir[2] = z / mag;
} // setGravityDir


// ----------------------------------------------------------------------
// Set gravitational acceleration.
void
spatialdata::spatialdb::GravityField::setGravityAcc(const double acceleration) {
    _acceleration = acceleration;
} // setGravityAcc


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
spatialdata::spatialdb::GravityField::setQueryValues(const char* const* names,
                                                     const size_t numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values (" << numVals << ") for query of gravity field spatial database " << getLabel()
            << "\n must be positive.\n";
        throw std::runtime_error(msg.str());
    } else if (numVals > 3) {
        std::ostringstream msg;
        msg << "Number of values (" << numVals << ") for query of gravity field spatial database " << getLabel()
            << "\n must be 1, 2, or 3.\n";
        throw std::runtime_error(msg.str());
    } // if/else
    assert(names && 0 < numVals);

    _querySize = numVals;
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        if (0 == strcasecmp(names[iVal], "gravity_field_x")) {
            _queryValues[iVal] = 0;
        } else if (0 == strcasecmp(names[iVal], "gravity_field_y")) {
            _queryValues[iVal] = 1;
        } else if (0 == strcasecmp(names[iVal], "gravity_field_z")) {
            _queryValues[iVal] = 2;
        } else {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << getLabel() << "'. Available values are: 'gravity_field_x', 'gravity_field_y', 'gravity_field_z'.";
            throw std::runtime_error(msg.str());
        } // if
    } // for
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::GravityField::query(double* vals,
                                            const size_t numVals,
                                            const double* coords,
                                            const size_t numDims,
                                            const spatialdata::geocoords::CoordSys* cs) {
    assert(cs);

    if (0 == _querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << getLabel() << "\n"
            << "have not been set. Please call setQueryValues() before query().\n";
        throw std::runtime_error(msg.str());
    } else if (numVals != _querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getLabel() << "\n"
            << "(" << _querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::runtime_error(msg.str());
    } // if

    if (geocoords::CoordSys::CARTESIAN == cs->getCSType()) {
        for (size_t i = 0; i < _querySize; ++i) {
            vals[i] = _acceleration*_gravityDir[_queryValues[i]];
        } // for
    } else {
        const geocoords::CSGeo* csGeo = dynamic_cast<const geocoords::CSGeo*>(cs);
        double surfaceNormal[3];
        const int numLocs = 1;
        csGeo->computeSurfaceNormal(surfaceNormal, coords, numLocs, numDims);
        for (size_t i = 0; i < _querySize; ++i) {
            vals[i] = -_acceleration * surfaceNormal[_queryValues[i]];
        } // for
    } // if/else

    return 0;
} // query


// End of file
