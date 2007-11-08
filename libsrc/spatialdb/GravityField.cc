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

#include "GravityField.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES sqrt()

#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringsgream
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::GravityField::GravityField(void) :
  SpatialDB("Gravity field"),
  _acceleration(9.80665), // m/s^2
  _csECEF(new geocoords::CSGeo),
  _queryVals(0),
  _querySize(0)
{ // constructor
  _upDir[0] = 0.0;
  _upDir[1] = 0.0;
  _upDir[2] = 0.0;

  if (0 == _csECEF)
    throw std::runtime_error("Error while initializing ECEF coordinate "
			     "system.");
  _csECEF->isGeocentric(true);
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
// Set values to be returned by queries.
void
spatialdata::spatialdb::GravityField::queryVals(const char** names,
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
      vals[i] = -_acceleration*_upDir[_queryVals[i]];
  else {
    const geocoords::CSGeo* csGeo = dynamic_cast<const geocoords::CSGeo*>(cs);
    if (!csGeo->isGeocentric())
      for (int i=0; i < _querySize; ++i)
	vals[i] = -_acceleration*_upDir[_queryVals[i]];
    else {
      // cs is either CSGeo (geocentric) or CSGeoLocalCart
      const int numLocs = 1;
      const int spaceDim = 3;
      assert(spaceDim == csGeo->spaceDim());

      // Convert coordinates to Earth-centered/Earth-fixed (ECEF)
      double xyzECEF[spaceDim];
      for (int i=0; i < spaceDim; ++i)
	xyzECEF[i] = coords[i];
      geocoords::Converter::convert(xyzECEF, numLocs, spaceDim,
				    _csECEF, csGeo);

      // Compute outward radial direction by computing
      const double mag = sqrt(xyzECEF[0]*xyzECEF[0] +
			      xyzECEF[1]*xyzECEF[1] +
			      xyzECEF[2]*xyzECEF[2]);
      for (int i=0; i < _querySize; ++i)
	vals[i] = -_acceleration*xyzECEF[i] / mag;
    } // else
  } // if/else

  return 0;
} // query


// End of file 
