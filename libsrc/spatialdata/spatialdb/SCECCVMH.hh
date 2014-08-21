// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SCECCVMH.hh
 *
 * @brief C++ object for performing querying of SCEC CVM-H version 5.2
 * and version 5.3.
 */

#if !defined(spatialdata_spatialdb_sceccvmh_hh)
#define spatialdata_spatialdb_sceccvmh_hh

#include "SpatialDB.hh" // ISA SpatialDB

#include <string> // HASA std::string

class spatialdata::spatialdb::SCECCVMH : SpatialDB
{ // SCECCVMH
  friend class TestSCECCVMH; // unit testing
 
// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :
 
  /// Constructor
  SCECCVMH(void);
 
  /// Destructor
  ~SCECCVMH(void);
 
  /** Set directory containing SCEC CVM-H data files.
   *
   * @param dir Directory containing data files.
   */
  void dataDir(const char* dir);
 
  /** Set minimum shear wave speed. Corresponding minima for Vp and
   * density are enforced using nominal Vp->Vs relation and
   * Vp->density relations.
   *
   * @param value Minimum shear wave speed.
   */
  void minVs(const double value);

  /** Set squashed topography/bathymetry flag and minimum elevation of
   * squashing.
   *
   * @param flag True if squashing, false otherwise.
   * @param limit Minimum elevation for squashing.
   */
  void squash(const bool flag,
	      const double limit =-2000.0);

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
  void queryVals(const char* const* names,
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
 
  SCECCVMH(const SCECCVMH&); ///< Not implemented
  const SCECCVMH& operator=(const SCECCVMH&); ///< Not implemented
 
// PRIVATE ENUMS ////////////////////////////////////////////////////////
private :
 
  enum QueryValsEnum {
    QUERY_VP=0, // vp
    QUERY_VS=1, // vs
    QUERY_DENSITY=2, // density
    QUERY_TOPOELEV=3, // Elevation of topography
    QUERY_BASEDEPTH=4, // Depth of basement
    QUERY_MOHODEPTH=5, // Depth of Moho
    QUERY_VPTAG=6 // Tag for Vp
  }; // ValsEnum

// PRIVATE METHODS //////////////////////////////////////////////////////
private :

  /** Perform query for Vp.
   *
   * @param vp Result of query
   * @returns 0 if found location, 1 otherwise.
   */
  int _queryVp(double* vp);

  /** Perform query for tag.
   *
   * @param tag Result of query
   * @returns 0 if found location, 1 otherwise.
   */
  int _queryTag(double* tag);

  /** Compute density from Vp.
   *
   * @param vp Vp in m/s.
   * @returns density in kg/m^3.
   */
  double _calcDensity(const double vp) const;

  /** Compute density from Vp.
   *
   * @param vp Vp in m/s.
   * @returns Vs in m/s.
   */
  double _calcVs(const double vp) const;

  /** Compute minimum Vp from minimum Vs.
   *
   * @returns Minimum Vp.
   */
  double _minVp(void) const;

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  double _xyzUTM[3];
  std::string _dataDir;
  GocadVoxet* _laLowResVp;
  GocadVoxet* _laLowResTag;
  GocadVoxet* _laHighResVp;
  GocadVoxet* _laHighResTag;
  GocadVoxet* _crustMantleVp;
  GocadVoxet* _crustMantleVs;
  GocadVoxet* _crustMantleTag;
  GocadVoxet* _topoElev;
  GocadVoxet* _baseDepth;
  GocadVoxet* _mohoDepth;  
  geocoords::CSGeoProj* _csUTM;

  double _squashLimit; ///< Elevation above which topography is squashed.
  double _minVs; ///< Minimum Vs to use.
  int* _queryVals; ///< Indices of values to be returned in queries.
  int _querySize; ///< Number of values requested to be returned in queries.
  bool _squashTopo; ///< Squash topography/bathymetry to sea level.

}; // SCECCVMH

#include "SCECCVMH.icc" // inline methods

#endif // spatialdata_spatialdb_sceccvmh_hh


// End of file 
