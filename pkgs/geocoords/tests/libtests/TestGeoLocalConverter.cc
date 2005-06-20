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

#include "TestGeoLocalConverter.h" // Implementation of class methods

#include "spatialdata/geocoords/GeoLocalConverter.h" // USES GeoLocalConverter
#include "spatialdata/geocoords/GeoCoordSys.h" // USES GeoCoordSys

#include <math.h> // USES M_PI
#include <string.h> // USES memcpy()

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::TestGeoLocalConverter );

// ----------------------------------------------------------------------
#include "data/TestGeoLocalConverter.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::TestGeoLocalConverter::testConstructor(void)
{ // testConstructor
  GeoCoordSys src;
  GeoLocalConverter converter(src);
} // testConstructor

// ----------------------------------------------------------------------
// Test geoToWGS84()
void
spatialdata::TestGeoLocalConverter::testGeoToWGS84(void)
{ // testGeoToWGS84
  GeoCoordSys csSrc;
  csSrc.projection("latlong");
  csSrc.datum("NAD27");
  csSrc.ellipsoid("clrk66");
  csSrc.initialize();

  GeoLocalConverter converter(csSrc);

  GeoCoordSys csCur(csSrc);

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = 0;
  if (size > 0)
    pCoords = new double[size];
  const double degToRad = M_PI / 180.0;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    pCoords[index++] = _LONLATNAD27ELEV[index] * degToRad;
    pCoords[index++] = _LONLATNAD27ELEV[index] * degToRad;
    pCoords[index++] = _LONLATNAD27ELEV[index];
  } // for
  
  converter._geoToWGS84(&pCoords, numLocs, &csCur);
  
  const double* pValsE = _LONLATWGS84ELEV;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    const double tolerance = 1.0e-06;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[index]/pValsE[index++]/degToRad,
				 tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[index]/pValsE[index++]/degToRad,
				 tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[index]/pValsE[index++],
				 tolerance);
  } // for
  
  delete[] pCoords; pCoords = 0;
} // testGeoToWGS84

// ----------------------------------------------------------------------
// Test elevToGeoidHt()
void
spatialdata::TestGeoLocalConverter::testElevToGeoidHt(void)
{ // testElevToGeoidHt
  GeoCoordSys csSrc;
  csSrc.projection("latlong");
  csSrc.datum("WGS84");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  GeoLocalConverter converter(csSrc);

  GeoCoordSys csCur(csSrc);

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = 0;
  if (size > 0)
    pCoords = new double[size];
  const double degToRad = M_PI / 180.0;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    pCoords[index++] = _LONLATWGS84ELEV[index] * degToRad;
    pCoords[index++] = _LONLATWGS84ELEV[index] * degToRad;
    pCoords[index++] = _LONLATWGS84ELEV[index];
  } // for
  
  converter._elevToGeoidHt(&pCoords, numLocs, &csCur);
  
  const double* pValsE = _LONLATWGS84GEOID;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    const double tolerance = 1.0e-06;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[index]/pValsE[index++]/degToRad,
				 tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[index]/pValsE[index++]/degToRad,
				 tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[index]/pValsE[index++],
				 tolerance);
  } // for
  
  delete[] pCoords; pCoords = 0;
} // testElevToGeoidHt

// ----------------------------------------------------------------------
// Test wgs84ToECEF()
void
spatialdata::TestGeoLocalConverter::testWGS84ToECEF(void)
{ // testWGS84ToECEF
  GeoCoordSys csSrc;
  csSrc.projection("latlong");
  csSrc.datum("WGS84");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  GeoLocalConverter converter(csSrc);

  GeoCoordSys csCur(csSrc);

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = 0;
  if (size > 0)
    pCoords = new double[size];
  const double degToRad = M_PI / 180.0;
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    pCoords[index++] = _LONLATWGS84ELEV[index] * degToRad;
    pCoords[index++] = _LONLATWGS84ELEV[index] * degToRad;
    pCoords[index++] = _LONLATWGS84ELEV[index];
  } // for
  
  converter._wgs84ToECEF(&pCoords, numLocs, &csCur);
  
  const double* pValsE = _XYZECEF;
  const double tolerance = 1.0e-05;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // testWGS84ToECEF

// ----------------------------------------------------------------------
// Test localOrigin()
void
spatialdata::TestGeoLocalConverter::testLocalOrigin(void)
{ // TestLocalOrigin
  GeoCoordSys src;
  src.projection("latlong");
  src.datum("NAD27");
  src.ellipsoid("clrk66");
  src.initialize();

  GeoLocalConverter converter(src);

  converter.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);

  const double tolerance = 1.0e-06;
  const double abstolerance = 0.01;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, converter._originLon/_ORIGINLON,
			       tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, converter._originLat/_ORIGINLAT,
			       tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINELEV, converter._originElev,
			       abstolerance);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINX, converter._originX, abstolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINY, converter._originY, abstolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINZ, converter._originZ, abstolerance);
} // TestLocalOrigin

// ----------------------------------------------------------------------
// Test convert()
void
spatialdata::TestGeoLocalConverter::testConvert(void)
{ // testConvert
  GeoCoordSys src;
  src.projection("latlong");
  src.datum("NAD27");
  src.ellipsoid("clrk66");
  src.initialize();

  GeoLocalConverter converter(src);
  converter.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);

  const bool is2D = false;
  const int numCoords = (is2D) ? 2 : 3;
  const int numLocs = _NUMLOCS;
  const int size = numLocs*numCoords;
  double* pCoords = (size > 0) ? new double[size] : 0;
  memcpy(pCoords, _LONLATNAD27ELEV, size*sizeof(double));
  
  converter.convert(&pCoords, numLocs, is2D);

  const double tolerance = 1.0e-6;
  const double* pXYZE = _XYZLOCAL;
  for (int i=0; i < size; ++i) {
    if (fabs(pXYZE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pXYZE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(pXYZE[i], pCoords[i], tolerance);
  } // for

  delete[] pCoords; pCoords = 0;
} // testConvert

// version
// $Id: TestGeoLocalConverter.cc,v 1.3 2005/06/19 19:38:36 baagaard Exp $

// End of file 
