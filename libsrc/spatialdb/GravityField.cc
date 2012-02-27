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

#include <portinfo>

#include "GravityField.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES sqrt()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::GravityField::GravityField(void) :
  SpatialDB("Gravity field"),
  _acceleration(9.80665), // m/s^2
  _csECEF(new geocoords::CSGeo),
  _queryVals(new int[3]),
  _querySize(3)
{ // constructor
  _gravityDir[0] = 0.0;
  _gravityDir[1] = 0.0;
  _gravityDir[2] = -1.0;

  if (0 == _csECEF)
    throw std::runtime_error("Error while initializing ECEF coordinate "
			     "system.");
  _csECEF->isGeocentric(true);
  _csECEF->initialize();

  assert(0 != _queryVals);
  _queryVals[0] = 0;
  _queryVals[1] = 1;
  _queryVals[2] = 2;
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::GravityField::~GravityField(void)
{ // destructor
  delete _csECEF; _csECEF = 0;
  delete[] _queryVals; _queryVals = 0;
  _querySize = 0;
} // destructor

// ----------------------------------------------------------------------
// Set direction of gravitational body force.
void
spatialdata::spatialdb::GravityField::gravityDir(const double x,
						 const double y,
						 const double z)
{ // gravityDir
  const double mag = sqrt(x*x + y*y + z*z);
  _gravityDir[0] = x / mag;
  _gravityDir[1] = y / mag;
  _gravityDir[2] = z / mag;
} // gravityDir

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::GravityField::queryVals(const char* const* names,
						const int numVals)
{ // queryVals
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(0 != names && 0 < numVals);
  
  _querySize = numVals;
  delete[] _queryVals; _queryVals = new int[numVals];
  for (int iVal=0; iVal < numVals; ++iVal) {
    if (0 == strcasecmp(names[iVal], "x"))
      _queryVals[iVal] = 0;
    else if (0 == strcasecmp(names[iVal], "y"))
      _queryVals[iVal] = 1;
    else if (0 == strcasecmp(names[iVal], "z"))
      _queryVals[iVal] = 2;
    else {
      std::ostringstream msg;
      msg
	<< "Could not find value " << names[iVal] << " in spatial database\n"
	<< label() << ". Available values are: 'x', 'y', 'z'.";
      throw std::runtime_error(msg.str());
    } // if
  } // for
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::GravityField::query(
			      double* vals,
			      const int numVals,
			      const double* coords,
			      const int numDims,
			      const spatialdata::geocoords::CoordSys* cs)
{ // query
  assert(0 != cs);

  if (0 == _querySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << label() << "\n"
      << "have not been set. Please call queryVals() before query().\n";
    throw std::runtime_error(msg.str());
  } // if
  else if (numVals != _querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << label() << "\n"
      << "(" << _querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } // if

  if (geocoords::CoordSys::CARTESIAN == cs->csType())
    for (int i=0; i < _querySize; ++i)
      vals[i] = _acceleration*_gravityDir[_queryVals[i]];
  else {
    const geocoords::CSGeo* csGeo = dynamic_cast<const geocoords::CSGeo*>(cs);
    double radialDir[3];
    const int numLocs = 1;
    csGeo->radialDir(radialDir, coords, numLocs, numDims);
    for (int i=0; i < _querySize; ++i)
      vals[i] = -_acceleration*radialDir[_queryVals[i]];
  } // if/else

  return 0;
} // query


// End of file 
