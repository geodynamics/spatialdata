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

#if !defined(_spatial_simpledbquery_h)
#define _spatial_simpledbquery_h

namespace spatial {
  class SimpleDBQuery;
  class TestSimpleDBQuery; // regression testing
}; // namespace spatial

#include <vector> // USES std::vector

// ----------------------------------------------------------------------
class spatial::SimpleDBQuery
{ // class SimpleDBQuery
  friend class TestSimpleDBQuery;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  SimpleDBQuery(const SimpleDB& db);
  
  /// Default destructor.
  ~SimpleDBQuery(void);
  
  /** Set query type.
   *
   * @param Set type of query
   */
  void QueryType(const SimpleDB::QueryEnum queryType);

  /** Set values to be returned by queries.
   *
   * @param names Names of values to be returned in queries
   * @param numVals Number of values to be returned in queries
   */
  void QueryVals(const char** names,
		 const int numVals);

  /** Query the database.
   *
   * @param pValues Pointer to computed values (output from query)
   * @param x X coordinate of location for query
   * @param y Y coordinate of location for query
   * @param z Z coordinate of location for query
   */
  void Query(double** pVals,
	     const double x,
	     const double y,
	     const double z);

 private :
  // PRIVATE STRUCT /////////////////////////////////////////////////////

  /** Interpolation weighting information */
  struct WtStruct {
    double Wt; ///< Weight for location
    int NearIndex; ///< Index into nearest
  }; // struct WtStruct

 private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Query database using nearest neighbor algorithm.
   *
   * Values at location are equal to values at nearest location in
   * database.
   *
   * @param pValues Pointer to computed values (output from query)
   * @param names Names of values to query
   * @param numVals Number of values to query
   */
  void QueryNearest(double** pVals);

  /** Query database using linear interpolation algorithm.
   *
   * Values at location are interpolation from locations in database.
   *
   * @param pValues Pointer to computed values (output from query)
   * @param names Names of values to query
   * @param numVals Number of values to query
   */
  void QueryLinear(double** pVals);

  /// Find locations in database nearest query location.
  void FindNearest(void);

  /** Get interpolation weighting functions for query.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void GetWeights(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for point interpolation.
   *
   * This routine is not actually used by a point query since it is
   * trivial. Instead it is used with the other topologies to build up
   * interpolation to the higher dimensions.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void FindPointPt(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for linear interpolation.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void FindLinePt(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for areal interpolation.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void FindAreaPt(std::vector<WtStruct>* pWeights);

  /** Get interpolation weighting functions for volumetric interpolation.
   *
   * @param pWeights Pointer to array of interpolation weights
   */
  void FindVolumePt(std::vector<WtStruct>* pWeights);

  /** Compute square of distance between points A and B.
   *
   * @param a Coordinates of point A
   * @param b Coordinates of point B
   */
  static double DistSquared(const double a[3],
			    const double b[3]);

  /** Compute area and "direction" of triangle abc. Direction is vector
   * normal to triangular surface.
   *
   * @param a Coordinates of point A
   * @param b Coordinates of point B
   * @param c Coordinates of point C
   */
  static void Area(double* area,
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
  static double Volume(const double a[3],
		       const double b[3],
		       const double c[3],
		       const double d[3]);

private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////

  /** Location of query */
  double mQ[3];

  /** Query type */
  SimpleDB::QueryEnum mQueryType;

  /** Index of nearest points in database to location */
  std::vector<int> mNearest;

  /** Reference to simple database */
  const SimpleDB& mDB;
  
  /** Values requested to be returned in queries */
  int* mQueryVals;

  /** Number of values requested to be returned in queries */
  int mQuerySize;

}; // class _SpatialDataQuery

#endif // _eqsim_spatialdataquery_h

// version
// $Id: SimpleDBQuery.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
