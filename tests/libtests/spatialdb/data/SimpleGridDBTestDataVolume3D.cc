// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include "SimpleGridDBTestDataVolume3D.hh"

const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_numX = 3;
const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_numY = 2;
const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_numZ = 4;

const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_spaceDim = 3;

const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_numVals = 2;

const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_dataDim = 3;

const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_numQueries = 5;

const double spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_dbX[_numX] = {
  -3.0, 1.0, 2.0,
};
const double spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_dbY[_numY] = {
  2.0, 4.0,
};
const double spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_dbZ[_numZ] = {
  -0.5, 0.0, 1.0, 4.0,
};

const double spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_dbData[_numX*_numY*_numZ*_numVals] = {
  1.00000000e-01,  1.10000000e+00, // 0,0,0
  3.00000000e-01,  3.30000000e+00, // 0,0,1
  2.00000000e-01,  2.20000000e+00, // 0,0,2
  1.00000000e-01,  1.10000000e+00, // 0,0,3
  4.00000000e-01,  4.60000000e+00, // 0,1,0
  3.00000000e-01,  3.20000000e+00, // 0,1,1
  7.00000000e-01,  5.20000000e+00, // 0,1,2
  5.00000000e-01,  4.60000000e+00, // 0,1,3
  0.00000000e-01,  1.20000000e+00, // 1,0,0
  1.00000000e-01,  3.40000000e+00, // 1,0,1
  2.00000000e-01,  2.10000000e+00, // 1,0,2
  6.00000000e-01,  1.40000000e+00, // 1,0,3
  9.00000000e-01,  4.70000000e+00, // 1,1,0
  4.00000000e-01,  3.30000000e+00, // 1,1,1
  7.00000000e-01,  5.50000000e+00, // 1,1,2
  6.00000000e-01,  4.70000000e+00, // 1,1,3
  5.00000000e-01,  1.60000000e+00, // 2,0,0
  3.00000000e-01,  3.30000000e+00, // 2,0,1
  8.00000000e-01,  2.80000000e+00, // 2,0,2
  3.00000000e-01,  1.50000000e+00, // 2,0,3
  7.00000000e-01,  4.80000000e+00, // 2,1,0
  4.00000000e-01,  3.40000000e+00, // 2,1,1
  3.00000000e-01,  5.70000000e+00, // 2,1,2
  4.00000000e-01,  4.50000000e+00, // 2,1,3
};

const char* spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_names[_numVals] = {
  "One",
  "Two",
};

const char* spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_units[_numVals] = {
  "m",
  "m",
};

const double spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_queryNearest[_numQueries*(_spaceDim+_numVals)] = {
  -3.2,  3.8,  2.0,  7.00000000e-01,  5.20000000e+00, // (0,1,2)
   1.1,  1.3, -0.1,  1.00000000e-01,  3.40000000e+00, // (1,0,1)
   0.0, -6.0,  5.0,  6.00000000e-01,  1.40000000e+00, // (1,0,3)
   1.6,  3.4, -0.6,  7.00000000e-01,  4.80000000e+00, // (2,1,0)
  -2.0,  3.5,  0.9,  7.00000000e-01,  5.20000000e+00, // (0,1,2)
};

const double spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_queryLinear[_numQueries*(_spaceDim+_numVals)] = {
  -3.0,  4.0,  1.0,   7.00000000e-01,  5.20000000e+00, // (0,1,2)
  -1.0,  2.5,  2.5,   3.62500000e-01,  2.52500000e+00, // (0,5, 0.25, 2.5)
   1.25, 3.0,  0.25,  3.25000000e-01,  3.49062500e+00, // (1.25, 0.5, 1.25)
   0.0,  4.1,  0.0,   0.0, 0.0, // not found
   1.0,  2.0, -0.6,   0.0, 0.0, // not fount
};

const int spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::_errFlags[_numQueries] = {
 0, 0, 0, 1, 1,};

spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::SimpleGridDBTestDataVolume3D(void)
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
} // constructor

spatialdata::spatialdb::SimpleGridDBTestDataVolume3D::~SimpleGridDBTestDataVolume3D(void)
{}


// End of file
