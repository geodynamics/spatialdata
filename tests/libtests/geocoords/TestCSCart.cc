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

#include "TestCSCart.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CSCart
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCSCart );

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSCart::testConstructor(void)
{ // testConstructor
  CSCart cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test toMeters()
void
spatialdata::geocoords::TestCSCart::testToMeters(void)
{ // testToMeters
  CSCart cs;
  const double toMeters = 3.2;
  cs.toMeters(toMeters);
  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, cs.toMeters(), tolerance);
} // testToMeters

// ----------------------------------------------------------------------
// Test spaceDim()
void
spatialdata::geocoords::TestCSCart::testSpaceDim(void)
{ // testSpaceDim
  CSCart cs;
  const int spaceDim = 2;
  cs.setSpaceDim(spaceDim);
  CPPUNIT_ASSERT_EQUAL(spaceDim, cs.spaceDim());
} // testSpaceDim

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestCSCart::testInitialize(void)
{ // testInitialize
  CSCart cs;
  cs.initialize();
} // testInitialize

// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSCart::testPickle(void)
{ // testPickle
  CSCart csA;
  const double toMeters = 5.4;
  const int spaceDim = 2;
  csA.toMeters(toMeters);
  csA.setSpaceDim(spaceDim);

  std::stringstream s;
  csA.pickle(s);

  CSCart csB;
  csB.unpickle(s);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, csB.toMeters(), tolerance);
  CPPUNIT_ASSERT_EQUAL(spaceDim, csB.spaceDim());
} // testPickle


// End of file 
