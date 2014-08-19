// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include "SimpleGridDBTestDataLine3D.hh"

const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_numX = 1;
const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_numY = 1;
const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_numZ = 3;

const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_spaceDim = 3;

const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_numVals = 2;

const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_dataDim = 1;

const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_numQueries = 5;

const double spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_dbX[_numX] = {
  2.0,
};
const double spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_dbY[_numY] = {
  0.6,
};
const double spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_dbZ[_numZ] = {
  -3.0, 1.0, 2.0,
};

const double spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_dbData[_numX*_numY*_numZ*_numVals] = {
  1.00000000e-01,  1.10000000e+00, // 0,0
  0.00000000e-01,  1.20000000e+00, // 1,0
  5.00000000e-01,  1.60000000e+00, // 2,0
};

const char* spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_names[_numVals] = {
  "One",
  "Two",
};

const char* spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_units[_numVals] = {
  "m",
  "m",
};

const double spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_queryNearest[_numQueries*(_spaceDim+_numVals)] = {
  3.8, 3.8, -3.2,   1.00000000e-01,  1.10000000e+00, // (0)
  1.3, 6.3,  1.1,   0.00000000e-01,  1.20000000e+00, // (1)
  6.0, 5.0,  0.0,   0.00000000e-01,  1.20000000e+00, // (1)
  3.4, 4.4,  1.6,   5.00000000e-01,  1.60000000e+00, // (2)
  3.5, 7.5, -2.0,   1.00000000e-01,  1.10000000e+00, // (0)
};

const double spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_queryLinear[_numQueries*(_spaceDim+_numVals)] = {
  3.8, 3.8, -3.0,   1.00000000e-01,  1.10000000e+00, // (0)
  1.3, 6.3, -1.0,   0.50000000e-01,  1.05000000e+00, // (0.5)
  6.0, 5.0,  1.25,  0.12500000e-01,  1.30000000e+00, // (1.25)
  3.4, 4.4, -4.0,   0.0, 0.0, // not found
  3.5, 7.5,  3.0,   0.0, 0.0, // not fount
};

const int spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_errFlags[_numQueries] = {
 0, 0, 0, 1, 1,};

const char* spatialdata::spatialdb::SimpleGridDBTestDataLine3D::_filename = "data/grid_line3d.spatialdb";

spatialdata::spatialdb::SimpleGridDBTestDataLine3D::SimpleGridDBTestDataLine3D(void)
{ // constructor
  numX = _numX;
  numY = _numY;
  numZ = _numZ;
  spaceDim = _spaceDim;
  numVals = _numVals;
  dataDim = _dataDim;
  numQueries = _numQueries;
  dbX = const_cast<double*>(_dbX);
  dbY = const_cast<double*>(_dbY);
  dbZ = const_cast<double*>(_dbZ);
  dbData = const_cast<double*>(_dbData);
  names = const_cast<char**>(_names);
  units = const_cast<char**>(_units);
  queryNearest = const_cast<double*>(_queryNearest);
  queryLinear = const_cast<double*>(_queryLinear);
  errFlags = const_cast<int*>(_errFlags);
  filename = const_cast<char*>(_filename);
} // constructor

spatialdata::spatialdb::SimpleGridDBTestDataLine3D::~SimpleGridDBTestDataLine3D(void)
{}


// End of file
