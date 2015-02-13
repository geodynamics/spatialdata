// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

// DO NOT EDIT THIS FILE
// This file was generated from python application simpledbdataarea3D.

#include "SimpleDBTestDataArea3D.hh"

const int spatialdata::spatialdb::SimpleDBTestDataArea3D::_numLocs = 6;

const int spatialdata::spatialdb::SimpleDBTestDataArea3D::_spaceDim = 3;

const int spatialdata::spatialdb::SimpleDBTestDataArea3D::_numVals = 2;

const int spatialdata::spatialdb::SimpleDBTestDataArea3D::_dataDim = 2;

const int spatialdata::spatialdb::SimpleDBTestDataArea3D::_numQueries = 4;

const double spatialdata::spatialdb::SimpleDBTestDataArea3D::_dbCoords[] = {
  3.40000000e+00,  9.50000000e+00,  8.70000000e+00,
  4.29442719e+00,  9.50000000e+00,  9.14721360e+00,
  6.97770876e+00,  9.50000000e+00,  1.04888544e+01,
  7.63236243e+00,  1.21186147e+01,  9.17954704e+00,
  3.83643578e+00,  1.12457431e+01,  7.82712844e+00,
  4.05465367e+00,  1.21186147e+01,  7.39069266e+00,
};

const double spatialdata::spatialdb::SimpleDBTestDataArea3D::_dbData[] = {
  1.00000000e-01,  1.10000000e+00,
  3.00000000e-01,  3.30000000e+00,
  2.00000000e-01,  2.20000000e+00,
  1.00000000e-01,  1.10000000e+00,
 -4.00000000e-01, -4.40000000e+00,
 -3.00000000e-01, -3.20000000e+00,
};

const char* spatialdata::spatialdb::SimpleDBTestDataArea3D::_names[] = {
"One",
"Two",
};

const char* spatialdata::spatialdb::SimpleDBTestDataArea3D::_units[] = {
"m",
"m",
};

const double spatialdata::spatialdb::SimpleDBTestDataArea3D::_queryNearest[] = {
  6.30149946e+00,  1.03728716e+01,  9.60520501e+00,  2.00000000e-01,  2.20000000e+00,
  3.78727022e+00,  1.01546537e+01,  8.48447656e+00,  1.00000000e-01,  1.10000000e+00,
  6.95615313e+00,  1.29914862e+01,  8.29589766e+00,  1.00000000e-01,  1.10000000e+00,
  4.89452639e+00,  1.19003968e+01,  7.94701520e+00, -3.00000000e-01, -3.20000000e+00,
};

const double spatialdata::spatialdb::SimpleDBTestDataArea3D::_queryLinear[] = {
  6.30149946e+00,  1.03728716e+01,  9.60520501e+00,  2.00000000e-01,  2.20000000e+00,
  3.78727022e+00,  1.01546537e+01,  8.48447656e+00, -3.75000000e-02, -4.12500000e-01,
  6.95615313e+00,  1.29914862e+01,  8.29589766e+00,  0.00000000e+00,  0.00000000e+00,
  4.89452639e+00,  1.19003968e+01,  7.94701520e+00, -2.25000000e-01, -2.42500000e+00,
};

const int spatialdata::spatialdb::SimpleDBTestDataArea3D::_errFlags[] = {
 0, 0, 1, 0,};

spatialdata::spatialdb::SimpleDBTestDataArea3D::SimpleDBTestDataArea3D(void)
{ // constructor
  numLocs = _numLocs;
  spaceDim = _spaceDim;
  numVals = _numVals;
  dataDim = _dataDim;
  numQueries = _numQueries;
  dbCoords = const_cast<double*>(_dbCoords);
  dbData = const_cast<double*>(_dbData);
  names = const_cast<char**>(_names);
  units = const_cast<char**>(_units);
  queryNearest = const_cast<double*>(_queryNearest);
  queryLinear = const_cast<double*>(_queryLinear);
  errFlags = const_cast<int*>(_errFlags);
} // constructor

spatialdata::spatialdb::SimpleDBTestDataArea3D::~SimpleDBTestDataArea3D(void)
{}


// End of file
