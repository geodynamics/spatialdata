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

#include "TestCSCart.h" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.h" // USES CSCart
#include "spatialdata/geocoords/CSCart.h" // USES CSCart

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
// Test toMeters
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
  csA.toMeters(toMeters);

  std::stringstream s;
  csA.pickle(s);

  CSCart csB;
  csB.unpickle(s);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, csB.toMeters(), tolerance);
} // testPickle

// version
// $Id$

// End of file 
