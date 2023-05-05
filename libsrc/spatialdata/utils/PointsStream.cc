// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include "PointsStream.hh" // Implementation of class methods

#include <iostream> // USES std::cout, std::cin
#include <fstream> // USES std::ifstream, std::ofstream
#include <iomanip> // USES std::setprecision(), std::width()
#include <vector> // USES std::vector
#include <assert.h> // USES assert()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error

// ----------------------------------------------------------------------
// Default constructor
spatialdata::utils::PointsStream::PointsStream(void) :
    _filename(""),
    _commentFlag("#"),
    _fieldWidth(14),
    _precision(5) {}


// ----------------------------------------------------------------------
// Default destructor
spatialdata::utils::PointsStream::~PointsStream(void) {}


// ----------------------------------------------------------------------
// Read points from stdin.
void
spatialdata::utils::PointsStream::read(double** ppPoints,
                                       size_t* pNumPts,
                                       size_t* pNumDims) const {
    std::istream* sin = !_filename.empty() ? new std::ifstream(_filename.c_str()) : &std::cin;

    if (!sin || !sin->good()) {
        const std::string name = !_filename.length() ? _filename : "std::cin";
        std::ostringstream msg;
        msg << "Could not open intput stream '" << name << "' for reading points.";
        throw std::runtime_error(msg.str());
    } // if

    size_t numPts = 0;
    size_t numDims = 3;

    const size_t initialCapacity = numDims*256;
    std::vector<double> buffer(initialCapacity);

    size_t capacity = initialCapacity;
    size_t index = 0;
    while (!sin->eof() && sin->good()) {
        if (numPts*numDims >= capacity) {
            capacity *= 2;
            buffer.resize(capacity);
        } // if
        for (size_t iDim = 0; iDim < numDims; ++iDim) {
            *sin >> buffer[index++];
        }
        if (sin->good()) {
            ++numPts;
        }
    } // while
    if (!sin->eof() && !sin->good()) {
        const std::string name = !_filename.empty() ? _filename : "std::cin";
        std::ostringstream msg;
        msg << "Error occurred while reading points from input stream '" << name << "'.";
        throw std::runtime_error(msg.str());
    } // if

    if (&std::cin != sin) {
        delete sin;
    }

    if (ppPoints) {
        const size_t size = numPts * numDims;
        double* pPoints = (size > 0) ? new double[size] : 0;
        for (size_t i = 0; i < size; ++i) {
            pPoints[i] = buffer[i];
        }
        *ppPoints = pPoints;
    } // if
    if (0 != pNumPts) {
        *pNumPts = numPts;
    }
    if (0 != pNumDims) {
        *pNumDims = numDims;
    }
} // read


// ----------------------------------------------------------------------
// Write points to stdout.
void
spatialdata::utils::PointsStream::write(const double* pPoints,
                                        const size_t numPts,
                                        const size_t numDims) const { // write
    std::ostream* pOut = !_filename.empty() ? new std::ofstream(_filename.c_str()) : &std::cout;

    if (!pOut || !pOut->good()) {
        const std::string name = !_filename.empty() ? _filename : "std::cout";
        std::ostringstream msg;
        msg << "Could not open output stream '" << name << "' for writing points.";
        throw std::runtime_error(msg.str());
    } // if

    *pOut
        << std::resetiosflags(std::ios::fixed)
        << std::setiosflags(std::ios::scientific)
        << std::setprecision(_precision);

    for (size_t iPoint = 0, index = 0; iPoint < numPts; ++iPoint) {
        for (size_t iDim = 0; iDim < numDims; ++iDim) {
            *pOut << std::setw(_fieldWidth) << pPoints[index++];
        }
        *pOut << "\n";
    } // for

    if (!pOut->good()) {
        const std::string name = !_filename.empty() ? _filename : "std::cout";
        std::ostringstream msg;
        msg << "Error occurred while writing points to output stream '" << name << "'.";
        throw std::runtime_error(msg.str());
    } // if

    if (&std::cout != pOut) {
        delete pOut;
    } // if
} // write


// End of file
