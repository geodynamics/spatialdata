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

from spatialdata.utils.UnitTestApp import UnitTestApp

import unittest


class TestApp(UnitTestApp):
    """Test application.
    """

    def __init__(self):
        """Constructor.
        """
        UnitTestApp.__init__(self)
        return

    def _suite(self):
        """Setup the test suite.
        """
        suite = unittest.TestSuite()

        from TestNondimensional import TestNondimensional
        suite.addTest(unittest.makeSuite(TestNondimensional))

        from TestNondimElasticQuasistatic import TestNondimElasticQuasistatic
        suite.addTest(unittest.makeSuite(TestNondimElasticQuasistatic))

        from TestNondimElasticDynamic import TestNondimElasticDynamic
        suite.addTest(unittest.makeSuite(TestNondimElasticDynamic))

        return suite


# ----------------------------------------------------------------------
if __name__ == '__main__':
    app = TestApp()
    app.run()


# End of file
