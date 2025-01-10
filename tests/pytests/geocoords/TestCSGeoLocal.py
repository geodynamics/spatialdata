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

import unittest

from spatialdata.testing.TestCases import make_suite
from spatialdata.geocoords.CSGeoLocal import CSGeoLocal


class TestCSGeoLocal(unittest.TestCase):

    def test_constructor(self):
        cs = CSGeoLocal()
        cs._configure()
        self.assertEqual(3, cs.getSpaceDim())

    def test_accessors(self):
        projString = "EPSG:29610" # UTM Zone 10

        cs = CSGeoLocal()
        cs.inventory.crsString = projString
        cs.inventory.spaceDim = 2
        cs.inventory.originX = 20.0
        cs.inventory.originY = 21.0
        cs.inventory.yAzimuth = 30.0
        cs._configure()

        self.assertEqual(projString, cs.getString())
        self.assertEqual(2, cs.getSpaceDim())
        originX, originY, yAzimuth = cs.getLocal()
        self.assertEqual(20.0, originX)
        self.assertEqual(21.0, originY)
        self.assertEqual(30.0,  yAzimuth)


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestCSGeoLocal]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
