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

/** @file libsrc/spatialdb/SimpleDBTypes.hh
 *
 * @brief C++ types used in simple spatial database.
 */

#if !defined(spatialdata_spatialdb_simpledbtypes_hh)
#define spatialdata_spatialdb_simpledbtypes_hh

#include <string> // USES std::string

struct spatialdata::spatialdb::SimpleDB::DataStruct {
  double* data;
  std::string* valNames;
  std::string* valUnits;
  int numLocs;
  int numVals;
  int dataDim;
  int spaceDim;
}; // DataStruct

namespace spatialdata {
  namespace spatialdb {
  class SpatialDBTypes;
  } // spatialdb
} // spatialdata

class spatialdata::spatialdb::SimpleDBTypes
{ // SimpleDBTypes

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Get coordinates of location in database.
   *
   * @param data Datain database
   * @param index Index of location in database
   */
  static double* dataCoords(const SimpleDB::DataStruct& data,
			    const int index);

  /** Get coordinates of location in database.
   *
   * @param coords Array for coordinates of location
   * @param spaceDim Number of dimensions for coordinates
   * @param data Datain database
   * @param index Index of location in database
   */
  static void dataCoords(double* const coords,
			 const int spaceDim,
			 const SimpleDB::DataStruct& data,
			 const int index);

  /** Get values of location in database.
   *
   * @param data Datain database
   * @param index Index of location in database
   */
  static double* dataVals(const SimpleDB::DataStruct& data,
			  const int index);

}; // class SpatialDBTypes

#include "SimpleDBTypes.icc" // inline methods

#endif // spatialdata_spatialdb_simpledbtypes_hh


// End of file 
