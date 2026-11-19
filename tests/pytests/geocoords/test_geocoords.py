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


if __name__ == "__main__":
    app = UnitTestApp(test_modules=TEST_MODULES, src_dirs=["spatialdata.geocoords"])
    app.run()


# End of file
