// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "SpatialDB.hh" // ISA SpatialDB object
#include "SimpleDB.hh" // Implementation of class methods

#include "SimpleIO.hh" // USES SimpleIO
#include "SimpleDBData.hh" // USES SimpleDBData
#include "SimpleDBQuery.hh" // USES SimpleDBQuery

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys

#include <stdexcept> // USES std::runtime_error
#include "Exception.hh" // USES OutOfBounds

#include <sstream> // USES std::ostringsgream
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::SimpleDB::SimpleDB(void) :
  _data(0),
  _iohandler(0),
  _query(0),
  _cs(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::SimpleDB::SimpleDB(const char* label) :
  SpatialDB(label),
  _data(0),
  _iohandler(0),
  _query(0),
  _cs(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SimpleDB::~SimpleDB(void)
{ // destructor
  delete _data; _data = 0;
  delete _iohandler; _iohandler = 0;
  delete _query; _query = 0;
  delete _cs; _cs = 0;
} // destructor

// ----------------------------------------------------------------------
/// Open the database and prepare for querying.
void
spatialdata::spatialdb::SimpleDB::open(void)
{ // open
  assert(_iohandler);

  // Read data
  if (!_data) {
    _data = new SimpleDBData;
    _iohandler->read(_data, &_cs);
  } // if

  // Create query object
  if (!_query)
    _query = new SimpleDBQuery(*this);
} // open

// ----------------------------------------------------------------------
/// Close the database.
void
spatialdata::spatialdb::SimpleDB::close(void)
{ // close
  delete _data; _data = 0;

  if (_query) {
    _query->deallocate();
  } // if
} // close

// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::SimpleDB::queryType(const SimpleDB::QueryEnum queryType)
{ // queryType
  if (0 == _query)
    _query = new SimpleDBQuery(*this);
  _query->queryType(queryType);
} // QueryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleDB::queryVals(const char* const* names,
					    const int numVals)
{ // queryVals
  if (0 == _query) {
    std::ostringstream msg;
    msg
      << "Spatial database " << label() << " has not been opened.\n"
      << "Please call Open() before calling QueryVals().";
    throw std::runtime_error(msg.str());
  } // if
  _query->queryVals(names, numVals);
} // queryVals

// ----------------------------------------------------------------------
// Set the I/O handler.
void
spatialdata::spatialdb::SimpleDB::ioHandler(const SimpleIO* iohandler)
{ // ioHandler
  delete _iohandler; _iohandler = (0 != iohandler) ? iohandler->clone() : 0;
} // ioHandler

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SimpleDB::query(double* vals,
					const int numVals,
					const double* coords,
					const int numDims,
			      const spatialdata::geocoords::CoordSys* pCSQuery)
{ // query
  try {
    if (0 == _query) {
      std::ostringstream msg;
      msg
	<< "Spatial database " << label() << " has not been opened.\n"
	<< "Please call open() before calling query().";
      throw std::runtime_error(msg.str());
    } // if
    else if (0 == _data) {
      std::ostringstream msg;
      msg
	<< "Spatial database " << label() << " does not contain any data.\n"
	<< "Database query aborted.";
      throw std::runtime_error(msg.str());
    } // if
    _query->query(vals, numVals, coords, numDims, pCSQuery);
  } catch(const OutOfBounds& err) {
    std::fill(vals, vals+numVals, 0);
    return 1;
  } catch(const std::exception& err) {
    throw std::runtime_error(err.what());
  } catch(...) {
    throw std::runtime_error("Unknown error in SpatialDB query");
  } // catch
  return 0;
} // query


// End of file 
