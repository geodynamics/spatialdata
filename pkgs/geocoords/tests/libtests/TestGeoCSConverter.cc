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
// Test convert() with datum switch
void
spatialdata::TestGeoCSConverter::testConvertGeoDatum(void)
{ // testConvertGeoDatum
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

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numCoords*numLocs;
  double* pLonLat = (size > 0) ? new double[size] : 0;
  memcpy(pLonLat, _LONLATSRC, size*sizeof(double));

  const bool isDeg = true;
  converter.convert(&pLonLat, numLocs, isDeg, is2D);

  const double tolerance = 1.0e-5;
  for (int i=0; i < size; ++i)
    if (fabs(_LONLATDEST[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pLonLat[i]/_LONLATDEST[i],
				   tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(_LONLATDEST[i], pLonLat[i], tolerance);
  delete[] pLonLat; pLonLat = 0;
} // testConvertGeoDatum

// ----------------------------------------------------------------------
// Test convert() with latlong to geocent
void
spatialdata::TestGeoCSConverter::testConvertGeoXYZ(void)
{ // testConvertGeoXYZ
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

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numLocs*numCoords;
  double* pCoords = (size > 0) ? new double[size] : 0;
  memcpy(pCoords, _LONLATSRC, size*sizeof(double));

  const bool isDeg = true;
  converter.convert(&pCoords, numLocs, isDeg, is2D);

  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/_XYZDEST[i], tolerance);

  delete[] pCoords; pCoords = 0;
} // testConvertGeoXYZ

// version
// $Id: TestGeoCSConverter.cc,v 1.2 2005/06/01 16:51:58 baagaard Exp $

// End of file 
