#!/usr/bin/env nemesis
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================
#
import os
import sys

current = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.dirname(current))
from UnitTestApp import UnitTestApp

import unittest


class TestApp(UnitTestApp):
    """Test application.
    """

    def _suite(self):
        """Setup the test suite.
        """
        suite = unittest.TestSuite()

        from TestSpatialdataVersion import TestSpatialdataVersion
        suite.addTest(unittest.makeSuite(TestSpatialdataVersion))

        return suite


# ----------------------------------------------------------------------
if __name__ == '__main__':
    app = TestApp()
    app.main()


# End of file
