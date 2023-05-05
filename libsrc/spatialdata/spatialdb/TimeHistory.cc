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

#include <portinfo>

#include "TimeHistory.hh" // Implementation of class methods

#include "TimeHistoryIO.hh" // USES TimeHistory

#include <cassert> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::TimeHistory::TimeHistory(void) :
    _description(""),
    _filename(""),
    _time(0),
    _amplitude(0),
    _npts(0),
    _ilower(0) {}


// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::TimeHistory::TimeHistory(const char* label) :
    _description(label),
    _filename(""),
    _time(0),
    _amplitude(0),
    _npts(0),
    _ilower(0) {}


// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::TimeHistory::~TimeHistory(void) {
    delete[] _time;_time = 0;
    delete[] _amplitude;_amplitude = 0;
    _npts = 0;
} // destructor


// ----------------------------------------------------------------------
// Open the time history and prepare for querying.
void
spatialdata::spatialdb::TimeHistory::open(void) {
    TimeHistoryIO::read(&_time, &_amplitude, &_npts, _filename.c_str());
    _ilower = 0;
} // open


// ----------------------------------------------------------------------
// Close the time history.
void
spatialdata::spatialdb::TimeHistory::close(void) {
    delete[] _time;_time = 0;
    delete[] _amplitude;_amplitude = 0;
    _npts = 0;
} // close


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::TimeHistory::query(double* value,
                                           const double t) {
    assert(0 != _npts);

    *value = 0.0;
    if (_npts > 1) {
        if (t < _time[_ilower]) {
            while (_ilower > 0) {
                if (t >= _time[_ilower]) {
                    break;
                }
                --_ilower;
            } // while
        } else if (t > _time[_ilower+1]) {
            const size_t imax = _npts-2;
            while (_ilower < imax) {
                if (t <= _time[_ilower+1]) {
                    break;
                }
                ++_ilower;
            } // while
        } // if/else

        assert(_ilower < _npts-1);
        if (( t >= _time[_ilower]) && ( t <= _time[_ilower+1]) ) {
            const double tL = _time[_ilower];
            const double tU = _time[_ilower+1];
            const double wtL = (tU - t) / (tU - tL);
            const double wtU = (t - tL) / (tU - tL);
            *value = wtL * _amplitude[_ilower] + wtU * _amplitude[_ilower+1];
        } else {
            return 1;
        } // else
    } else {
        *value = _amplitude[0];
    } // else

    return 0;
} // query


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::TimeHistory::query(float* value,
                                           const float t) { // query
    double valueD = 0.0;
    const double tD = t;

    const int err = query(&valueD, tD);
    *value = valueD;
    return err;
} // query


// End of file
