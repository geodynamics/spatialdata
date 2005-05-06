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

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
/// Default constructor
spatial::SimpleDB::SimpleDB(void) :
  mpIOHandler(0),
  mpQuery(0),
  mpData(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatial::SimpleDB::SimpleDB(const char* label) :
  SpatialDB(label),
  mpIOHandler(0),
  mpQuery(0),
  mpData(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatial::SimpleDB::~SimpleDB(void)
{ // destructor
  delete mpQuery; mpQuery = 0;
  if (0 != mpData) {
    delete[] mpData->Data; mpData->Data = 0;
    delete[] mpData->ValNames; mpData->ValNames = 0;
  } // if
  delete mpData; mpData = 0;
} // destructor

// ----------------------------------------------------------------------
/// Open the database and prepare for querying.
void
spatial::SimpleDB::Open(void)
{ // Open
  FIREWALL(0 != mpIOHandler);

  // Read data
  if (0 == mpData) {
    mpData = new DataStruct;
    mpData->Data = 0;
    mpData->ValNames = 0;
  } // if
  mpIOHandler->Read(mpData);

  // Create query object
  if (0 == mpQuery)
    mpQuery = new SimpleDBQuery(*this);
} // Open

// ----------------------------------------------------------------------
/// Close the database.
void
spatial::SimpleDB::Close(void)
{ // Close
  delete mpQuery; mpQuery = 0;
  delete[] mpData; mpData = 0;
} // Close

// ----------------------------------------------------------------------
// Set query type.
void
spatial::SimpleDB::QueryType(const SimpleDB::QueryEnum queryType)
{ // QueryType
  if (0 == mpQuery) {
    std::ostringstream msg;
    msg
      << "Spatial database " << Label() << " has not been opened.\n"
      << "Please call Open() before calling QueryType().";
    throw std::runtime_error(msg.str());
  } // if
  mpQuery->QueryType(queryType);
} // QueryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatial::SimpleDB::QueryVals(const char** names,
			     const int numVals)
{ // QueryVals
  if (0 == mpQuery) {
    std::ostringstream msg;
    msg
      << "Spatial database " << Label() << " has not been opened.\n"
      << "Please call Open() before calling QueryVals().";
    throw std::runtime_error(msg.str());
  } // if
  mpQuery->QueryVals(names, numVals);
} // QueryVals

// ----------------------------------------------------------------------
// Set the I/O handler.
void
spatial::SimpleDB::IOHandler(const SimpleIO* iohandler)
{ // IOHandler
  mpIOHandler = iohandler->Clone();
} // IOHandler

// ----------------------------------------------------------------------
// Query the database.
void
spatial::SimpleDB::Query(double** pVals,
			 const int numVals,
			 const double x,
			 const double y,
			 const double z)
{ // Query
  if (0 == mpQuery) {
    std::ostringstream msg;
    msg
      << "Spatial database " << Label() << " has not been opened.\n"
      << "Please call Open() before calling Query().";
    throw std::runtime_error(msg.str());
  } // if
  else if (0 == mpData) {
    std::ostringstream msg;
    msg
      << "Spatial database " << Label() << " does not contain any data.\n"
      << "Database query aborted.";
    throw std::runtime_error(msg.str());
  } // if
  mpQuery->Query(pVals, numVals, x, y, z);
} // Query

// version
// $Id: SimpleDB.cc,v 1.4 2005/05/05 20:31:29 baagaard Exp $

// End of file 
