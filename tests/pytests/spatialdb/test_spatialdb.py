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

from spatialdata.testing.UnitTestApp import UnitTestApp

import TestSimpleIOAscii
import TestSimpleDB
import TestUniformDB
import TestAnalyticDB
import TestSimpleGridDB
import TestUserFunctionDB
import TestCompositeDB
import TestGravityField
import TestTimeHistoryIO
import TestTimeHistory
import TestGenSimpleDBApp


TEST_MODULES = [
    TestSimpleIOAscii,
    TestSimpleDB,
    TestUniformDB,
    TestAnalyticDB,
    TestSimpleGridDB,
    TestUserFunctionDB,
    TestCompositeDB,
    TestGravityField,
    TestTimeHistoryIO,
    TestTimeHistory,
    TestGenSimpleDBApp,
]


if __name__ == '__main__':
    app = UnitTestApp(test_modules=TEST_MODULES, src_dirs=["spatialdata.spatialdb"])
    app.run()


# End of file
