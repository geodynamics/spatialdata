#!/usr/bin/env nemesis
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import pathlib
import sys

sys.path.append(str(pathlib.Path(__file__).resolve().parent.parent))
from UnitTestApp import UnitTestApp


import TestSpatialdataVersion


TEST_MODULES = [
    TestSpatialdataVersion,
]


if __name__ == '__main__':
    app = UnitTestApp(src_dirs=["spatialdata.utils"])
    app.test_modules = TEST_MODULES
    app.run()


# End of file
