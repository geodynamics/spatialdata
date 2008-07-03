// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

#include "GeoGridVelModel.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES pow()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <string.h> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Constructor
yourname::spatialdb::GeoGridVelModel::GeoGridVelModel(void) :
  SpatialDB("My velocity model"),
  _filename(""),
  _csGeo(new spatialdata::geocoords::CSGeo),
  _queryVals(0),
  _querySize(0)
{ // constructor
  _csGeo->datumHoriz("WGS84");
  _csGeo->datumVert("mean sea level");
  _csGeo->ellipsoid("WGS84");
  _csGeo->initialize();
} // constructor

// ----------------------------------------------------------------------
// Destructor
yourname::spatialdb::GeoGridVelModel::~GeoGridVelModel(void)
{ // destructor
  // Deallocate all data
  delete _csGeo; _csGeo = 0;

  delete[] _queryVals; _queryVals = 0;
  _querySize = 0;

} // destructor

// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
yourname::spatialdb::GeoGridVelModel::open(void)
{ // open
  // Read the velocity model and do any necessary pre-query stuff.
} // open

// ----------------------------------------------------------------------
// Close the database.
void
yourname::spatialdb::GeoGridVelModel::close(void)
{ // close
  // Deallocate all data allocated in open() and query().
} // close

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
yourname::spatialdb::GeoGridVelModel::queryVals(const char** names,
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
    // Set the values to be returned in a query.
    if (0 == strcasecmp(names[iVal], "vp"))
      _queryVals[iVal] = QUERY_VP;
    else if (0 == strcasecmp(names[iVal], "vs"))
      _queryVals[iVal] = QUERY_VS;
    else if (0 == strcasecmp(names[iVal], "density")) {
      _queryVals[iVal] = QUERY_DENSITY;
      std::ostringstream msg;
      msg
	<< "Could not find value " << names[iVal] << " in spatial database\n"
	<< label() << ". Available values are:\n"
	<< "vp, vs, density, topo-elev, basement-depth, moho-depth, vp-tag.";
      throw std::runtime_error(msg.str());
    } // else
  } // for
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
yourname::spatialdb::GeoGridVelModel::query(double* vals,
					const int numVals,
					const double* coords,
					const int numDims,
					const spatialdata::geocoords::CoordSys* csQuery)
{ // query
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

  // Convert coordinates to local coordinate system
  memcpy(_xyzGeo, coords, numDims*sizeof(double));
  spatialdata::geocoords::Converter::convert(_xyzGeo, 1, numDims, 
					     _csGeo, csQuery);

  int queryFlag = 0;
  
  // ADD QUERY STUFF HERE

  return queryFlag;
} // query


// End of file
