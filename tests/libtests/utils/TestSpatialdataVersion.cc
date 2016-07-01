// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSpatialdataVersion.hh" // Implementation of class methods

#include "spatialdata/utils/SpatialdataVersion.hh" // USES PointStream

#include "proj_api.h" // USES PJ_VERSION

#include <string> // USES std::string()
#include <string.h> // USES strlen()
#include <stdio.h> // USES snprintf()

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::utils::TestSpatialdataVersion );

// ----------------------------------------------------------------------
// Test isRelease()
void
spatialdata::utils::TestSpatialdataVersion::testIsRelease(void)
{ // testIsRelease
#if SPATIALDATA_RELEASE_VERSION
  CPPUNIT_ASSERT(SpatialdataVersion::isRelease());
#else
  CPPUNIT_ASSERT(!SpatialdataVersion::isRelease());
#endif
} // testIsRelease

// ----------------------------------------------------------------------
// Test version()
void
spatialdata::utils::TestSpatialdataVersion::testVersion(void)
{ // testVersion
  CPPUNIT_ASSERT_EQUAL(std::string(SPATIALDATA_VERSION), std::string(SpatialdataVersion::version()));
} // testVersion

// ----------------------------------------------------------------------
// Test gitRevision()
void
spatialdata::utils::TestSpatialdataVersion::testGitRevision(void)
{ // testGitRevision
#if SPATIALDATA_RELEASE_VERSION
  CPPUNIT_ASSERT_EQUAL(std::string("unknown"), std::string(SpatialdataVersion::gitRevision()));
#else
  // Git revision should be of the form vX.X.X-gXXXXX.
  const char* rev = SpatialdataVersion::gitRevision();
  CPPUNIT_ASSERT_EQUAL('v', rev[0]);
#endif
} // testGitRevision

#include <iostream>
// ----------------------------------------------------------------------
// Test gitHash()
void
spatialdata::utils::TestSpatialdataVersion::testGitHash(void)
{ // testGitHash
#if SPATIALDATA_RELEASE_VERSION
  CPPUNIT_ASSERT_EQUAL(std::string("unknown"), std::string(SpatialdataVersion::gitHash()));
#else
  // Git hash should contain lower case and numbers.
  const char* hash = SpatialdataVersion::gitHash();
  const int len = strlen(hash);
  for (int i=0; i < len; ++i) {
    const int value = int(hash[i]);
    CPPUNIT_ASSERT((value >= int('0') && value <= int('9')) || (value >= int('a') && value <= int('z')));
  } // for
#endif
} // testGitHash

// ----------------------------------------------------------------------
// Test gitDate()
void
spatialdata::utils::TestSpatialdataVersion::testGitDate(void)
{ // testGitDate
#if SPATIALDATA_RELEASE_VERSION
  CPPUNIT_ASSERT_EQUAL(std::string("unknown"), std::string(SpatialdataVersion::gitRevision()));
#else
  const char* datetime = SpatialdataVersion::gitDate();
  CPPUNIT_ASSERT(strlen(datetime) > 0);
#endif
} // testGitDate

// ----------------------------------------------------------------------
// Test gitBranch()
void
spatialdata::utils::TestSpatialdataVersion::testGitBranch(void)
{ // testGitBranch
#if SPATIALDATA_RELEASE_VERSION
  CPPUNIT_ASSERT_EQUAL(std::string("unknown"), std::string(SpatialdataVersion::gitRevision()));
#else
  const char* branch = SpatialdataVersion::gitRevision();
  CPPUNIT_ASSERT(strlen(branch) > 0);
#endif
} // testGitBranch

// ----------------------------------------------------------------------
// Test projVersion()
void
spatialdata::utils::TestSpatialdataVersion::testProjVersion(void)
{ // testProjVersion
  const size_t maxsize = 64;
  char value[maxsize];
  snprintf(value, maxsize-1, "%d", PJ_VERSION);
  CPPUNIT_ASSERT_EQUAL(std::string(value), std::string(SpatialdataVersion::projVersion()));
} // testProjVersion


// End of file 
