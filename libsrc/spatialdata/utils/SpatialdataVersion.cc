// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

#include <portinfo>

#include "SpatialdataVersion.hh" // Implementation of class methods

// ----------------------------------------------------------------------
const bool spatialdata::utils::SpatialdataVersion::_isRelease = int(SPATIALDATA_RELEASE_VERSION);
const char* spatialdata::utils::SpatialdataVersion::_version = PACKAGE_VERSION;
const char* spatialdata::utils::SpatialdataVersion::_gitBranch = SPATIALDATA_GIT_BRANCH;
const char* spatialdata::utils::SpatialdataVersion::_gitRevision = SPATIALDATA_GIT_REVISION;
const char* spatialdata::utils::SpatialdataVersion::_gitDate = SPATIALDATA_GIT_DATE;
const char* spatialdata::utils::SpatialdataVersion::_gitHash = SPATIALDATA_GIT_HASH;

// ----------------------------------------------------------------------
// Default constructor.
spatialdata::utils::SpatialdataVersion::SpatialdataVersion(void)
{}

// ----------------------------------------------------------------------
// Default destrictor.
spatialdata::utils::SpatialdataVersion::~SpatialdataVersion(void)
{}

#include <iostream>
// ----------------------------------------------------------------------
// Is source from a release?
bool
spatialdata::utils::SpatialdataVersion::isRelease(void)
{ // isRelease
  return _isRelease;
} // isRelease

// ----------------------------------------------------------------------
// Get version number.
const char*
spatialdata::utils::SpatialdataVersion::version(void)
{ // version
  return _version;
} // version

// ----------------------------------------------------------------------
// Get GIT revision.
const char*
spatialdata::utils::SpatialdataVersion::gitRevision(void)
{ // gitRevision
  return _gitRevision;
} // gitRevision

// ----------------------------------------------------------------------
// Get GIT hash.
const char*
spatialdata::utils::SpatialdataVersion::gitHash(void)
{ // gitHash
  return _gitHash;
} // gitHash

// ----------------------------------------------------------------------
// Get date of GIT revision.
const char*
spatialdata::utils::SpatialdataVersion::gitDate(void)
{ // gitDate
  return _gitDate;
} // gitDate

// ----------------------------------------------------------------------
// Get GIT branch.
const char*
spatialdata::utils::SpatialdataVersion::gitBranch(void)
{ // gitBranch
  return _gitBranch;
} // gitBranch


// End of file 
