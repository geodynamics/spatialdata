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
// Test convert() with change in horizontal datum
void
spatialdata::TestGeoCSConverter::testConvertGeoDatumH(void)
{ // testConvertGeoDatumH
  GeoCoordSys src;
  src.projection("latlong");
  src.datumHoriz("NAD27");
  src.datumVert("MSL");
  src.ellipsoid("clrk66");
  src.initialize();

  GeoCoordSys dest;
  dest.projection("latlong");
  dest.datumHoriz("WGS84");
  dest.datumVert("MSL");
  dest.ellipsoid("WGS84");
  dest.initialize();

  GeoCSConverter converter(dest, src);

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numCoords*numLocs;
  double* pLonLat = (size > 0) ? new double[size] : 0;
  memcpy(pLonLat, _LONLATNAD27ELEV, size*sizeof(double));
  
  const bool isDeg = true;
  converter.convert(&pLonLat, numLocs, isDeg, is2D);
  
  const double tolerance = 1.0e-5;
  for (int i=0; i < size; ++i)
    if (fabs(_LONLATWGS84ELEV[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pLonLat[i]/_LONLATWGS84ELEV[i],
				   tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(_LONLATWGS84ELEV[i], pLonLat[i], tolerance);
  delete[] pLonLat; pLonLat = 0;
} // testConvertGeoDatumH

// ----------------------------------------------------------------------
// Test convert() with changes in both vertical and horizontal datums
// NAD27Elev -> WGS84Geoid
void
spatialdata::TestGeoCSConverter::testConvertGeoDatumA(void)
{ // testConvertGeoDatumA
  GeoCoordSys src;
  src.projection("latlong");
  src.datumHoriz("NAD27");
  src.datumVert("MSL");
  src.ellipsoid("clrk66");
  src.initialize();

  GeoCoordSys dest;
  dest.projection("latlong");
  dest.datumHoriz("WGS84");
  dest.datumVert("WGS84 ellipsoid");
  dest.ellipsoid("WGS84");
  dest.initialize();

  GeoCSConverter converter(dest, src);

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numCoords*numLocs;
  double* pLonLat = (size > 0) ? new double[size] : 0;
  memcpy(pLonLat, _LONLATNAD27ELEV, size*sizeof(double));
  
  const bool isDeg = true;
  converter.convert(&pLonLat, numLocs, isDeg, is2D);
  
  const double tolerance = 1.0e-5;
  for (int i=0; i < size; ++i)
    if (fabs(_LONLATWGS84GEOID[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pLonLat[i]/_LONLATWGS84GEOID[i],
				   tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(_LONLATWGS84GEOID[i], pLonLat[i],
				   tolerance);
  delete[] pLonLat; pLonLat = 0;
} // testConvertGeoDatumA

// ----------------------------------------------------------------------
// Test convert() with changes in both vertical and horizontal datums
// WGS84Geoid -> NAD27Elev
void
spatialdata::TestGeoCSConverter::testConvertGeoDatumB(void)
{ // testConvertGeoDatumB
  GeoCoordSys dest;
  dest.projection("latlong");
  dest.datumHoriz("NAD27");
  dest.datumVert("MSL");
  dest.ellipsoid("clrk66");
  dest.initialize();

  GeoCoordSys src;
  src.projection("latlong");
  src.datumHoriz("WGS84");
  src.datumVert("WGS84 ellipsoid");
  src.ellipsoid("WGS84");
  src.initialize();

  GeoCSConverter converter(dest, src);

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numCoords*numLocs;
  double* pLonLat = (size > 0) ? new double[size] : 0;
  memcpy(pLonLat, _LONLATWGS84GEOID, size*sizeof(double));
  
  const bool isDeg = true;
  converter.convert(&pLonLat, numLocs, isDeg, is2D);
  
  const double tolerance = 1.0e-5;
  for (int i=0; i < size; ++i)
    if (fabs(_LONLATNAD27ELEV[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pLonLat[i]/_LONLATNAD27ELEV[i],
				   tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(_LONLATNAD27ELEV[i], pLonLat[i],
				   tolerance);
  delete[] pLonLat; pLonLat = 0;
} // testConvertGeoDatumB

// ----------------------------------------------------------------------
// Test convert() with latlong to geocent
void
spatialdata::TestGeoCSConverter::testConvertGeoXYZ(void)
{ // testConvertGeoXYZ
  GeoCoordSys src;
  src.projection("latlong");
  src.datumHoriz("WGS84");
  src.datumVert("WGS84 ellipsoid");
  src.ellipsoid("WGS84");
  src.initialize();

  GeoCoordSys dest;
  dest.projection("geocent");
  dest.datumHoriz("WGS84");
  dest.datumVert("WGS84 ellipsoid");
  dest.ellipsoid("WGS84");
  dest.initialize();

  GeoCSConverter converter(dest, src);

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numLocs*numCoords;
  double* pCoords = (size > 0) ? new double[size] : 0;
  memcpy(pCoords, _LONLATWGS84GEOID, size*sizeof(double));

  const bool isDeg = true;
  converter.convert(&pCoords, numLocs, isDeg, is2D);

  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/_XYZECEF[i], tolerance);

  delete[] pCoords; pCoords = 0;
} // testConvertGeoXYZ

// version
// $Id: TestGeoCSConverter.cc,v 1.3 2005/07/02 00:21:13 baagaard Exp $

// End of file 
