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

/** @file lib/SimpleDB.h
 *
 * @brief C++ manager for simple spatial database.
 */

#if !defined(_spatial_simpledb_h)
#define _spatial_simpledb_h

namespace spatial {
  class SpatialDB; // ISA SpatialDB
  class SimpleDB;
  class SimpleIO; // USES SimpleIO
  class SimpleDBTypes; // helper
  class SimpleDBQuery; // helper
  class TestSimpleDB; // regression testing
  class TestSimpleDBQuery; // regression testing
}; // namespace spatial

/// C++ manager for simple spatial database.
class spatial::SimpleDB : public SpatialDB
{ // class SimpleDB
  friend class SimpleDBQuery; // helper
  friend class SimpleDBTypes; // helper
  friend class TestSimpleDB; // regression testing
  friend class TestSimpleDBQuery; // regression testing

 public :
  // PUBLIC ENUM ////////////////////////////////////////////////////////

  /** Topology of spatial data */
  enum TopoEnum { POINT, LINE, AREA, VOLUME };

  /** Type of query */
  enum QueryEnum { NEAREST=0, LINEAR=1 };

  // PUBLIC MEMBERS /////////////////////////////////////////////////////

  /** Structure used to store data in database */
  struct DataStruct;
  
 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  SimpleDB(void);
  
  /** Constructor with label.
   *
   * @param label Label of database
   */
  SimpleDB(const char* label);
  
  /// Default destructor.
  ~SimpleDB(void);
  
  /// Open the database and prepare for querying.
  void Open(void);

  /// Close the database.
  void Close(void);

  /** Set query type.
   *
   * @pre Must call Open() before QueryType()
   *
   * @param queryType Set type of query
   */
  void QueryType(const SimpleDB::QueryEnum queryType);

  /** Set values to be returned by queries.
   *
   * @pre Must call Open() before QueryVals()
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  void QueryVals(const char** names,
		 const int numVals);

  /** Set the I/O handler.
   *
   * @param iohandler
   */
  void IOHandler(SimpleIO* iohandler);

  /** Query the database.
   *
   * @pre Must call Open() before Query()
   *
   * @param pVals Pointer to computed values (output from query)
   * @param x X coordinate of location for query
   * @param y Y coordinate of location for query
   * @param z Z coordinate of location for query
   */
  void Query(double** pVals,
	     const double x,
	     const double y,
	     const double z);

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  SimpleDB(const SimpleDB& data); ///< Not implemented
  const SimpleDB& operator=(const SimpleDB& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////
  
  /** I/O handler */
  SimpleIO* mpIOHandler;

  /** Query handler */
  SimpleDBQuery* mpQuery;

  /** Pointer to data */
  DataStruct* mpData;

}; // class SimpleDB

#include "SimpleDB.icc"

#endif // _spatial_simpledb_h

// version
// $Id: SimpleDB.h,v 1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
