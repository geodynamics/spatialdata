// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/spatialdb/SimpleIOAscii.i
 *
 * @brief SWIG interface to C++ SimpleIOAscii object.
 */

namespace spatialdata {
    namespace spatialdb {
        class SimpleDBData; // forward declaration

        class SimpleIOAscii: public SimpleIO
        { // SimpleIOAscii
public:

            // PUBLIC METHODS /////////////////////////////////////////////////

            /// Default constructor.
            SimpleIOAscii(void);

            /// Default destructor.
            ~SimpleIOAscii(void);

            /** Read the database.
             *
             * @param pData Database data
             * @param ppCS Pointer to coordinate system
             */
            void read(SimpleDBData* pData,
                      spatialdata::geocoords::CoordSys** ppCS);

            /** Write the database.
             *
             * @param data Database data
             * @param pCS Pointer to coordinate system
             */
            void write(const SimpleDBData& data,
                       const spatialdata::geocoords::CoordSys* pCS);

        }; // class SimpleIOAscii

    } // spatialdb
} // spatialdata

// End of file
