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

#if !defined(yourname_spatialdb_geogridvelmodel_hh)
#define yourname_spatialdb_geogridvelmodel_hh

#include "spatialdata/spatialdb/SpatialDB.hh" // ISA SpatialDB

#include <string> // HASA std::string

namespace yourname {
  namespace spatialdb {
    class GeoGridVelModel;

    class TestGeoGridVelModel; // unit testing
  } // spatialdb
} // yourname

namespace spatialdata {
  namespace geocoords {
    class CSGeo; // HASA CSGeo
  } // geocoords
} // spatialdata

class yourname::spatialdb::GeoGridVelModel : spatialdata::spatialdb::SpatialDB
{ // GeoGridVelModel
  friend class TestGeoGridVelModel; // unit testing
 
// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :
 
  /// Constructor
  GeoGridVelModel(void);
 
  /// Destructor
  ~GeoGridVelModel(void);
 
  /** Set filename of velocity model.
   *
   * @param name Filename of velocity model.
   */
  void filename(const char* name);
 
  /// Open the database and prepare for querying.
  void open(void);
 
  /// Close the database.
  void close(void);
 
  /** Set values to be returned by queries.
   *
   * @pre Must call open() before queryVals()
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  void queryVals(const char** names,
		 const int numVals);
 
  /** Query the database.
   *
   * @note pVals should be preallocated to accommodate numVals values.
   *
   * @pre Must call open() before query()
   *
   * @param vals Array for computed values (output from query), must be
   *   allocated BEFORE calling query().
   * @param numVals Number of values expected (size of pVals array)
   * @param coords Coordinates of point for query
   * @param numDims Number of dimensions for coordinates
   * @param pCSQuery Coordinate system of coordinates
   *
   * @returns 0 on success, 1 on failure (i.e., could not interpolate)
   */
  int query(double* vals,
	    const int numVals,
	    const double* coords,
	    const int numDims,
	    const spatialdata::geocoords::CoordSys* pCSQuery);
 
 
// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :
 
  GeoGridVelModel(const GeoGridVelModel&); ///< Not implemented
  const GeoGridVelModel& operator=(const GeoGridVelModel&); ///< Not implemented
 
// PRIVATE ENUMS ////////////////////////////////////////////////////////
private :
 
  // Indices of values in database (used in queryVals to indicate
  // which values to return in a query).
  enum QueryValsEnum {
    QUERY_VP=0, // vp
    QUERY_VS=1, // vs
    QUERY_DENSITY=2, // density
  }; // ValsEnum

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  double _xyzGeo[3];

  // Add members for holding velocity model information.

  std::string _filename;
  spatialdata::geocoords::CSGeo* _csGeo;

  int* _queryVals; ///< Indices of values to be returned in queries.
  int _querySize; ///< Number of values requested to be returned in queries.

}; // GeoGridVelModel

#include "GeoGridVelModel.icc" // inline methods

#endif // yourname_spatialdb_geogridvelmodel_hh


// End of file 
