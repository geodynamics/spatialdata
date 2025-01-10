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
from spatialdata.geocoords.CSGeo import CSGeo


class TestCSGeo(unittest.TestCase):

    def test_constructor(self):
        cs = CSGeo()
        cs._configure()
        self.assertEqual(3, cs.getSpaceDim())

    def test_accessors(self):
        projString = "+proj=utm +zone=11"

        cs = CSGeo()
        cs.inventory.crsString = projString
        cs.inventory.spaceDim = 2
        cs._configure()

        self.assertEqual(projString, cs.getString())
        self.assertEqual(2, cs.getSpaceDim())


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestCSGeo]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
