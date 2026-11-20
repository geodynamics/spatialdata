#!/usr/bin/env nemesis
# -*- python -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


import unittest

from spatialdata.testing.TestCases import make_suite
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

        self.assertEqual(1.0e3, cs.getToMeters())
        self.assertEqual(2, cs.getSpaceDim())


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestCSCart]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
