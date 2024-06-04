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

#include "SpatialDB.hh" // Implementation of class methods

#include <cassert> // USES assert()
#include <vector> // USES std::vector

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "spatialdata/units/Parser.hh" // USES Parser

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::SpatialDB::SpatialDB(void) :
    _description("") {}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::SpatialDB::SpatialDB(const char* label) :
    _description(label) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SpatialDB::~SpatialDB(void) {}


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SpatialDB::query(float* vals,
                                         const size_t numVals,
                                         const float* coords,
                                         const size_t numDims,
                                         const spatialdata::geocoords::CoordSys* csQuery) {
    double* coordsD = (numDims > 0) ? new double[numDims] : NULL;
    for (size_t i = 0; i < numDims; ++i) {
        coordsD[i] = coords[i];
    } // for

    double* valsD = (numVals > 0) ? new double[numVals] : NULL;

    const int err = query(valsD, numVals, coordsD, numDims, csQuery);

    for (size_t i = 0; i < numVals; ++i) {
        vals[i] = valsD[i];
    } // for

    delete[] valsD;valsD = NULL;
    delete[] coordsD;coordsD = NULL;

    return err;
} // query


// ----------------------------------------------------------------------
// Perform multiple queries of the database.
void
spatialdata::spatialdb::SpatialDB::multiquery(double* vals,
                                              const size_t numLocsV,
                                              const size_t numValsV,
                                              int* err,
                                              const size_t numLocsE,
                                              const double* coords,
                                              const size_t numLocsC,
                                              const size_t numDimsC,
                                              const spatialdata::geocoords::CoordSys* csQuery) {
    assert(numLocsV == numLocsE);
    assert(numLocsC == numLocsE);
    assert( (!vals && 0 == numLocsV && 0 == numValsV) ||
            (vals && numLocsV > 0 && numValsV > 0) );
    assert( (!err && 0 == numLocsE) ||
            (err && numLocsE > 0) );
    assert( (!coords && 0 == numLocsC && 0 == numDimsC) ||
            (coords && numLocsC > 0 && numDimsC > 0) );

    for (size_t i = 0, indexV = 0, indexC = 0;
         i < numLocsV;
         ++i, indexV += numValsV, indexC += numDimsC) {
        err[i] = query(&vals[indexV], numValsV, &coords[indexC], numDimsC, csQuery);
    } // for
} // multiquery


// ----------------------------------------------------------------------
// Perform multiple queries of the database.
void
spatialdata::spatialdb::SpatialDB::multiquery(float* vals,
                                              const size_t numLocsV,
                                              const size_t numValsV,
                                              int* err,
                                              const size_t numLocsE,
                                              const float* coords,
                                              const size_t numLocsC,
                                              const size_t numDimsC,
                                              const spatialdata::geocoords::CoordSys* csQuery) {
    assert(numLocsV == numLocsE);
    assert(numLocsC == numLocsE);
    assert( (!vals && 0 == numLocsV && 0 == numValsV) ||
            (vals && numLocsV > 0 && numValsV > 0) );
    assert( (!err && 0 == numLocsE) ||
            (err && numLocsE > 0) );
    assert( (!coords && 0 == numLocsC && 0 == numDimsC) ||
            (coords && numLocsC > 0 && numDimsC > 0) );

    for (size_t i = 0, indexV = 0, indexC = 0;
         i < numLocsV;
         ++i, indexV += numValsV, indexC += numDimsC) {
        err[i] = query(&vals[indexV], numValsV, &coords[indexC], numDimsC, csQuery);
    } // for
} // multiquery


#include <iostream>
// ----------------------------------------------------------------------
// Convert values to SI units.
void
spatialdata::spatialdb::SpatialDB::_convertToSI(double* vals,
                                                std::string* units,
                                                const size_t numLocs,
                                                const size_t numVals) {
    assert(vals);
    assert(units);

    spatialdata::units::Parser parser;

    const std::string& none = "none";
    std::vector<double> scales(numVals);
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        if (none != units[iVal]) {
            scales[iVal] = parser.parse(units[iVal].c_str());
        } else {
            scales[iVal] = 1.0;
        } // if/else
    } // for

    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        for (size_t iVal = 0; iVal < numVals; ++iVal) {
            vals[iLoc*numVals+iVal] *= scales[iVal];
        } // for
    } // for
} // _convertToSI


// End of file
