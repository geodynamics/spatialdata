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

import unittest

from spatialdata.geocoords.CSCart import CSCart


class TestCSCart(unittest.TestCase):

    def test_constructor(self):
        cs = CSCart()
        cs._configure()
        self.assertEqual(3, cs.getSpaceDim())

    def test_accessors(self):
        cs = CSCart()
        cs.inventory.units = "km"
        cs.inventory.spaceDim = 2
        cs._configure()

        self.assertEqual(1.0e+3, cs.getToMeters())
        self.assertEqual(2, cs.getSpaceDim())


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestCSCart]

    suite = unittest.TestSuite()
    for cls in TEST_CLASSES:
        suite.addTests(loader.loadTestsFromTestCase(cls))
    return suite


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
