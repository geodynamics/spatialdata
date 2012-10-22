// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SimpleGridDB.hh
 *
 * @brief C++ object for performing querying of data on a nonuniform
 * (or uniform) grid in a geographic projected coordinate system.
 */

#if !defined(spatialdata_spatialdb_simplegriddb_hh)
#define spatialdata_spatialdb_simplegriddb_hh

#include "SpatialDB.hh" // ISA SpatialDB

#include <string> // HASA std::string
#include <iosfwd> // USES std::istream

class spatialdata::spatialdb::SimpleGridDB : SpatialDB
{ // SimpleGridDB
  friend class TestSimpleGridDB; // unit testing
 
 public :
  // PUBLIC ENUM ////////////////////////////////////////////////////////

  /** Type of query */
  enum QueryEnum {
    NEAREST=0, ///< Nearest interpolation.
    LINEAR=1, ///< Linear interpolation.
  };

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :
 
  /// Constructor
  SimpleGridDB(void);
 
  /// Destructor
  ~SimpleGridDB(void);
 
  /** Set filename containing data.
   *
   * @param dir Directory containing data files.
   */
  void filename(const char* value);
 
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
  void queryType(const QueryEnum queryType);

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
 
 
// PRIVATE METHODS //////////////////////////////////////////////////////
private :

  /** Read data file header.
   *
   * @param filein Input stream.
   */
  void _readHeader(std::istream& filein);

  /** Read data values.
   *
   * @param filein Input stream.
   */
  void _readData(std::istream& filein);

  /// Check compatibility of spatial database parameters.
  void _checkCompatibility(void) const;

  /** Bilinear search for coordinate.
   *
   * Returns index of target as a double.
   *
   * @param target Coordinates of target.
   * @param vals Array of ordered values to search.
   * @param nvals Number of values.
   */
  double _search(const double target,
		 const double* vals,
		 const int nvals);

  /** Interpolate in 1-D to get values at target location defined by
   * indices.
   *
   * @param vals Array for computed values (output from query), must be
   *   allocated BEFORE calling query().
   * @param numVals Number of values expected (size of pVals array)
   * @param indexX Index along x dimension.
   * @param numX Number of coordinates along x dimension.
   */
  void _interpolate1D(double* vals,
		      const int numVals,
		      const double indexX,
		      const int numX) const;

  /** Interpolate in 2-D to get values at target location defined by
   * indices.
   *
   * @param vals Array for computed values (output from query), must be
   *   allocated BEFORE calling query().
   * @param numVals Number of values expected (size of pVals array)
   * @param indexX Index along x dimension.
   * @param numX Number of coordinates along x dimension.
   * @param indexY Index along y dimension.
   * @param numY Number of coordinates along y dimension.
   */
  void _interpolate2D(double* vals,
		      const int numVals,
		      const double indexX,
		      const int numX,
		      const double indexY,
		      const int numY) const;

  /** Interpolate in 3-D to get values at target location defined by
   * indices.
   *
   * @param vals Array for computed values (output from query), must be
   *   allocated BEFORE calling query().
   * @param numVals Number of values expected (size of pVals array)
   * @param indexX Index along x dimension.
   * @param indexY Index along y dimension.
   * @param indexZ Index along z dimension.
   */
  void _interpolate3D(double* vals,
		      const int numVals,
		      const double indexX,
		      const double indexY,
		      const double indexZ) const;

  /** Get index into data array.
   *
   * @param indexX Index along x dimension.
   * @param indexY Index along y dimension.
   * @param indexZ Index along z dimension.
   *
   * @returns Index into data array.
   */
  int _dataIndex(const int indexX,
		 const int indexY,
		 const int indexZ) const;

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :
  
  double* _data; ///< Array of data values.
  double* _x; ///< Array of x coordinates.
  double* _y; ///< Array of y coordinates.
  double* _z; ///< Array of z coordinates.

  double _xyz[3];

  int* _queryVals; ///< Indices of values to be returned in queries.
  int _querySize; ///< Number of values requested to be returned in queries.

  int _numX; ///< Number of points along x dimension.
  int _numY; ///< Number of points along y dimension.
  int _numZ; ///< Number of points along z dimension.
  int _dataDim; ///< Dimension of data topology.
  int _spaceDim; ///< Spatial dimension of data.

  int _numValues; ///< Number of values in database.
  std::string* _names; ///< Names of data values.
  std::string* _units; ///< Units of values.  

  std::string _filename; ///< Filename of data file
  geocoords::CoordSys* _cs; ///< Coordinate system

  QueryEnum _queryType; ///< Query type

  static const char* FILEHEADER;

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :
 
  SimpleGridDB(const SimpleGridDB&); ///< Not implemented
  const SimpleGridDB& operator=(const SimpleGridDB&); ///< Not implemented
 
}; // SimpleGridDB

#include "SimpleGridDB.icc" // inline methods

#endif // spatialdata_spatialdb_simplegriddb_hh


// End of file 
