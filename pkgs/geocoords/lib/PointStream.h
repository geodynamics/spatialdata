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

/** @file pkgs/geocoords/lib/PointStream.h
 *
 * @brief C++ PointStream object
 *
 * C++ object for pickling/unpickling points from a stream.
 */

#if !defined(spatialdata_geocoords_pointstream_h)
#define spatialdata_geocoords_pointstream_h

namespace spatialdata {
  namespace geocoords {
    class PointStream;
  }; // namespace geocoords
}; // namespace spatialdata

#include <iosfwd> // USES std::istream, std::ostream

/// C++ object for pickling/unpickler points from a stream.
class spatialdata::geocoords::PointStream
{ // class PointStream

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor.
  PointStream(void);

  /// Default destructor
  ~PointStream(void);

  /** Load data from input stream into array of points.
   *
   * @param ppPoints Pointer to pointer to array of points
   * @param pNumLocs Pointer to number of points
   * @param pNumCoords Pointer to number of coordinates per point
   * @param sin Input stream
   */
  void load(double** ppMesh,
	    int* pNumLocs,
	    int* pNumCoords,
	    std::istream& sin) const;

  /** Dump data from array of points to output stream.
   *
   * @param pPoints Pointer to array of points
   * @param numLocs Number of locations
   * @param numCoords Number of coordinates per point
   * @param sout Output stream
   */
  void dump(const double* const pPoints,
	    const int numLocs,
	    const int numCoords,
	    std::ostream& sout) const;

}; // class PointStream

#endif // spatialdata_geocoords_pointstream_h

// version
// $Id: PointStream.h,v 1.1 2005/06/08 03:20:40 baagaard Exp $

// End of file 
