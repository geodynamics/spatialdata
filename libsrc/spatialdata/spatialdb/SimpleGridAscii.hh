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

/** @file libsrc/spatialdb/SimpleGridAscii.hh
 *
 * @brief C++ object for reading/writing SimpleGridDB info as ASCII
 * files.
 */

#if !defined(spatialdata_spatialdb_simplegridascii_hh)
#define spatialdata_spatialdb_simplegridascii_hh

#include "SimpleGridDB.hh" // ISA SimpleGridDB

#include <iosfwd> // USES std::istream

// ----------------------------------------------------------------------
class spatialdata::spatialdb::SimpleGridAscii
{ // SimpleGridAscii

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  // Using default constructor.
  
  // Using default destructor.

  // Using default copy constructor
  
  /** Read the database.
   *
   * @param db Spatial database.
   */
  static
  void read(SimpleGridDB* db);

  /** Write the database.
   *
   * @param db Spatial database.
   */
  static
  void write(const SimpleGridDB& db);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  /** Read data file header.
   *
   * @param filein Input stream.
   * @param db Spatial database.
   */
  static
  void _readHeader(std::istream& filein,
		   SimpleGridDB* const db);
  
  /** Read data values.
   *
   * @param filein Input stream.
   * @param db Spatial database.
   */
  static
  void _readData(std::istream& filein,
		 SimpleGridDB* const db);

  /** Write the data file header.
   *
   * @param fileout Output stream.
   * @param db Spatial database.
   */
  static
  void _writeHeader(std::ostream& fileout,
		    const SimpleGridDB& db);
  
  /** Write data values.
   *
   * @param fileout Output stream.
   * @param db Spatial database.
   */
  static
  void _writeData(std::ostream& fileout,
		  const SimpleGridDB& db);

 private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  /** Magic header in ascii files */
  static const char* FILEHEADER;

}; // class SimpleGridAscii

#endif // spatialdata_spatialdb_SimpleGridAscii_hh


// End of file 
