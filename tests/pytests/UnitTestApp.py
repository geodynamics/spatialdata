# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================
"""Application for running Python unit tests with code coverage.

We place this script in tests/pytests so that we can import it into the individual scripts in the
subdirectories.
"""


import unittest


class UnitTestApp():
    """
    Test application.
    """
    test_modules = []

    def __init__(self, src_dirs=["spatialdata"]):
        self.cov = None
        self.suite = []
        try:
            import coverage
            self.cov = coverage.Coverage(source=src_dirs)
        except ImportError:
            pass

    def run(self):
        """
        Run the application.
        """
        if self.cov:
            self.cov.start()

        success = unittest.TextTestRunner(verbosity=2).run(self._suite()).wasSuccessful()

        if self.cov:
            self.cov.stop()
            self.cov.save()
            self.cov.report()
        
        if not success:
            import sys
            sys.exit(1)


    def _suite(self):
        loader = unittest.defaultTestLoader
        suite = unittest.TestSuite()
        for mod in self.test_modules:
            suite.addTests(loader.loadTestsFromModule(mod))
        return suite


# End of file
