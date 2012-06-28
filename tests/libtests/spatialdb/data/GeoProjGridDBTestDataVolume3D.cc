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

#include "GeoProjGridDBTestDataVolume3D.hh"

const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_numX = 3;
const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_numY = 2;
const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_numZ = 4;

const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_spaceDim = 3;

const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_numVals = 2;

const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_dataDim = 3;

const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_numQueries = 5;

const double spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_dbX[_numX] = {
  -3.0, 1.0, 2.0,
};
const double spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_dbY[_numY] = {
  2.0, 4.0,
};
const double spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_dbZ[_numZ] = {
  -0.5, 0.0, 1.0, 4.0,
};

const double spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_dbData[_numX*_numY*_numZ*_numVals] = {
  1.00000000e-01,  1.10000000e+00,
  3.00000000e-01,  3.30000000e+00,
  2.00000000e-01,  2.20000000e+00,
  1.00000000e-01,  1.10000000e+00,
  4.00000000e-01,  4.60000000e+00,
  3.00000000e-01,  3.20000000e+00,
  7.00000000e-01,  5.20000000e+00,
  5.00000000e-01,  4.60000000e+00,
  0.00000000e-01,  1.20000000e+00,
  1.00000000e-01,  3.40000000e+00,
  2.00000000e-01,  2.10000000e+00,
  6.00000000e-01,  1.40000000e+00,
  9.00000000e-01,  4.70000000e+00,
  4.00000000e-01,  3.30000000e+00,
  7.00000000e-01,  5.50000000e+00,
  6.00000000e-01,  4.70000000e+00,
  5.00000000e-01,  1.60000000e+00,
  3.00000000e-01,  3.30000000e+00,
  8.00000000e-01,  2.80000000e+00,
  3.00000000e-01,  1.50000000e+00,
  7.00000000e-01,  4.80000000e+00,
  4.00000000e-01,  3.40000000e+00,
  3.00000000e-01,  5.70000000e+00,
  4.00000000e-01,  4.50000000e+00,
};

const char* spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_names[] = {
  "One",
  "Two",
};

const char* spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_units[] = {
  "m",
  "m",
};

const double spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_queryNearest[] = {
  4.38173419e+00,  8.36254772e+00,  8.74899281e+00,  1.00000000e-01,  1.10000000e+00,
  2.35495601e+00,  1.00264422e+01,  9.00123360e+00,  5.00000000e-01,  4.60000000e+00,
  3.91112675e+00,  1.07838373e+01,  9.69020768e+00,  7.00000000e-01,  5.20000000e+00,
  3.87701461e+00,  1.04910673e+01,  9.08761157e+00,  7.00000000e-01,  5.20000000e+00,
  3.01795532e+00,  8.84019490e+00,  8.79326896e+00,  3.00000000e-01,  3.30000000e+00,
};

const double spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_queryLinear[] = {
  4.38173419e+00,  8.36254772e+00,  8.74899281e+00,  1.35000000e-01,  1.49500000e+00,
  2.35495601e+00,  1.00264422e+01,  9.00123360e+00,  4.10000000e-01,  3.85500000e+00,
  3.91112675e+00,  1.07838373e+01,  9.69020768e+00,  0.00000000e+00,  0.00000000e+00,
  3.87701461e+00,  1.04910673e+01,  9.08761157e+00,  5.30000000e-01,  4.42000000e+00,
  3.01795532e+00,  8.84019490e+00,  8.79326896e+00,  2.00000000e-01,  2.15500000e+00,
};

const int spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::_errFlags[] = {
 0, 0, 1, 0, 0,};

spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::GeoProjGridDBTestDataVolume3D(void)
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

spatialdata::spatialdb::GeoProjGridDBTestDataVolume3D::~GeoProjGridDBTestDataVolume3D(void)
{}


// End of file
