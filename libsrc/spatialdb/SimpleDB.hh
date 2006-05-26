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

/** @file libsrc/spatialdb/SimpleDB.hh
 *
 * @brief C++ manager for simple spatial database.
 */

#if !defined(spatialdata_spatialdb_simpledb_hh)
#define spatialdata_spatialdb_simpledb_hh

namespace spatialdata {
  namespace spatialdb {
  class SpatialDB; // ISA SpatialDB
  class SimpleDB;
  class SimpleIO; // USES SimpleIO
  class SimpleDBTypes; // helper
  class SimpleDBQuery; // helper
  class TestSimpleDB; // regression testing
  class TestSimpleDBQuery; // regression testing
  } // spatialdb
} // spatialdata

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::SimpleDB : public SpatialDB
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
  void open(void);

  /// Close the database.
  void close(void);

  /** Set query type.
   *
   * @pre Must call Open() before QueryType()
   *
   * @param queryType Set type of query
   */
  void queryType(const SimpleDB::QueryEnum queryType);

  /** Set values to be returned by queries.
   *
   * @pre Must call Open() before QueryVals()
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  void queryVals(const char** names,
		 const int numVals);

  /** Set the I/O handler.
   *
   * @param iohandler
   */
  void ioHandler(const SimpleIO* iohandler);

  /** Query the database.
   *
   * @pre Must call Open() before Query()
   *
   * @param pVals Pointer to computed values (output from query)
   * @param numVals Number of values expected (size of pVals array)
   * @param x X coordinate of location for query
   * @param y Y coordinate of location for query
   * @param z Z coordinate of location for query
   * @param pCSQuery Coordinate system of coordinates
   *
   * @returns 0 on success, 1 on failure (i.e., could not interpolate
   *   so values set to 0)
   */
  int query(double** pVals,
	     const int numVals,
	     const double x,
	     const double y,
	     const double z,
	     const spatialdata::geocoords::CoordSys* pCSQuery);

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  SimpleDB(const SimpleDB& data); ///< Not implemented
  const SimpleDB& operator=(const SimpleDB& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////
  
  SimpleIO* _pIOHandler; ///< I/O handler
  SimpleDBQuery* _pQuery; ///< Query handler
  DataStruct* _pData; ///< Pointer to data
  spatialdata::geocoords::CoordSys* _pCS; ///< Coordinate system

}; // class SimpleDB

#include "SimpleDB.icc"

#endif // spatialdata_spatialdb_simpledb_hh

// version
// $Id$

// End of file 