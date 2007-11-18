// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

/** @file libsrc/spatialdb/GocadVoxet.hh
 *
 * @brief C++ implementation of object for managing Gocad Voxets.
 *
 */

#if !defined(spatialdata_spatialdb_gocadvoxet_hh)
#define spatialdata_spatialdb_gocadvoxet_hh

#include <string> // USES std::string

namespace spatialdata {
  namespace spatialdb {
    class GocadVoxet;
  } // spatialdb
} // spatialdata

class spatialdata::spatialdb::GocadVoxet
{ // GocadVoxet
  friend class TestGocadVOxet; // unit testing

// PUBLIC MEMBERS ///////////////////////////////////////////////////////
public :

  /// Constructor
  GocadVoxet(void);

  /// Destructor
  ~GocadVoxet(void);

  /** Read voxet file and property data.
   *
   * @param dir Directory containing voxet data files.
   * @param filename Name of voxet file.
   * @param property Name of property in voxet file to read.
   */
  void read(const char* dir,
	    const char* filename,
	    const char* property);

  /** Query voxet for value.
   *
   * @param value Value for result.
   * @param pt Location of query.
   * @returns 0 if pt is inside voxet, 1 if outside voxet.
   */
  int query(double* value,
	    const double pt[3]) const;

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :

  GocadVoxet(const GocadVoxet&); ///< Not implemented
  const GocadVoxet& operator=(const GocadVoxet&); ///< Not implemented

// PRIVATE STRUCTS //////////////////////////////////////////////////////
private :

  struct Geometry {
    float o[3];
    float u[3];
    float v[3];
    float w[3];
    float min[3];
    float max[3];
    int n[3];
    std::string name[3];
    std::string type[3];
    float scale[3];
  }; // axis

  struct Property {
    std::string name;
    float noDataValue;
    int esize;
    int isSigned;
    std::string etype;
    int offset;
    std::string filename;
  }; // property

// PRIVATE METHODS //////////////////////////////////////////////////////
private :

  /** Read voxet file.
   *
   * @param filename Name of Gocad voxet file.
   * @param propertyName Name of property to read.
   */
  void _readVoxetFile(const char* filename,
		      const char* propertyName);

  /** Read property file.
   *
   * @param filename Name of voxet data file.
   */
  void _readPropertyFile(const char* filename);

  /** Convert array of float values from big endian to native float type.
   *
   * @param vals Array of values.
   * @param nvals Number of values.
   */
  void
  _endianBigToNative(float* vals,
		     const int nvals) const;

  /// Reset class data.
  void _resetData(void);

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  Geometry _geometry; ///< Geometry of voxet data.
  Property _property; ///< Voxet properties.
  float* _data; ///< Array with data values

}; // GocadVoxet

#endif // spatialdata_spatialdb_gocadvoxet_hh


// End of file 
