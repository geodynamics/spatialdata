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
from spatialdata.spatialdb.UserFunctionDB import UserFunctionDB


class TestUserFunctionDB(unittest.TestCase):

    def setUp(self):
        db = UserFunctionDB()
        db.inventory.label = "test"
        db.cs._configure()
        db._configure()
        self._db = db

    def test_constructor(self):
        # Trigger call to setUp().
        pass


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestUserFunctionDB]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
