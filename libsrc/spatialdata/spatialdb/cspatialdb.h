/*
 * ================================================================================================
 * This code is part of SpatialData, developed through the Computational Infrastructure
 * for Geodynamics (https://github.com/geodynamics/spatialdata).
 *
 * Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
 * All rights reserved.
 *
 * See https://mit-license.org/ and LICENSE.md and for license information.
 * =================================================================================================
 */
#pragma once

/** Call SpatialDB:Query().
 *
 * @param db Pointer to SpatialDB
 * @param vals Array for computed values (output from query), must be
 *   allocated BEFORE calling spatialdb_query*()
 * @param numVals Number of values expected (size of pVals array)
 * @param coords Coordinates of point for query
 * @param numDims Number of dimensions for coordinates
 * @param cs Pointer to CoordSys
 *
 * @returns 0 on success, 1 on failure (i.e., values not set)
 */
int spatialdb_query(void* db,
                    double* vals,
                    const int numVals,
                    const double* coords,
                    const int numDims,
                    const void* cs);

/* End of file  */
