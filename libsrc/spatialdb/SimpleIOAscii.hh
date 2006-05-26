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

/** @file libsrc/spatialdb/SimpleIOAscii.hh
 *
 * @brief C++ object for reading/writing SimpleDB info as ASCII files.
 */

#if !defined(spatialdata_spatialdb_simpleioascii_hh)
#define spatialdata_spatialdb_simpleioascii_hh

#include <iosfwd> // USES std::istream

namespace spatialdata {
  namespace spatialdb {
    class SimpleIOAscii;
    class SimpleIO;
  } // spatialdb
} // spatialdata

// ----------------------------------------------------------------------
class spatialdata::spatialdb::SimpleIOAscii : public SimpleIO
{ // SimpleIOAscii

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  // Using default constructor.
  
  // Using default destructor.

  // Using default copy constructor
  
  /** Clone object.
   *
   * @returns Pointer copy of this.
   */
  SimpleIO* clone(void) const;
  
  /** Read the database.
   *
   * @param pData Database data
   * @param ppCS Pointer to coordinate system
   */
  void read(SimpleDB::DataStruct* pData,
	    spatialdata::geocoords::CoordSys** ppCS);

  /** Write the database.
   *
   * @param data Database data
   * @param pCS Pointer to coordinate system
   */
  void write(const SimpleDB::DataStruct& data,
	     const spatialdata::geocoords::CoordSys* pCS);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Read database version 1 file.
   *
   * @param pData Database data
   * @param ppCS Pointer to coordinate system
   * @param filein File input stream
   */
  static void _readV1(SimpleDB::DataStruct* pData,
		      spatialdata::geocoords::CoordSys** ppCS,
		      std::istream& filein);

  /** Parse string into topology type.
   *
   * @param str String associated with topology
   *
   * @returns Topology type
   */
  static SimpleDB::TopoEnum parseTopoString(const char* str);
  
  /** Get string associated with topology type.
   *
   * @param topoType Topology type
   *
   * @returns String associated with topology
   */
  static const char* topoString(const SimpleDB::TopoEnum topoType);

 private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  /** String associated with 0-D distribution of data */
  static const char* POINTSTRING;

  /** String associated with 1-D distribution of data */
  static const char* LINESTRING;

  /** String associated with 2-D distribution of data */
  static const char* AREASTRING;

  /** String associated with 3-D distribution of data */
  static const char* VOLSTRING;

  /** Magic header in ascii files */
  static const char* HEADER;

}; // class SimpleIOAscii

#include "SimpleIOAscii.icc" // inline methods

#endif // spatialdata_spatialdb_SimpleIOAscii_hh

// version
// $Id$

// End of file 
