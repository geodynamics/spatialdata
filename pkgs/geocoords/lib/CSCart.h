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

/** @file pkgs/geocoords/lib/CSCart.h
 *
 * @brief C++ CSCart object
 *
 * C++ object for managing parameters defining Cartesian coordinate systems.
 */

#if !defined(spatialdata_geocoords_cscart_h)
#define spatialdata_geocoords_cscart_h

namespace spatialdata {
  namespace geocoords {
    class CSCart;
    class TestCSCart; // forward declaration
  } // geocoords
} // spatialdata

/// C++ object for managing parameters defining Cartesian coordinate systems
class spatialdata::geocoords::CSCart : public CoordSys
{ // class CSCart
  friend class TestCSCart;

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /// Default constructor
  CSCart(void);

  /// Default destructor
  virtual ~CSCart(void);

  /// Initialize the coordinate system.
  virtual void initialize(void);

  /** Set scale factor for converting coordinates to SI units (meters).
   *
   * @param scale Scale factor
   */
  void toMeters(const double scale);

  /** Get scale factor to convert coordinates to SI units (meters).
   *
   * @returns Scale factor
   */
  double toMeters(void) const;

  /** Pickle coordinate system to ascii stream.
   *
   * @param s Output stream
   */
  virtual void pickle(std::ostream& s) const;

  /** Unpickle coordinate system from ascii stream.
   *
   * @param s Input stream
   */
  virtual void unpickle(std::istream& s);

private :
  // PRIVATE METHODS ////////////////////////////////////////////////////

  double _toMeters; ///< Scale factor to convert coordinates to meters

}; // class CSCart

#include "CSCart.icc"

#endif // spatialdata_geocoodrs_cscart_h

// version
// $Id$

// End of file 
