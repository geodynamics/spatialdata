// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University at Buffalo
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ======================================================================
//

#include <portinfo>

#include "SpatialdataVersion.hh" // Implementation of class methods

#include "proj.h" // Proj API

// ----------------------------------------------------------------------
#define STR_HELPER(x) #x
#define STR(c) STR_HELPER(x)

#define VERSION_JOINER_HELPER(major, minor, patch, dot) STR_HELPER(major ## dot ## minor ## dot ## patch)
#define VERSION_JOINER(major, minor, patch) VERSION_JOINER_HELPER(major, minor, patch, .)

const bool spatialdata::utils::SpatialdataVersion::_isRelease = int(SPATIALDATA_RELEASE_VERSION);
const char* spatialdata::utils::SpatialdataVersion::_version = SPATIALDATA_VERSION;
const char* spatialdata::utils::SpatialdataVersion::_gitBranch = SPATIALDATA_GIT_BRANCH;
const char* spatialdata::utils::SpatialdataVersion::_gitRevision = SPATIALDATA_GIT_REVISION;
const char* spatialdata::utils::SpatialdataVersion::_gitDate = SPATIALDATA_GIT_DATE;
const char* spatialdata::utils::SpatialdataVersion::_gitHash = SPATIALDATA_GIT_HASH;
const char* spatialdata::utils::SpatialdataVersion::_projVersion =
    VERSION_JOINER(PROJ_VERSION_MAJOR, PROJ_VERSION_MINOR, PROJ_VERSION_PATCH);

// ----------------------------------------------------------------------
// Default constructor.
spatialdata::utils::SpatialdataVersion::SpatialdataVersion(void)
{}


// ----------------------------------------------------------------------
// Default destrictor.
spatialdata::utils::SpatialdataVersion::~SpatialdataVersion(void)
{}


// ----------------------------------------------------------------------
// Is source from a release?
bool
spatialdata::utils::SpatialdataVersion::isRelease(void) {
    return _isRelease;
} // isRelease


// ----------------------------------------------------------------------
// Get version number.
const char*
spatialdata::utils::SpatialdataVersion::version(void) {
    return _version;
} // version


// ----------------------------------------------------------------------
// Get GIT revision.
const char*
spatialdata::utils::SpatialdataVersion::gitRevision(void) {
    return _gitRevision;
} // gitRevision


// ----------------------------------------------------------------------
// Get GIT hash.
const char*
spatialdata::utils::SpatialdataVersion::gitHash(void) {
    return _gitHash;
} // gitHash


// ----------------------------------------------------------------------
// Get date of GIT revision.
const char*
spatialdata::utils::SpatialdataVersion::gitDate(void) {
    return _gitDate;
} // gitDate


// ----------------------------------------------------------------------
// Get GIT branch.
const char*
spatialdata::utils::SpatialdataVersion::gitBranch(void) {
    return _gitBranch;
} // gitBranch


// ----------------------------------------------------------------------
// Get Proj.4 version number.
const char*
spatialdata::utils::SpatialdataVersion::projVersion(void) {
    return _projVersion;
} // projVersion


// End of file
