// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

/** @file modulesrc/geocoords/CSGeoLocal.i
 *
 * @brief SWIG interface to C++ CSGeoLocal object.
 */

namespace spatialdata {
    namespace geocoords {
        class CSGeoLocal: public CSGeo {
            friend class TestCSGeoLocal;

public:

            // PUBLIC METHODS /////////////////////////////////////////////////

            /// Default constructor
            CSGeoLocal(void);

            /// Default destructor
            ~CSGeoLocal(void);

            /** Clone coordinate system.
             *
             * @returns Pointer to copy
             */
            CoordSys* clone(void) const override;

            /** Set parameters specifying local coordinate system.
             *
             * @param[in] originX X coordinate of local origin.
             * @param[in] originY Y coordinate of local origin.
             * @param[in] yAzimuth Azimuth (degrees) of y axis.
             */
            void setLocal(const double originX,
                          const double originY,
                          const double yAzimuth);

            /** Get parameters specifying local coordinate system.
             *
             * @param[out] originX X coordinate of local origin.
             * @param[out] originY Y coordinate of local origin.
             * @param[out] yAzimuth Azimuth (degrees) of y axis.
             */
            %apply double* OUTPUT { double* originX };
            %apply double* OUTPUT { double* originY };
            %apply double* OUTPUT { double* yAzimuth };
            void getLocal(double* originX,
                          double* originY,
                          double* yAzimuth) const;

            %clear double* originX;
            %clear double* originY;
            %clear double* yAzimuth;

            /** Convert coordinates from local coordinate system to geographic coordinate system.
             *
             * @param[inout] coords Array of coordinates
             * @param[in] numLocs Number of location
             * @param[in] numDims Number of spatial dimensions in coordinates
             */
            void localToGeographic(double* coords,
                                   const size_t numLocs,
                                   const size_t numDims) const override;

            /** Convert coordinates from geographic coordinate system to local coordinate system.
             *
             * @param[inout] coords Array of coordinates
             * @param[in] numLocs Number of location
             * @param[in] numDims Number of spatial dimensions in coordinates
             */
            void geographicToLocal(double* coords,
                                   const size_t numLocs,
                                   const size_t numDims) const override;

            /** Pickle coordinate system to ascii stream.
             *
             * @param s Output stream
             */
            void pickle(std::ostream& s) const override;

            /** Unpickle coordinate system from ascii stream.
             *
             * @param s Input stream
             */
            void unpickle(std::istream& s) override;

        }; // class CSGeoLocal

    } // geocoords
} // spatialdata

// End of file
