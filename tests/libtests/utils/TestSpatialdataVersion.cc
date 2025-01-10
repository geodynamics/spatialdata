// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "spatialdata/utils/SpatialdataVersion.hh" // USES PointStream

extern "C" {
#include "proj.h" // USES PROJ_VERSION_*
}

#include "catch2/catch_test_macros.hpp"

#include <string> // USES std::string()
#include <cstring> // USES strlen()
#include <stdio.h> // USES snprintf()
#include <sstream> // USES std::ostringstream

// ------------------------------------------------------------------------------------------------
namespace spatialdata {
    namespace utils {
        class TestSpatialdataVersion;
    } // utils
} // spatialdata

class spatialdata::utils::TestSpatialdataVersion {
    // PUBLIC METHODS /////////////////////////////////////////////////////////////////////////////
public:

    /// Test version()
    static
    void testVersion(void);

    /// Test git testGitMetadata.
    static
    void testGitMetadata(void);

    /// Test projVersion()
    static
    void testProjVersion(void);

}; // class TestSpatialdataVersion

// ------------------------------------------------------------------------------------------------
TEST_CASE("TestSpatialdataVersion::testVersion", "[TestSpatialdataVersion]") {
    spatialdata::utils::TestSpatialdataVersion::testVersion();
}
TEST_CASE("TestSpatialdataVersion::testGitMetadata", "[TestSpatialdataVersion]") {
    spatialdata::utils::TestSpatialdataVersion::testGitMetadata();
}
TEST_CASE("TestSpatialdataVersion::testProjVersion", "[TestSpatialdataVersion]") {
    spatialdata::utils::TestSpatialdataVersion::testProjVersion();
}

// ------------------------------------------------------------------------------------------------
// Test isRelease()
void
spatialdata::utils::TestSpatialdataVersion::testVersion(void) {
#if SPATIALDATA_RELEASE_VERSION
    CHECK(SpatialdataVersion::isRelease());
#else
    CHECK(!SpatialdataVersion::isRelease());
#endif

    CHECK(std::string(SPATIALDATA_VERSION) == std::string(SpatialdataVersion::version()));

} // testVersion


// ------------------------------------------------------------------------------------------------
// Test git metadata.
void
spatialdata::utils::TestSpatialdataVersion::testGitMetadata(void) {
#if SPATIALDATA_RELEASE_VERSION
    CHECK(std::string("unknown") == std::string(SpatialdataVersion::gitRevision()));
    CHECK(std::string("unknown") == std::string(SpatialdataVersion::gitHash()));
    CHECK(std::string("unknown") == std::string(SpatialdataVersion::gitDate()));
    CHECK(std::string("unknown") == std::string(SpatialdataVersion::gitBranch()));
#else
    // Git revision should be of the form vX.X.X-gXXXXX.
    const char* rev = SpatialdataVersion::gitRevision();
    CHECK('v' == rev[0]);

    // Git hash should contain lower case and numbers.
    const char* hash = SpatialdataVersion::gitHash();
    const int len = strlen(hash);
    for (int i = 0; i < len; ++i) {
        const int value = int(hash[i]);
        assert((value >= int('0') && value <= int('9')) || (value >= int('a') && value <= int('z')));
    } // for

    const char* datetime = SpatialdataVersion::gitDate();
    CHECK(strlen(datetime) > 0);

    const char* branch = SpatialdataVersion::gitBranch();
    CHECK(strlen(branch) > 0);
#endif
} // testGitMetadata


// ------------------------------------------------------------------------------------------------
// Test projVersion()
void
spatialdata::utils::TestSpatialdataVersion::testProjVersion(void) {
    std::ostringstream version;
    version << PROJ_VERSION_MAJOR << "." << PROJ_VERSION_MINOR << "." << PROJ_VERSION_PATCH;
    CHECK(version.str() == std::string(SpatialdataVersion::projVersion()));
} // testProjVersion


// End of file
