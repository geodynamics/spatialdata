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

/** @file lib/SimpleIO.h
 *
 * @brief C++ abstract base class for I/O of data for simple spatial database.
 */

#if !defined(spatialdata_spatialdb_simpleio_h)
#define spatialdata_spatialdb_simpleio_h

namespace spatialdata {
  namespace spatialdb {
    class SimpleIO;
    class SimpleDB; // USES SimpleDB
  } // spatialdb
} // spatialdata

/// C++ manager for simple spatial database.
class spatialdata::spatialdb::SimpleIO
{ // class SimpleIO

public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  SimpleIO(void);
  
  /// Default destructor.
  virtual ~SimpleIO(void);

  // Using default copy constructor

  /** Clone object.
   *
   * @returns Pointer copy of this.
   */
  virtual SimpleIO* clone(void) const = 0;
  
  /** Set filename for database.
   *
   * @param filename Filename of database
   */
  void filename(const char* filename);

  /** Get filename for database.
   *
   * @returns Filename of database
   */
  const char* filename(void) const;

  /** Read the database.
   *
   * @param pData Database data
   * @param ppCS Pointer to coordinate system
   */
  virtual void read(SimpleDB::DataStruct* pData,
		    spatialdata::geocoords::CoordSys** ppCS) = 0;

  /** Write the database.
   *
   * @param data Database data
   * @param cs Coordinate system
   */
  virtual void write(const SimpleDB::DataStruct& data,
		     const spatialdata::geocoords::CoordSys& cs) = 0;

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Check compatibility of topology and spatial distribution.
   *
   * Currently, this compatiblity check only involves making sure
   * there are enough number of points to perform the interpolation
   * corresponding to the topology of the spatial distribution. It
   * does not check the actual topology of the distribution.
   *
   * @param data Database data
   */
  static void checkCompatibility(const SimpleDB::DataStruct& data);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  const SimpleIO& operator=(const SimpleIO& data); ///< Not implemented
  
private :
 // PRIVATE MEMBERS ////////////////////////////////////////////////////
  
  /** Filename of database */
  const char* _filename;

}; // class SimpleIO

#include "SimpleIO.icc"

#endif // spatialdata_spatialdb_simpleio_h

// version
// $Id: SimpleIO.h,v 1.1 2005/05/25 18:42:56 baagaard Exp $

// End of file 
