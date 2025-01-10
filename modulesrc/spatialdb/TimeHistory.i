// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/spatialdb/TimeHistory.i
 *
 * @brief SWIG interface to C++ TimeHistory object.
 */

namespace spatialdata {
    namespace spatialdb {
        class TimeHistory
        { // class TimeHistory
public:

            // PUBLIC METHODS /////////////////////////////////////////////////

            /// Default constructor.
            TimeHistory(void);

            /** Constructor with description.
             *
             * @param description Description for database
             */
            TimeHistory(const char* description);

            /// Default destructor.
            ~TimeHistory(void);

            /** Set description of time history.
             *
             * @param description Description for time history.
             */
            void setDescription(const char* description);

            /** Get description of time history.
             *
             * @returns Description for time history.
             */
            const char* getDescription(void) const;

            /** Set filename for time history.
             *
             * @param name Name of file.
             */
            void setFilename(const char* name);

            /** Set filename for time history.
             *
             * @return Name of file.
             */
            const char* getFilename(void);

            /// Open the time history and prepare for querying.
            void open(void);

            /// Close the time history.
            void close(void);

            /** Query the database.
             *
             * @pre Must call open() before query()
             *
             * @param value Value in time history.
             * @param t Time for query.
             *
             * @returns 0 on success, 1 on failure (i.e., could not interpolate)
             */
            %apply double* OUTPUT { double* value };
            int query(double* value,
                      const double t);

            %clear(double* value);

        }; // class TimeHistory

    } // spatialdb
} // spatialdata

// End of file
