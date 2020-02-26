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

    def _suite(self):
        """Setup the test suite.
        """
        suite = unittest.TestSuite()

        from TestSimpleIOAscii import TestSimpleIOAscii
        suite.addTest(unittest.makeSuite(TestSimpleIOAscii))

        from TestSimpleDB import TestSimpleDB
        suite.addTest(unittest.makeSuite(TestSimpleDB))

        from TestUniformDB import TestUniformDB
        suite.addTest(unittest.makeSuite(TestUniformDB))

        from TestSimpleGridDB import TestSimpleGridDB
        suite.addTest(unittest.makeSuite(TestSimpleGridDB))

        from TestUserFunctionDB import TestUserFunctionDB
        suite.addTest(unittest.makeSuite(TestUserFunctionDB))

        from TestCompositeDB import TestCompositeDB
        suite.addTest(unittest.makeSuite(TestCompositeDB))

        from TestGravityField import TestGravityField
        suite.addTest(unittest.makeSuite(TestGravityField))

        from TestTimeHistoryIO import TestTimeHistoryIO
        suite.addTest(unittest.makeSuite(TestTimeHistoryIO))

        from TestTimeHistory import TestTimeHistory
        suite.addTest(unittest.makeSuite(TestTimeHistory))

        from TestGenSimpleDBApp import TestGenSimpleDBApp
        suite.addTest(unittest.makeSuite(TestGenSimpleDBApp))

        return suite


# ----------------------------------------------------------------------
if __name__ == '__main__':
    app = TestApp()
    app.run()


# End of file
