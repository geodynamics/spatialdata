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

#if !defined(_spatial_simpleioascii_h)
#define _spatial_simpleioascii_h

#include <iosfwd> // USES std::istream

namespace spatial {
  class SimpleIOAscii;
}; // namespace spatial

// ----------------------------------------------------------------------
class spatial::SimpleIOAscii : public SimpleIO
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
  SimpleIO* Clone(void) const;
  
  /** Read the database.
   *
   * @param pData Database data
   */
  void Read(SimpleDB::DataStruct* pData);

  /** Write the database.
   *
   * @param data Database data
   */
  void Write(const SimpleDB::DataStruct& data);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Read database version 1 file.
   *
   * @param pData Database data
   * @param filein File input stream
   */
  static void ReadV1(SimpleDB::DataStruct* pData,
		     std::istream& filein);

  /** Parse string into topology type.
   *
   * @param str String associated with topology
   *
   * @returns Topology type
   */
  static SimpleDB::TopoEnum ParseTopoString(const char* str);
  
  /** Get string associated with topology type.
   *
   * @param topoType Topology type
   *
   * @returns String associated with topology
   */
  static const char* TopoString(const SimpleDB::TopoEnum topoType);

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

#endif // _spatial_SimpleIOAscii_h

// version
// $Id: SimpleIOAscii.h,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

// End of file 
