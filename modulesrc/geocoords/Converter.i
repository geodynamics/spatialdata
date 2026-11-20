// -*- c++ -*-
// -*- coding: utf-8 -*-
//
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2026 The SpatialData authors and contributors
// SPDX-License-Identifier: MIT


namespace spatialdata {
    namespace geocoords {
        class CoordSys; // forward declaration

        class Converter {
          public:
            // PUBLIC METHODS /////////////////////////////////////////////////

            /// Default constructor
            Converter(void);

            /// Default destructor
            ~Converter(void);

            /** Convert coordinates from source coordinate system to destination
             * coordinate system.
             *
             * @param coords Array of coordinates
             * @param numLocs Number of location
             * @param numDims Number of spatial dimensions in coordinates
             * @param pCSDest Pointer to destination coordinate system
             * @param pCSSrc Pointer to source coordinate system
             */
            %apply(double* INPLACE_ARRAY2,
                    int DIM1,
                    int DIM2){(double* coords,
                               const size_t numLocs,
                               const size_t numDims)};
            void convert(double* coords,
                         const size_t numLocs,
                         const size_t numDims,
                         const CoordSys* pCSDest,
                         const CoordSys* pCSSrc);

            %clear(double* coords,
                    const size_t numLocs,
                    const size_t numDims);

        }; // class Converter

    } // namespace geocoords
} // namespace spatialdata


// End of file
