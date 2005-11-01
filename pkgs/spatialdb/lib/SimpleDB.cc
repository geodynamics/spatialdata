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

#include "SpatialDB.h" // ISA SpatialDB object
#include "SimpleDB.h" // Implementation of class methods

#include "SimpleIO.h" // USES SimpleIO
#include "SimpleDBQuery.h" // USES SimpleDBQuery
#include "SimpleDBTypes.h" // USES SimpleDBTypes

#include "spatialdata/geocoords/CoordSys.h" // USES CoordSys

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

#if defined(HAVE_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#include <assert.h>
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::SimpleDB::SimpleDB(void) :
  _pIOHandler(0),
  _pQuery(0),
  _pData(0),
  _pCS(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::SimpleDB::SimpleDB(const char* label) :
  SpatialDB(label),
  _pIOHandler(0),
  _pQuery(0),
  _pData(0),
  _pCS(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::SimpleDB::~SimpleDB(void)
{ // destructor
  delete _pQuery; _pQuery = 0;
  if (0 != _pData) {
    delete[] _pData->data; _pData->data = 0;
    delete[] _pData->valNames; _pData->valNames = 0;
  } // if
  delete _pData; _pData = 0;

  delete _pCS; _pCS = 0;
} // destructor

// ----------------------------------------------------------------------
/// Open the database and prepare for querying.
void
spatialdata::spatialdb::SimpleDB::open(void)
{ // open
  FIREWALL(0 != _pIOHandler);

  // Read data
  if (0 == _pData) {
    _pData = new DataStruct;
    _pData->data = 0;
    _pData->valNames = 0;
  } // if
  _pIOHandler->read(_pData, &_pCS);

  // Create query object
  if (0 == _pQuery)
    _pQuery = new SimpleDBQuery(*this);
} // open

// ----------------------------------------------------------------------
/// Close the database.
void
spatialdata::spatialdb::SimpleDB::close(void)
{ // close
  delete _pQuery; _pQuery = 0;
  delete[] _pData; _pData = 0;
} // close

// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::SimpleDB::queryType(const SimpleDB::QueryEnum queryType)
{ // queryType
  if (0 == _pQuery)
    _pQuery = new SimpleDBQuery(*this);
  _pQuery->queryType(queryType);
} // QueryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleDB::queryVals(const char** names,
					    const int numVals)
{ // queryVals
  if (0 == _pQuery) {
    std::ostringstream msg;
    msg
      << "Spatial database " << label() << " has not been opened.\n"
      << "Please call Open() before calling QueryVals().";
    throw std::runtime_error(msg.str());
  } // if
  _pQuery->queryVals(names, numVals);
} // queryVals

// ----------------------------------------------------------------------
// Set the I/O handler.
void
spatialdata::spatialdb::SimpleDB::ioHandler(const SimpleIO* iohandler)
{ // ioHandler
  _pIOHandler = iohandler->clone();
} // ioHandler

// ----------------------------------------------------------------------
// Query the database.
void
spatialdata::spatialdb::SimpleDB::query(double** pVals,
					const int numVals,
					const double x,
					const double y,
					const double z,
			      const spatialdata::geocoords::CoordSys* pCSQuery)
{ // query
  if (0 == _pQuery) {
    std::ostringstream msg;
    msg
      << "Spatial database " << label() << " has not been opened.\n"
      << "Please call Open() before calling Query().";
    throw std::runtime_error(msg.str());
  } // if
  else if (0 == _pData) {
    std::ostringstream msg;
    msg
      << "Spatial database " << label() << " does not contain any data.\n"
      << "Database query aborted.";
    throw std::runtime_error(msg.str());
  } // if
  _pQuery->query(pVals, numVals, x, y, z, pCSQuery);
} // query

// version
// $Id: SimpleDB.cc,v 1.1 2005/05/25 18:42:56 baagaard Exp $

// End of file 
