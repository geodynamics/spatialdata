// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/spatialdb/SpatialDBObj.i
 *
 * @brief SWIG interface to C++ SpatialDB object.
 */

namespace spatialdata {
    namespace geocoords {
        class CoordSys; // forward declaration
    } // geocoords

    namespace spatialdb {
        class SpatialDB
        { // class SpatialDB
public:

            // PUBLIC METHODS /////////////////////////////////////////////////

            /// Default constructor.
            SpatialDB(void);

            /** Constructor with description.
             *
             * @param description Description for database
             */
            SpatialDB(const char* description);

            /// Default destructor.
            virtual
            ~SpatialDB(void);

            /** Set description of spatial database.
             *
             * @param description Description for database
             */
            void setDescription(const char* description);

            /** Get description of spatial database.
             *
             * @returns Description for database
             */
            const char* getDescription(void) const;

            /// Open the database and prepare for querying.
            virtual
            void open(void) = 0;

            /// Close the database.
            virtual
            void close(void) = 0;

            /** Set values to be returned by queries.
             *
             * @pre Must call open() before setQueryValues()
             *
             * @param names Names of values to be returned in queries
             * @param numVals Number of values to be returned in queries
             */
            %apply(const char* const* string_list, const int list_len) {
                (const char* const* names, const size_t numVals)
            };
            virtual
            void setQueryValues(const char* const* names,
                                const size_t numVals) = 0;

            %clear(const char* const* names, const size_t numVals);

            /** Query the database.
             *
             * @note vals should be preallocated to accommodate numVals values.
             *
             * @pre Must call open() before query().
             *
             * @param vals Array for computed values (output from query), must be
             *   allocated BEFORE calling query().
             * @param numVals Number of values expected (size of pVals array)
             * @param coords Coordinates of point for query [numDims].
             * @param numDims Number of dimensions for coordinates.
             * @param csQuery Coordinate system of coordinates.
             *
             * @returns 0 on success, 1 on failure (i.e., could not interpolate)
             */
            %apply(double* INPLACE_ARRAY1, int DIM1) {
                (double* vals, const size_t numVals)
            };
            %apply(double* IN_ARRAY1, int DIM1) {
                (const double* coords, const size_t numDims)
            };
            virtual
            int query(double* vals,
                      const size_t numVals,
                      const double* coords,
                      const size_t numDims,
                      const spatialdata::geocoords::CoordSys* csQuery) = 0;

            %clear(double* vals, const size_t numVals);
            %clear(const double* coords, const size_t numDims);

            /** Perform multiple queries of the database.
             *
             * @note vals should be preallocated to accommodate numVals values
             * at numLocs locations.
             *
             * @note err should be preallocated to accommodate numLocs values.
             *
             * @pre Must call open() before query().
             *
             * @param vals Array for computed values (output from query), must be
             *   allocated BEFORE calling query() [numLocs*numVals].
             * @param numLocsV Number of locations.
             * @param numValsV Number of values expected.
             * @param err Array for error flag values (output from query), must be
             *   allocated BEFORE calling query() [numLocs].
             * @param numLocsE Number of locations.
             * @param coords Coordinates of point for query [numLocs*numDims].
             * @param numLocsC Number of locations.
             * @param numDimsC Number of dimensions for coordinates.
             * @param csQuery Coordinate system of coordinates.
             */
            %apply(double* INPLACE_ARRAY2, int DIM1, int DIM2) {
                (double* vals,
                 const size_t numLocsV,
                 const size_t numValsV)
            };
            %apply(int* INPLACE_ARRAY1, int DIM1) {
                (int* err,
                 const size_t numLocsE)
            };
            %apply(double* IN_ARRAY2, int DIM1, int DIM2) {
                (const double* coords,
                 const size_t numLocsC,
                 const size_t numDimsC)
            };
            void multiquery(double* vals,
                            const size_t numLocsV,
                            const size_t numValsV,
                            int* err,
                            const size_t numLocsE,
                            const double* coords,
                            const size_t numLocsC,
                            const size_t numDimsC,
                            const spatialdata::geocoords::CoordSys* csQuery);

            %clear(double* vals, const size_t numLocsV, const size_t numValsV);
            %clear(int* err, const size_t numLocsE);
            %clear(const double* coords, const size_t numLocsC, const size_t numDimsC);

        }; // class SpatialDB

    } // spatialdb
} // spatialdata

// End of file
