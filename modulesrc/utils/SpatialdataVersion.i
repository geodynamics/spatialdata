// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/**
 * @file modulesrc/utils/SpatialdataVersion.i
 *
 * @brief C++ object for Spatialdata version information.
 */

namespace spatialdata {
    namespace utils {
        class SpatialdataVersion
        { // SpatialdataVersion
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

        }; // SpatialdataVersion

    } // utils
} // spatialdata

// End of file
