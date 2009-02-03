// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

/** @file libsrc/spatialdb/SimpleDBData.hh
 *
 * @brief C++ data in simple spatial database.
 */

#if !defined(spatialdata_spatialdb_simpledbdata_hh)
#define spatialdata_spatialdb_simpledbdata_hh

#include "spatialdbfwd.hh" // forward declarations

#include <string> // USES std::string

class spatialdata::spatialdb::SimpleDBData
{ // SimpleDBData
  friend class TestSimpleDBData; // unit testing

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  SimpleDBData(void);

  /// Default destructor
  ~SimpleDBData(void);

  /** Allocate data structues.
   *
   * @param numLocs Number of locations.
   * @param numValues Number of values.
   * @param spaceDim Spatial dimension of domain.
   * @param dataDim Spatial dimension of data distribution.
   */
  void allocate(const int numLocs,
		const int numValues,
		const int spaceDim,
		const int dataDim);

  /** Set data values.
   *
   * @pre Must call allocate() before setData().
   *
   * @param values Array of data values [numLocs*numValues].
   * @param numLocs Number of locations.
   * @param numValues Number of values.
   */
  void data(const double* values,
	    const int numLocs,
	    const int numValues);

  /** Set coordinates of locations.
   *
   * @pre Must call allocate() before setLocations().
   *
   * @param values Array of coordinates of locations [numLocs*spaceDim].
   * @param numLocs Number of locations.
   * @param spaceDim Spatial dimension of coordinates.
   */
  void coordinates(const double* values,
		   const int numLocs,
		   const int spaceDim);

  /** Set names of values.
   *
   * @pre Must call allocate() before setNames().
   *
   * @param names Array of names of values [numValues].
   * @param numValues Number of values.
   */
  void names(const char** const values,
	     const int numValues);

  /** Set units of values.
   *
   * @pre Must call allocate() before setUnits().
   *
   * @param units Array of units of values [numValues].
   * @param numValues Number of values.
   */
  void units(const char** const values,
	     const int numValues);

  /** Get number of locations for data.
   *
   * @returns Number of locations.
   */
  int numLocs(void) const;

  /** Get number of values for data.
   *
   * @returns Number of values.
   */
  int numValues(void) const;

  /** Get spatial dimension of data distribution.
   *
   * @returns Spatial dimension.
   */
  int dataDim(void) const;

  /** Get spatial dimension of locations.
   *
   * @returns Spatial dimension.
   */
  int spaceDim(void) const;

  /** Get coordinates of location in database.
   *
   * @param index Index of location in database
   * @returns Coordinates of location.
   */
  const double* coordinates(const int index) const;

  /** Get coordinates of location in database.
   *
   * @param index Index of location in database
   * @returns Coordinates of location.
   */
  double* coordinates(const int index);

  /** Get data values at location in database.
   *
   * @param index Index of location in database.
   * @returns Data values at location.
   */
  const double* data(const int index) const;

  /** Get data values at location in database.
   *
   * @param index Index of location in database.
   * @returns Data values at location.
   */
  double* data(const int index);

  /** Get name of value.
   *
   * @param index Index of value.
   * @returns Name of value.
   */
  const char* name(const int index) const;

  /** Get units of value.
   *
   * @param index Index of value.
   * @returns Units of value.
   */
  const char* units(const int index) const;

private :
// PRIVATE METHODS ////////////////////////////////////////////////////

  double* _data; ///< Array of data values.
  double* _coordinates; ///< Array of coordinates of locations.
  std::string* _names; ///< Names of data values.
  std::string* _units; ///< Units of values.
  int _numLocs; ///< Number of locations.
  int _numValues; ///< Number of values.
  int _dataDim; ///< Spatial dimension of data distribution.
  int _spaceDim; ///< Spatial dimension of coordinate locations.

}; // class SpatialDBData

#include "SimpleDBData.icc" // inline methods

#endif // spatialdata_spatialdb_simpledbdata_hh


// End of file 
