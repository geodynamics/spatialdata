// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include "spatialdata/testing/TestDriver.hh"

int
main(int argc,
     char* argv[]) {
    spatialdata::testing::TestDriver driver;
    return driver.run(argc, argv);
} // main


// End of file
