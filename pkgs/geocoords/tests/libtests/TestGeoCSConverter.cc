// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestGeoCSConverter.h" // Implementation of class methods

#include "spatialdata/geocoords/GeoCSConverter.h" // USES GeoCSConverter
#include "spatialdata/geocoords/GeoCoordSys.h" // USES GeoCoordSys

#include <math.h> // USES M_PI

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::TestGeoCSConverter );

// ----------------------------------------------------------------------
#include "data/TestGeoCSConverter.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::TestGeoCSConverter::testConstructor(void)
{ // testConstructor
  GeoCoordSys src;
  GeoCoordSys dest;
  GeoCSConverter converter(dest, src);
} // testConstructor

// ----------------------------------------------------------------------
// Test convert() with source, destination arrays
void
spatialdata::TestGeoCSConverter::testConvertDestSrc(void)
{ // testConvertDestSrc
  GeoCoordSys src;
  src.projection("latlong");
  src.datum("NAD27");
  src.ellipsoid("clrk66");
  src.initialize();

  GeoCoordSys dest;
  dest.projection("latlong");
  dest.datum("WGS84");
  dest.ellipsoid("WGS84");
  dest.initialize();

  GeoCSConverter converter(dest, src);

  double* pLonLatDest = 0;
  const double* pLonLatSrc = _LONLATSRC;
  const int numLocs = _NUMLOCS;
  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  converter.convert(&pLonLatDest, pLonLatSrc, numLocs, is2D);

  const int size = numCoords*numLocs;
  const double tolerance = 1.0e-5;
  for (int i=0; i < size; ++i)
    if (fabs(_LONLATDEST[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(pLonLatDest[i]/_LONLATDEST[i], 1.0, 
				   tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(pLonLatDest[i], _LONLATDEST[i], tolerance);
  delete[] pLonLatDest; pLonLatDest = 0;
} // testConvertDestSrc

// ----------------------------------------------------------------------
// Test convert() with x, y, z, arrays
void
spatialdata::TestGeoCSConverter::testConvertDest(void)
{ // testConvertXYZ
  GeoCoordSys src;
  src.projection("latlong");
  src.datum("NAD27");
  src.ellipsoid("clrk66");
  src.initialize();

  GeoCoordSys dest;
  dest.projection("geocent");
  dest.datum("WGS84");
  dest.ellipsoid("WGS84");
  dest.initialize();

  GeoCSConverter converter(dest, src);

  double* pXYZ = 0;
  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  if (size > 0)
    pXYZ = new double[size];
  const double degToRad = M_PI / 180.0;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    pXYZ[index++] = _LONLATSRC[index] * degToRad;
    pXYZ[index++] = _LONLATSRC[index] * degToRad;
    pXYZ[index++] = _LONLATSRC[index];
  } // for
  converter.convert(&pXYZ, numLocs);

  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i) {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(pXYZ[i]/_XYZDEST[i], 1.0, tolerance);
  } // for
  delete[] pXYZ; pXYZ = 0;
} // testConvertXYZ

// version
// $Id: TestGeoCSConverter.cc,v 1.1 2005/05/25 17:29:42 baagaard Exp $

// End of file 
