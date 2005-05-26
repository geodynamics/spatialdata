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

/** @file pkgs/geocoords/lib/Projection.h
 *
 * @brief C++ Projection object
 *
 * C++ manager for types of geographic projections.
 */

#if !defined(_spatialdata_projection_h)
#define _spatialdata_projection_h

namespace spatialdata {
  class Projection;
}; // namespace spatialdata

/// C++ manager for types of geographic projections.
class spatialdata::Projection
{ // class Projection

 public :
  // PUBLIC ENUM ////////////////////////////////////////////////////////

  /** Projections */
  enum ProjEnum { AEA, // Albers Equal Area
		  AEQD, // Azimuthal Equidistant
		  AIRY, // Airy
		  AITOFF, // Aitoff
		  ALSK, // Mod. Stererographics of Alaska
		  APIAN, // Apian Globular I
		  AUGUST, // August Epicycloidal
		  BACON, // Bacon Globular
		  BIPC, // Bipolar conic of western hemisphere
		  BOGGS, // Boggs Eumorphic
		  BONNE, // Bonne (Werner lat_1=90)
		  CASS, // Cassini
		  CC, // Central Cylindrical
		  CEA, // Equal Area Cylindrical
		  CHAMB, // Chamberlin Trimetric
		  COLLG, // Collignon
		  CRAST, // Craster Parabolic (Putnins P4)
		  DENOY, // Denoyer Semi-Elliptical
		  ECK1, // Eckert I
		  ECK2, // Eckert II
		  ECK3, // Eckert III
		  ECK4, // Eckert IV
		  ECK5, // Eckert V
		  ECK6, // Eckert VI
		  EQC, // Equidistant Cylindrical (Plate Caree)
		  EQDC, // Equidistant Conic
		  EULER, // Euler
		  FAHEY, // Fahey
		  FOUC, // Foucaut
		  FOUC_S, // Foucaut Sinusoidal
		  GALL, // Gall (Gall Stereographic)
		  GEOS, // Geostationary Satellite View
		  GINS8, // Ginsburg VIII (TsNIIGAiK)
		  GN_SINU, // General Sinusoidal Series
		  GNOM, // Gnomonic
		  GOODE, // Goode Homolosine
		  GS48, // Mod. Stererographics of 48 U.S.
		  GS50, // Mod. Stererographics of 50 U.S.
		  HAMMER, // Hammer & Eckert-Greifendorff
		  HATANO, // Hatano Asymmetrical Equal Area
		  IMW_P, // International Map of the World Polyconic
		  KAV5, // Kavraisky V
		  KAV7, // Kavraisky VII
		  KROVAK, // Krovak
		  LABRD, // Laborde
		  LAEA, // Lambert Azimuthal Equal Area
		  LAGRNG, // Lagrange
		  LARR, // Larrivee
		  LASK, // Laskowski
		  LCC, // Lambert Conformal Conic
		  LCCA, // Lambert Conformal Conic Alternative
		  LEAC, // Lambert Equal Area Conic
		  LEE_OS, // Lee Oblated Stereographic
		  LOXIM, // Loximuthal
		  LSAT, // Space oblique for LANDSAT
		  MBT_S, // McBryde-Thomas Flat-Polar Sine (No. 1)
		  MBT_FPS, // McBryde-Thomas Flat-Pole Sine (No. 2)
		  MBTFPP, // McBride-Thomas Flat-Polar Parabolic
		  MBTFPQ, // McBryde-Thomas Flat-Polar Quartic
		  MBTFPS, // McBryde-Thomas Flat-Polar Sinusoidal
		  MERC, // Mercator
		  MIL_OS, // Miller Oblated Stereographic
		  MILL, // Miller Cylindrical
		  MPOLY, // Modified Polyconic
		  MOLL, // Mollweide
		  MURD1, // Murdoch I
		  MURD2, // Murdoch II
		  MURD3, // Murdoch III
		  NELL, // Nell
		  NELL_H, // Nell-Hammer
		  NICOL, // Nicolosi Globular
		  NSPER, // Near-sided perspective
		  NZMG, // New Zealand Map Grid
		  OB_TRAN, // General Oblique Transformation
		  OCEA, // Oblique Cylindrical Equal Area
		  OEA, // Oblated Equal Area
		  OMERC, // Oblique Mercator
		  ORTEL, // Ortelius Oval
		  ORTHO, // Orthographic
		  PCONIC, // Perspective Conic
		  POLY, // Polyconic (American)
		  PUTP1, // Putnins P1
		  PUTP2, // Putnins P2
		  PUTP3, // Putnins P3
		  PUTP3P, // Putnins P3'
		  PUTP4P, // Putnins P4'
		  PUTP5, // Putnins P5
		  PUTP5P, // Putnins P5'
		  PUTP6, // Putnins P6
		  PUTP6P, // Putnins P6'
		  QUA_AUT, // Quartic Authalic
		  ROBIN, // Robinson
		  RPOLY, // Rectangular Polyconic
		  SINU, // Sinusoidal (Sanson-Flamsteed)
		  SOMERC, // Swiss. Obl. Mercator
		  STERE, // Stereographic
		  STEREA, // Oblique Stereographic Alternative
		  TCC, // Transverse Central Cylindrical
		  TCEA, // Transverse Cylindrical Equal Area
		  TISSOT, // Tissot
		  TMERC, // Transverse Mercator
		  TPEQD, // Two Point Equidistant
		  TPERS, // Tilted perspective
		  UPS, // Universal Polar Stereographic
		  URM5, // Urmaev V
		  URMFPS, // Urmaev Flat-Polar Sinusoidal
		  UTM, // Universal Transverse Mercator (UTM)
		  VANDG, // van der Grinten (I)
		  VANDG2, // van der Grinten II
		  VANDG3, // van der Grinten III
		  VANDG4, // van der Grinten IV
		  VITK1, // Vitkovsky I
		  WAG1, // Wagner I (Kavraisky VI)
		  WAG2, // Wagner II
		  WAG3, // Wagner III
		  WAG4, // Wagner IV
		  WAG5, // Wagner V
		  WAG6, // Wagner VI
		  WAG7, // Wagner VII
		  WEREN, // Werenskiold I
		  WINK1, // Winkel I
		  WINK2, // Winkel II
		  WINTRI // Winkel Tripel
  }; 

 public :
  // PUBLIC METHODS /////////////////////////////////////////////////////

  /** Convert string to projection type.
   *
   * @param name Name of projection
   *
   * @returns Projection type
   */
  static ProjEnum stringToProj(const char* name);

  /** Convert projection type to string.
   *
   * @param proj Projection type
   *
   * @returns Name of projection
   *
   */
  static const char* projToString(const ProjEnum proj);

}; // class Projection

#endif spatialdata_projection_h

// version
// $Id: Projection.h,v 1.1 2005/05/25 17:28:11 baagaard Exp $

// End of file 
