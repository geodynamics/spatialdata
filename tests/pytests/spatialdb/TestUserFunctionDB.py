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

from spatialdata.spatialdb.UserFunctionDB import UserFunctionDB


# ----------------------------------------------------------------------------------------------------------------------
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


# ----------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestUserFunctionDB))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file
