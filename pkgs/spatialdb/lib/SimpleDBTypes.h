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

/** @file lib/SimpleDBTypes.h
 *
 * @brief C++ types used in simple spatial database.
 */

#if !defined(spatialdata_spatialdb_simpledbtypes_h)
#define spatialdata_spatialdb_simpledbtypes_h

#include <string> // USES std::string

struct spatialdata::spatialdb::SimpleDB::DataStruct {
  double* data;
  std::string* valNames;
  std::string* valUnits;
  int numLocs;
  int numVals;
  TopoEnum topology;
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

  /** Get values of location in database.
   *
   * @param data Datain database
   * @param index Index of location in database
   */
  static double* dataVals(const SimpleDB::DataStruct& data,
			  const int index);

}; // class SpatialDBTypes

#include "SimpleDBTypes.icc" // inline methods

#endif // spatialdata_spatialdb_simpledbtypes_h

// version
// $Id: SimpleDBTypes.h,v 1.1 2005/05/25 18:42:56 baagaard Exp $

// End of file 
