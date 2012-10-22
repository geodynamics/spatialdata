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

#include "SimpleGridDBTestDataArea2D.hh"

const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_numX = 3;
const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_numY = 2;
const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_numZ = 0;

const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_spaceDim = 2;

const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_numVals = 2;

const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_dataDim = 2;

const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_numQueries = 5;

const double spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_dbX[_numX] = {
  -3.0, 1.0, 2.0,
};
const double spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_dbY[_numY] = {
  2.0, 4.0,
};
const double* spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_dbZ = 0;

const double spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_dbData[_numX*_numY*_numVals] = {
  1.00000000e-01,  1.10000000e+00, // 0,0
  0.00000000e-01,  1.20000000e+00, // 1,0
  5.00000000e-01,  1.60000000e+00, // 2,0
  4.00000000e-01,  4.60000000e+00, // 0,1
  9.00000000e-01,  4.70000000e+00, // 1,1
  7.00000000e-01,  4.80000000e+00, // 2,1
};

const char* spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_names[_numVals] = {
  "One",
  "Two",
};

const char* spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_units[_numVals] = {
  "m",
  "m",
};

const double spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_queryNearest[_numQueries*(_spaceDim+_numVals)] = {
  -3.2,  3.8,  4.00000000e-01,  4.60000000e+00, // (0,1)
   1.1,  1.3,  0.00000000e-01,  1.20000000e+00, // (1,0)
   0.0, -6.0,  0.00000000e-01,  1.20000000e+00, // (1,0)
   1.6,  3.4,  7.00000000e-01,  4.80000000e+00, // (2,1)
  -2.0,  3.5,  4.00000000e-01,  4.60000000e+00, // (0,1)
};

const double spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_queryLinear[_numQueries*(_spaceDim+_numVals)] = {
  -3.0,  4.0,   4.00000000e-01,  4.60000000e+00, // (0,1)
  -1.0,  2.5,   2.00000000e-01,  2.02500000e+00, // (0.5, 0.25)
   1.25, 3.0,   4.87500000e-01,  3.01250000e+00, // (1.25, 0.5)
   0.0,  4.1,   0.0, 0.0, // not found
   3.0,  2.0,   0.0, 0.0, // not fount
};

const int spatialdata::spatialdb::SimpleGridDBTestDataArea2D::_errFlags[_numQueries] = {
 0, 0, 0, 1, 1,};

spatialdata::spatialdb::SimpleGridDBTestDataArea2D::SimpleGridDBTestDataArea2D(void)
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

spatialdata::spatialdb::SimpleGridDBTestDataArea2D::~SimpleGridDBTestDataArea2D(void)
{}


// End of file
