// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestConverter.hh" // Implementation of class methods

#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeoLocalCart.hh" // USES CSGeoLocalCart

#include <math.h> // USES M_PI
#include <string.h> // USES memcpy()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestConverter );

// ----------------------------------------------------------------------
#include "data/TestConverter.dat"

// ----------------------------------------------------------------------
// Test NAD27 -> WGS84
void
spatialdata::geocoords::TestConverter::testNAD27ToWGS84(void)
{ // testNAD27ToWGS84
  CSGeo csSrc;
  csSrc.datumHoriz("NAD27");
  csSrc.datumVert("mean sea level");
  csSrc.ellipsoid("clrk66");
  csSrc.initialize();

  CSGeo csDest;
  csDest.datumHoriz("WGS84");
  csDest.datumVert("ellipsoid");
  csDest.ellipsoid("WGS84");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double [size];
  memcpy(coords, _LONLATNAD27ELEV, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _LONLATWGS84GEOID;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/valsE[i], tolerance);
  
  delete[] coords; coords = 0;
} // testNAD27ToWGS84

// ----------------------------------------------------------------------
// Test NAD27 -> WGS84
void
spatialdata::geocoords::TestConverter::testWGS84ToNAD27(void)
{ // testWGS84ToNAD27
  CSGeo csSrc;
  csSrc.datumHoriz("WGS84");
  csSrc.datumVert("ellipsoid");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  CSGeo csDest;
  csDest.datumHoriz("NAD27");
  csDest.datumVert("mean sea level");
  csDest.ellipsoid("clrk66");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double [size];
  memcpy(coords, _LONLATWGS84GEOID, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _LONLATNAD27ELEV;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/valsE[i], tolerance);
  
  delete[] coords; coords = 0;
} // testWGS84ToNAD27

// ----------------------------------------------------------------------
// Test WGS84 -> ECEF
void
spatialdata::geocoords::TestConverter::testWGS84ToECEF(void)
{ // testWGS84ToECEF
  CSGeo csSrc;
  csSrc.datumHoriz("WGS84");
  csSrc.datumVert("ellipsoid");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  CSGeo csDest;
  csDest.isGeocentric(true);
  csDest.datumHoriz("WGS84");
  csDest.datumVert("ellipsoid");
  csDest.ellipsoid("WGS84");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double[size];
  memcpy(coords, _LONLATWGS84GEOID, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _XYZECEF;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/valsE[i], tolerance);
  
  delete[] coords; coords = 0;
} // testWGS84ToECEF

// ----------------------------------------------------------------------
// Test ECEF -> WGS84
void
spatialdata::geocoords::TestConverter::testECEFToWGS84(void)
{ // testECEFToWGS84
  CSGeo csSrc;
  csSrc.isGeocentric(true);
  csSrc.datumHoriz("WGS84");
  csSrc.datumVert("ellipsoid");
  csSrc.ellipsoid("WGS84");
  csSrc.initialize();

  CSGeo csDest;
  csDest.datumHoriz("WGS84");
  csDest.datumVert("ellipsoid");
  csDest.ellipsoid("WGS84");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double[size];
  memcpy(coords, _XYZECEF, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _LONLATWGS84GEOID;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/valsE[i], tolerance);
  
  delete[] coords; coords = 0;
} // testECEFToWGS84

// ----------------------------------------------------------------------
// Test NAD27ToLocal()
void
spatialdata::geocoords::TestConverter::testNAD27ToLocal(void)
{ // testNad27ToLocal
  CSGeo csSrc;
  csSrc.datumHoriz("NAD27");
  csSrc.datumVert("mean sea level");
  csSrc.ellipsoid("clrk66");
  csSrc.initialize();

  CSGeoLocalCart csDest;
  csDest.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  csDest.ellipsoid("clrk66");
  csDest.datumHoriz("NAD27");
  csDest.datumVert("mean sea level");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double [size];
  memcpy(coords, _LONLATNAD27ELEV, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _XYZLOCAL;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    if (fabs(valsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/valsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(valsE[i], coords[i], tolerance);
  
  delete[] coords; coords = 0;
} // TestNAD27ToLocal

// ----------------------------------------------------------------------
// Test LocalToNAD27()
void
spatialdata::geocoords::TestConverter::testLocalToNAD27(void)
{ // testNad27ToLocal
  CSGeoLocalCart csSrc;
  csSrc.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  csSrc.ellipsoid("clrk66");
  csSrc.datumHoriz("NAD27");
  csSrc.datumVert("mean sea level");
  csSrc.initialize();

  CSGeo csDest;
  csDest.datumHoriz("NAD27");
  csDest.datumVert("mean sea level");
  csDest.ellipsoid("clrk66");
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double [size];
  memcpy(coords, _XYZLOCAL, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _LONLATNAD27ELEV;
  const double tolerance = 1.0e-06;
  for (int i=0; i < size; ++i)
    if (fabs(valsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/valsE[i], tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL(valsE[i], coords[i], tolerance);
  
  delete[] coords; coords = 0;
} // TestLocalToNAD27

// ----------------------------------------------------------------------
// Test CartToCart()
void
spatialdata::geocoords::TestConverter::testCartToCart(void)
{ // testCartToCart
  const double srcToMeters = 2.0;
  const double destToMeters = 0.4;

  CSCart csSrc;
  csSrc.toMeters(srcToMeters);
  csSrc.initialize();

  CSCart csDest;
  csDest.toMeters(destToMeters);
  csDest.initialize();

  const int numLocs = _NUMLOCS;
  const int numDims = 3;
  const int size = numLocs*numDims;
  double* coords = new double [size];
  memcpy(coords, _XYZLOCAL, size*sizeof(double));
  
  Converter::convert(coords, numLocs, numDims, &csDest, &csSrc);
  
  const double* valsE = _XYZLOCAL;
  const double tolerance = 1.0e-06;
  const double scale = srcToMeters / destToMeters;
  for (int i=0; i < size; ++i)
    if (fabs(valsE[i]) > tolerance)
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, coords[i]/(valsE[i]*scale), 
				   tolerance);
    else
      CPPUNIT_ASSERT_DOUBLES_EQUAL((valsE[i]*scale), coords[i], tolerance);
  
  delete[] coords; coords = 0;
} // TestCartToCart


// End of file 
