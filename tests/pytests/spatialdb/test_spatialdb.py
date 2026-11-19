#!/usr/bin/env nemesis
# -*- python -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


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


if __name__ == "__main__":
    app = UnitTestApp(test_modules=TEST_MODULES, src_dirs=["spatialdata.spatialdb"])
    app.run()


# End of file
