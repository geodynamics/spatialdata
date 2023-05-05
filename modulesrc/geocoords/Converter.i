// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/geocoords/Converter.i
 *
 * @brief SWIG interface to C++ Converter object.
 */

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
            %apply(double* INPLACE_ARRAY2, int DIM1, int DIM2) {
                (double* coords, const size_t numLocs, const size_t numDims)
            };
            void convert(double* coords,
                         const size_t numLocs,
                         const size_t numDims,
                         const CoordSys* pCSDest,
                         const CoordSys* pCSSrc);

            %clear(double* coords, const size_t numLocs, const size_t numDims);

        }; // class Converter

    } // geocoords
} // spatialdata

// End of file
