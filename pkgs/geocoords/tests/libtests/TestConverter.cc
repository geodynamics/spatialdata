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

#include "TestConverter.h" // Implementation of class methods

#include "spatialdata/geocoords/Converter.h" // USES Converter
#include "spatialdata/geocoords/CoordSys.h" // USES CoordSys
#include "spatialdata/geocoords/CoordSysGeo.h" // USES CoordSysGeo
#include "spatialdata/geocoords/CoordSysLocal.h" // USES CoordSysLocal

#include <math.h> // USES M_PI
#include <string.h> // USES memcpy()

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestConverter );

// ----------------------------------------------------------------------
#include "data/TestConverter.dat"

// ----------------------------------------------------------------------
// Test NAD27 -> WGS84
void
spatialdata::geocoords::TestConverter::testNAD27ToWGS84(void)
{ // testNAD27ToWGS84
  CoordSysGeo csSrc;
  csSrc.datumHoriz("NAD27");
  csSrc.datumVert("mean sea level");
  csSrc.ellipsoid("clrk66");
  csSrc.initialize();

  CoordSysGeo csDest;
  csDest.datumHoriz("WGS84");
  csDest.datumVert("WGS84 Ellipsoid");
  csDest.ellipsoid("WGS84");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = new double [size];
  memcpy(pCoords, _LONLATNAD27ELEV, size*sizeof(double));
  
  Converter::convert(&pCoords, numLocs, csDest, csSrc);
  
  const double* pValsE = _LONLATWGS84GEOID;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // testNAD27ToWGS84

// ----------------------------------------------------------------------
// Test NAD27 -> WGS84
void
spatialdata::geocoords::TestConverter::testWGS84ToNAD27(void)
{ // testWGS84ToNAD27
  CoordSysGeo csSrc;
  csSrc.datumHoriz("WGS84");
  csSrc.datumVert("WGS84 Ellipsoid");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  CoordSysGeo csDest;
  csDest.datumHoriz("NAD27");
  csDest.datumVert("mean sea level");
  csDest.ellipsoid("clrk66");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = new double [size];
  memcpy(pCoords, _LONLATWGS84GEOID, size*sizeof(double));
  
  Converter::convert(&pCoords, numLocs, csDest, csSrc);
  
  const double* pValsE = _LONLATNAD27ELEV;
  const double tolerance = 1.0e-05;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // testWGS84ToNAD27

// ----------------------------------------------------------------------
// Test WGS84 -> ECEF
void
spatialdata::geocoords::TestConverter::testWGS84ToECEF(void)
{ // testWGS84ToECEF
  CoordSysGeo csSrc;
  csSrc.datumHoriz("WGS84");
  csSrc.datumVert("WGS84 ellipsoid");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  CoordSysGeo csDest;
  csDest.isGeocentric(true);
  csDest.datumHoriz("WGS84");
  csDest.datumVert("WGS84 ellipsoid");
  csDest.ellipsoid("WGS84");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = new double[size];
  memcpy(pCoords, _LONLATWGS84GEOID, size*sizeof(double));
  
  Converter::convert(&pCoords, numLocs, csDest, csSrc);
  
  const double* pValsE = _XYZECEF;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // testWGS84ToECEF

// ----------------------------------------------------------------------
// Test ECEF -> WGS84
void
spatialdata::geocoords::TestConverter::testECEFToWGS84(void)
{ // testECEFToWGS84
  CoordSysGeo csSrc;
  csSrc.isGeocentric(true);
  csSrc.datumHoriz("WGS84");
  csSrc.datumVert("WGS84 ellipsoid");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  CoordSysGeo csDest;
  csDest.datumHoriz("WGS84");
  csDest.datumVert("WGS84 ellipsoid");
  csDest.ellipsoid("WGS84");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = new double[size];
  memcpy(pCoords, _XYZECEF, size*sizeof(double));
  
  Converter::convert(&pCoords, numLocs, csDest, csSrc);
  
  const double* pValsE = _LONLATWGS84GEOID;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // testECEFToWGS84

// ----------------------------------------------------------------------
// Test NAD27ToLocal()
void
spatialdata::geocoords::TestConverter::testNAD27ToLocal(void)
{ // testNad27ToLocal
  CoordSysGeo csSrc;
  csSrc.datumHoriz("NAD27");
  csSrc.datumVert("mean sea level");
  csSrc.ellipsoid("clrk66");
  csSrc.initialize();

  CoordSysLocal csDest;
  csDest.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV,
		     "clrk66", "NAD27", "mean sea level");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = new double [size];
  memcpy(pCoords, _LONLATNAD27ELEV, size*sizeof(double));
  
  Converter::convert(&pCoords, numLocs, csDest, csSrc);
  
  const double* pValsE = _XYZLOCAL;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    if (fabs(pValsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(pValsE[i], pCoords[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // TestNAD27ToLocal

// ----------------------------------------------------------------------
// Test LocalToNAD27()
void
spatialdata::geocoords::TestConverter::testLocalToNAD27(void)
{ // testNad27ToLocal
  CoordSysLocal csSrc;
  csSrc.localOrigin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV,
		     "clrk66", "NAD27", "mean sea level");
  csSrc.initialize();

  CoordSysGeo csDest;
  csDest.datumHoriz("NAD27");
  csDest.datumVert("mean sea level");
  csDest.ellipsoid("clrk66");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numCoords = 3;
  const int size = numLocs*numCoords;
  double* pCoords = new double [size];
  memcpy(pCoords, _XYZLOCAL, size*sizeof(double));
  
  Converter::convert(&pCoords, numLocs, csDest, csSrc);
  
  const double* pValsE = _LONLATNAD27ELEV;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    if (fabs(pValsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pCoords[i]/pValsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(pValsE[i], pCoords[i], tolerance);
  
  delete[] pCoords; pCoords = 0;
} // TestLocalToNAD27

// version
// $Id$

// End of file 
