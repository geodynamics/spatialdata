// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
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
  _label(""),
  _filename(""),
  _time(0),
  _amplitude(0),
  _npts(0),
  _ilower(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::TimeHistory::TimeHistory(const char* label) :
  _label(label),
  _filename(""),
  _time(0),
  _amplitude(0),
  _npts(0),
  _ilower(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::TimeHistory::~TimeHistory(void)
{ // destructor
  delete[] _time; _time = 0;
  delete[] _amplitude; _amplitude = 0;
  _npts = 0;
} // destructor

// ----------------------------------------------------------------------
// Open the time history and prepare for querying.
void
spatialdata::spatialdb::TimeHistory::open(void)
{ // open
  TimeHistoryIO::read(&_time, &_amplitude, &_npts, _filename.c_str());
  _ilower = 0;
} // open

// ----------------------------------------------------------------------
// Close the time history.
void
spatialdata::spatialdb::TimeHistory::close(void)
{ // close
  delete[] _time; _time = 0;
  delete[] _amplitude; _amplitude = 0;
  _npts = 0;
} // close

#include <iostream>
// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::TimeHistory::query(double* value,
      const double t)
{ // query
  assert(0 != _npts);
  
  if (_npts > 1) {
    if (t < _time[_ilower]) {
      while (_ilower > 0) {
	if (t >= _time[_ilower])
	  break;
	--_ilower;
      } // while
    } else if (t > _time[_ilower+1]) {
      const int imax = _npts-2;
      while(_ilower < imax) {
	if (t <= _time[_ilower+1])
	  break;
	++_ilower;
      } // while
    } // if/else

    assert(_ilower < _npts-1);
    if (t >= _time[_ilower] && t <= _time[_ilower+1]) {
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


// End of file 
