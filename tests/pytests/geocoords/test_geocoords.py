#!/usr/bin/env nemesis
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import pathlib
import sys

from spatialdata.testing.UnitTestApp import UnitTestApp

import TestCSCart
import TestCSGeo
import TestCSGeoLocal
import TestConverter


TEST_MODULES = [
    TestCSCart,
    TestCSGeo,
    TestCSGeoLocal,
    TestConverter,
]


if __name__ == '__main__':
    app = UnitTestApp(test_modules=TEST_MODULES, src_dirs=["spatialdata.geocoords"])
    app.run()


# End of file
