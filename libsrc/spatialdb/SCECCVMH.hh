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

#if !defined(spatialdata_spatialdb_sceccvmh_hh)
#define spatialdata_spatialdb_sceccvmh_hh

#include "spatialdata/spatialdb/SpatialDB.hh" // ISA SpatialDB

#include <string>> // HASA std::string

namespace spatialdata {
  namespace spatialdb {
    class SCECCVMH;

    class GocadVoxet; // HASA GocadVoxet
    class TestSCECCVMH; // unit testing
  } // spatialdb

  namespace geocoords {
    class CSGeoProj; // HASA CSGeoProj
  } // geocoords
} // spatialdata

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

  SCECCVMH(const SCECCVMH&); ///< Not implemented
  const SCECCVMH& operator=(const SCECCVMH&); ///< Not implemented

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

}; // SCECCVMH

#endif // spatialdata_spatialdb_sceccvmh_hh


// End of file 