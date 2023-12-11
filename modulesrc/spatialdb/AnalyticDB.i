// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/spatialdb/AnalyticDB.i
 *
 * @brief SWIG interface to C++ AnalyticDB object.
 */

namespace spatialdata {
    namespace spatialdb {
        class AnalyticDB: public SpatialDB {
public:

            // PUBLIC METHODS /////////////////////////////////////////////////

            /// Default constructor.
            AnalyticDB(void);

            /** Constructor with label.
             *
             * @param label Label of database
             */
            AnalyticDB(const char* label);

            /// Default destructor.
            ~AnalyticDB(void);

            /** Set values in database.
             *
             * @param names Array of names of values in database.
             * @param units Array of units of values in database.
             * @param expressions Array of expressions in database.
             * @param numValues Number of values in database.
             */
            %apply(const char* const* string_list) {
                (const char* const* names)
            };
            %apply(const char* const* string_list) {
                (const char* const* units)
            };
            %apply(const char* const* string_list, const int list_len) {
                (const char* const* expressions,
                 const size_t numValues)
            };
            void setData(const char* const* names,
                         const char* const* names,
                         const char* const* expressions,
                         const size_t numValues);

            %clear(const char* const* names);
            %clear(const char* const* units);
            %clear(const char* const* expressions, const size_t numValues);

            /** Set coordinate system associated with user functions.
             *
             * @param cs Coordinate system.
             */
            void setCoordSys(const spatialdata::geocoords::CoordSys& cs);

            /// Open the database and prepare for querying.
            void open(void);

            /// Close the database.
            void close(void);

            /** Set values to be returned by queries.
             *
             * @pre Must call open() before setQueryValues()
             *
             * @param names Names of values to be returned in queries
             * @param numValues Number of values to be returned in queries
             */
            %apply(const char* const* string_list, const int list_len) {
                (const char* const* names, const size_t numValues)
            };
            void setQueryValues(const char* const* names,
                                const size_t numValues);

            %clear(const char* const* names, const size_t numValues);

            /** Query the database.
             *
             * @pre Must call open() before query()
             *
             * @param values Array for computed values (output from query), vals
             *   must be allocated BEFORE calling query().
             * @param numValues Number of values expected (size of pVals array)
             * @param coords Coordinates of point for query
             * @param numDims Number of dimensions for coordinates
             * @param pCSQuery Coordinate system of coordinates
             *
             * @returns 0 on success, 1 on failure (i.e., could not interpolate
             *   so values set to 0)
             */
            %apply(double* INPLACE_ARRAY1, int DIM1) {
                (double* values, const size_t numValues)
            };
            %apply(double* IN_ARRAY1, int DIM1) {
                (const double* coords, const size_t numDims)
            };
            int query(double* values,
                      const size_t numValues,
                      const double* coords,
                      const size_t numDims,
                      const spatialdata::geocoords::CoordSys* pCSQuery);

            %clear(double* values, const size_t numValues);
            %clear(const double* coords, const size_t numDims);

        }; // class AnalyticDB

    } // spatialdb
} // spatialdata

// End of file
