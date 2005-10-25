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

#include "TestGeoid.h" // Implementation of class methods

#include "spatialdata/geocoords/Geoid.h" // USES Geoid

#include <math.h> // USES M_PI

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestGeoid );

// ----------------------------------------------------------------------
#include "data/TestGeoid.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestGeoid::testConstructor(void)
{ // testConstructor
  Geoid geoid;
} // testConstructor

// ----------------------------------------------------------------------
// Test elevation()
void
spatialdata::geocoords::TestGeoid::testElevation(void)
{ // testElevation
  Geoid geoid;
  geoid.initialize();
  
  const int numLocs = _NUMLOCS;
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    const double* pLonLat = &_LONLAT[2*iLoc];
    const double deg2rad = M_PI / 180.0;
    const double elev = geoid.elevation(pLonLat[0]*deg2rad, 
					pLonLat[1]*deg2rad);
    const double elevE = _GEOIDHT[iLoc];
    const double tolerance = 1.0e-6;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, elev/elevE, tolerance);
  } // for
} // testElevation

// version
// $Id: TestGeoid.cc,v 1.1 2005/06/19 19:38:36 baagaard Exp $

// End of file 
