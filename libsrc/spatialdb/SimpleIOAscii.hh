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

#include "SimpleIO.hh" // ISA SimpleIO

#include <iosfwd> // USES std::istream

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
  void read(SimpleDBData* pData,
	    spatialdata::geocoords::CoordSys** ppCS);

  /** Write the database.
   *
   * @param data Database data
   * @param pCS Pointer to coordinate system
   */
  void write(const SimpleDBData& data,
	     const spatialdata::geocoords::CoordSys* pCS);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Read database version 1 file.
   *
   * @param pData Database data
   * @param ppCS Pointer to coordinate system
   * @param filein File input stream
   */
  static void _readV1(SimpleDBData* pData,
		      spatialdata::geocoords::CoordSys** ppCS,
		      std::istream& filein);

 private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  /** Magic header in ascii files */
  static const char* HEADER;

}; // class SimpleIOAscii

#include "SimpleIOAscii.icc" // inline methods

#endif // spatialdata_spatialdb_SimpleIOAscii_hh

// version
// $Id$

// End of file 
