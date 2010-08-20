// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SimpleDBQuery.hh
 *
 * @brief C++ object for performing querying of SimpleDB.
 */

#if !defined(spatialdata_spatialdb_simpledbquery_hh)
#define spatialdata_spatialdb_simpledbquery_hh

#include "spatialdbfwd.hh" // forward declarations

#include <vector> // USES std::vector

// ----------------------------------------------------------------------
class spatialdata::spatialdb::SimpleDBQuery
{ // class SimpleDBQuery
  friend class TestSimpleDBQuery;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Default constructor.
   *
   * @param db Database
   */
  SimpleDBQuery(const SimpleDB& db);
  
  /// Default destructor.
  ~SimpleDBQuery(void);
  
  /** Set query type.
   *
   * @param Set type of query
   */
  void queryType(const SimpleDB::QueryEnum queryType);

  /** Set values to be returned by queries.
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  void queryVals(const char* const* names,
		 const int numVals);

  /** Query the database.
   *
   * @param vals Array for computed values (output from query)
   * @param numVals Number of values expected (size of pVals array)
   * @param coords Coordinates of point to query
   * @param numDims Number of dimensions for coordinates
   * @param pCSQuery Coordinate system of coordinates
   */
  void query(double* vals,
	     const int numVals,
	     const double* coords,
	     const int numDims,
	     const spatialdata::geocoords::CoordSys* pCSQuery);

 private :
  // PRIVATE STRUCT /////////////////////////////////////////////////////

  /** Interpolation weighting information */
  struct WtStruct {
    double wt; ///< Weight for location
    int nearIndex; ///< Index into nearest
  }; // struct WtStruct

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Query database using nearest neighbor algorithm.
   *
   * Values at location are equal to values at nearest location in
   * database.
   *
   * @param values Array for computed values (output from query)
   * @param numVals Number of values expected (size of pVals array)
   */
  void _queryNearest(double* vals,
		     const int numVals);

  /** Query database using linear interpolation algorithm.
   *
   * Values at location are interpolation from locations in database.
   *
   * @param vals Array for computed values (output from query)
   * @param numVals Number of values expected (size of pVals array)
   */
  void _queryLinear(double* vals,
		    const int numVals);

  /// Find locations in database nearest query location.
  void _findNearest(void);

  /** Get interpolation weighting functions for query.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void _getWeights(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for point interpolation.
   *
   * This routine is not actually used by a point query since it is
   * trivial. Instead it is used with the other topologies to build up
   * interpolation to the higher dimensions.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void _findPointPt(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for linear interpolation.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void _findLinePt(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for areal interpolation.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void _findAreaPt(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for volumetric interpolation.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void _findVolumePt(std::vector<WtStruct>* pWeights);

  /** Set coordiantes of point in 3-D space using coordinates in
   * current coordinate system.
   *
   * @param pt3 Coordinates of point in 3-D space [output].
   * @param pt Cooridinates of point in current coordinate sytem.
   * @param spaceDim Spatial dimension of current coordinate system.
   */
  static
  void _setPoint3(double* const pt3,
		  const double* pt,
		  const int spaceDim);

  /** Compute square of distance between points A and B.
   *
   * @param a Coordinates of point A
   * @param b Coordinates of point B
   */
  static double _distSquared(const double a[3],
			     const double b[3]);

  /** Compute area and "direction" of triangle abc. Direction is vector
   * normal to triangular surface.
   *
   * @param a Coordinates of point A
   * @param b Coordinates of point B
   * @param c Coordinates of point C
   */
  static void _area(double* area,
		    double dir[3],
		    const double* a,
		    const double* b,
		    const double* c);

  /** Compute volume of tetrahedral defined by four points.
   *
   * @param a Coordinates of point A
   * @param b Coordinates of point B
   * @param c Coordinates of point C
   * @param d Coordinates of point D
   */
  static double _volume(const double a[3],
			const double b[3],
			const double c[3],
			const double d[3]);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  /** Location of query */
  double _q[3];

  /** Query type */
  SimpleDB::QueryEnum _queryType;

  /** Index of nearest points in database to location */
  std::vector<int> _nearest;

  /** Reference to simple database */
  const SimpleDB& _db;
  
  /** Values requested to be returned in queries */
  int* _queryVals;

  /** Number of values requested to be returned in queries */
  int _querySize;

}; // class SimpleDBQuery

#endif // spatialdata_spatialdb_spatialdbquery_hh


// End of file 
