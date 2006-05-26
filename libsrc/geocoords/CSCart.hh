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

/** @file libsrc/geocoords/CSCart.hh
 *
 * @brief C++ CSCart object
 *
 * C++ object for managing parameters defining Cartesian coordinate systems.
 */

#if !defined(spatialdata_geocoords_cscart_hh)
#define spatialdata_geocoords_cscart_hh

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

  /** Clone coordinate system.
   *
   * @returns Pointer to copy
   */
  virtual CoordSys* clone(void) const;

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

protected :
  // PROTECTED METHODS //////////////////////////////////////////////////

  /** Copy constructor
   *
   * @param cs Coordinate system to copy
   */
  CSCart(const CSCart& cs);

private :
  // PRIVATE MEMBERS ////////////////////////////////////////////////////

  double _toMeters; ///< Scale factor to convert coordinates to meters

}; // class CSCart

#include "CSCart.icc"

#endif // spatialdata_geocoodrs_cscart_hh

// version
// $Id$

// End of file 
