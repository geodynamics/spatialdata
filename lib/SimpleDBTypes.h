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

#if !defined(_spatial_simpledbtypes_h)
#define _spatial_simpledbtypes_h

struct spatial::SimpleDB::DataStruct {
  double* Data;
  std::string* ValNames;
  int NumLocs;
  int NumVals;
  TopoEnum Topology;
}; // DataStruct

namespace spatial {
  class SpatialDBTypes;
}; // namespace spatial

class spatial::SimpleDBTypes
{ // SimpleDBTypes

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Get coordinates of location in database.
   *
   * @param data Datain database
   * @param index Index of location in database
   */
  static double* DataCoords(const SimpleDB::DataStruct& data,
			    const int index);

  /** Get values of location in database.
   *
   * @param data Datain database
   * @param index Index of location in database
   */
  static double* DataVals(const SimpleDB::DataStruct& data,
			  const int index);

}; // class SpatialDBTypes

#include "SimpleDBTypes.icc" // inline methods

#endif // _spatial_simpledbtypes_h

// version
// $Id: SimpleDBTypes.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
