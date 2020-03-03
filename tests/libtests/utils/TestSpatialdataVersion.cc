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

#include <cppunit/extensions/HelperMacros.h>

#include "spatialdata/utils/SpatialdataVersion.hh" // USES PointStream

extern "C" {
#include "proj.h" // USES PROJ_VERSION_*
}

#include <string> // USES std::string()
#include <cstring> // USES strlen()
#include <stdio.h> // USES snprintf()

// ----------------------------------------------------------------------
namespace spatialdata {
    namespace utils {
        class TestSpatialdataVersion;
    } // utils
} // spatialdata

/// C++ unit testing for SpatialdataVersion
class spatialdata::utils::TestSpatialdataVersion : public CppUnit::TestFixture {
    // CPPUNIT TEST SUITE /////////////////////////////////////////////////
    CPPUNIT_TEST_SUITE(TestSpatialdataVersion);

    CPPUNIT_TEST(testVersion);
    CPPUNIT_TEST(testGitMetadata);
    CPPUNIT_TEST(testProjVersion);

    CPPUNIT_TEST_SUITE_END();

    // PUBLIC METHODS /////////////////////////////////////////////////////
public:

    /// Test version()
    void testVersion(void);

    /// Test git testGitMetadata.
    void testGitMetadata(void);

    /// Test projVersion()
    void testProjVersion(void);

}; // class TestSpatialdataVersion
CPPUNIT_TEST_SUITE_REGISTRATION(spatialdata::utils::TestSpatialdataVersion);

// ----------------------------------------------------------------------
// Test isRelease()
void
spatialdata::utils::TestSpatialdataVersion::testVersion(void) {
#if SPATIALDATA_RELEASE_VERSION
    CPPUNIT_ASSERT_MESSAGE("Mismatch in release flag.", SpatialdataVersion::isRelease());
#else
    CPPUNIT_ASSERT_MESSAGE("Mismatch in release flag.",!SpatialdataVersion::isRelease());
#endif

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in version string.",
                                 std::string(SPATIALDATA_VERSION), std::string(SpatialdataVersion::version()));

} // testVersion


// ----------------------------------------------------------------------
// Test git metadata.
void
spatialdata::utils::TestSpatialdataVersion::testGitMetadata(void) {
#if SPATIALDATA_RELEASE_VERSION
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in Git revision.",
                                 std::string("unknown"), std::string(SpatialdataVersion::gitRevision()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in Git hash.",
                                 std::string("unknown"), std::string(SpatialdataVersion::gitHash()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in Git date/time.",
                                 std::string("unknown"), std::string(SpatialdataVersion::gitDate()));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Mismatch in Git branch.",
                                 std::string("unknown"), std::string(SpatialdataVersion::gitBranch()));
#else
    // Git revision should be of the form vX.X.X-gXXXXX.
    const char* rev = SpatialdataVersion::gitRevision();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Git revision should start with 'v'.", 'v', rev[0]);

    // Git hash should contain lower case and numbers.
    const char* hash = SpatialdataVersion::gitHash();
    const int len = strlen(hash);
    for (int i = 0; i < len; ++i) {
        const int value = int(hash[i]);
        CPPUNIT_ASSERT_MESSAGE("Expect hash to contain lowercase letters and numbers.",
                               (value >= int('0') && value <= int('9')) || (value >= int('a') && value <= int('z')));
    } // for

    const char* datetime = SpatialdataVersion::gitDate();
    CPPUNIT_ASSERT_MESSAGE("Empty string for Git date/time.", strlen(datetime) > 0);

    const char* branch = SpatialdataVersion::gitBranch();
    CPPUNIT_ASSERT_MESSAGE("Empty string for Git branch.", strlen(branch) > 0);
#endif
} // testGitMetadata


// ----------------------------------------------------------------------
// Test projVersion()
void
spatialdata::utils::TestSpatialdataVersion::testProjVersion(void) {
    std::ostringstream version;
    version << PROJ_VERSION_MAJOR << "." << PROJ_VERSION_MINOR << "." << PROJ_VERSION_PATCH;
    CPPUNIT_ASSERT_EQUAL(version.str(), std::string(SpatialdataVersion::projVersion()));
} // testProjVersion


// End of file
