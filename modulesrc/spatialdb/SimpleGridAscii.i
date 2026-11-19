// -*- c++ -*-
// -*- coding: utf-8 -*-
//
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2026 The SpatialData authors and contributors
// SPDX-License-Identifier: MIT


/** @file modulesrc/spatialdb/SimpleGridAscii.i
 *
 * @brief SWIG interface to C++ SimpleGridAscii object.
 */

namespace spatialdata {
    namespace spatialdb {
        class spatialdata::spatialdb::SimpleGridAscii { // SimpleGridAscii
          public:
            // PUBLIC METHODS /////////////////////////////////////////////////

            // Using default constructor.

            // Using default destructor.

            // Using default copy constructor

            /** Read the database.
             *
             * @param db Spatial database.
             */
            static void read(SimpleGridDB* db);

            /** Write the database.
             *
             * @param db Spatial database.
             */
            static void write(const SimpleGridDB& db);

        }; // class SimpleGridAscii

    } // namespace spatialdb
} // namespace spatialdata


// End of file
