// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "utilsfwd.hh" // forward declarations

/// @brief C++ object for getting version info.
class spatialdata::utils::SpatialdataVersion { // SpatialdataVersion
    friend class TestSpatialdataVersion; // unit testing

    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
public:

    /// Default constructor.
    SpatialdataVersion(void);

    /// Default destrictor.
    ~SpatialdataVersion(void);

    /** Is source from a release?
     *
     * @returns True if source code comes from a release?
     */
    static
    bool isRelease(void);

    /** Get version number.
     *
     * @returns Version number.
     */
    static
    const char* version(void);

    /** Get GIT revision.
     *
     * @returns GIT revision.
     */
    static
    const char* gitRevision(void);

    /** Get GIT hash.
     *
     * @returns GIT hash.
     */
    static
    const char* gitHash(void);

    /** Get date of GIT revision.
     *
     * @returns Date of GIT revision.
     */
    static
    const char* gitDate(void);

    /** Get GIT branch.
     *
     * @returns GIT branch.
     */
    static
    const char* gitBranch(void);

    /** Get Proj.4 version number.
     *
     * @returns Version number.
     */
    static
    const char* projVersion(void);

    // PRIVATE METHODS //////////////////////////////////////////////////////
private:

    SpatialdataVersion(const SpatialdataVersion&); ///< Not implemented
    const SpatialdataVersion& operator=(const SpatialdataVersion&); ///< Not implemented

    // PRIVATE MEMBERS //////////////////////////////////////////////////////
private:

    static const bool _isRelease; ///< Is source code from a release?
    static const char* _version; ///< Version number.
    static const char* _gitRevision; ///< GIT revision.
    static const char* _gitDate; ///< Date of GIT revision.
    static const char* _gitHash; ///< GIT hash.
    static const char* _gitBranch; ///< GIT branch.

    static const char* _projVersion; ///< Proj.4 version number.

}; // SpatialdataVersion

// End of file
