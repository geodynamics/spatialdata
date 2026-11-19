// -*- c++ -*-
// -*- coding: utf-8 -*-
//
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2026 The SpatialData authors and contributors
// SPDX-License-Identifier: MIT


#include "spatialdata/testing/TestDriver.hh"

int
main(int argc,
     char* argv[]) {
    spatialdata::testing::TestDriver driver;
    return driver.run(argc, argv);
} // main


// End of file
