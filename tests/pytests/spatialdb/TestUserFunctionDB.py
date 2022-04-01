#!/usr/bin/env nemesis
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

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
