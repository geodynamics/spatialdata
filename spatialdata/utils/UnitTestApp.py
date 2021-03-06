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

# @brief Python application for Python unit tests.

from pythia.pyre.applications.Script import Script

import unittest


class UnitTestApp(Script):
    """
    Test application.
    """
    cov = None
    try:
        import coverage
        cov = coverage.Coverage(source=["spatialdata"])
    except ImportError:
        pass

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="unittestapp"):
        """
        Constructor.
        """
        Script.__init__(self, name)
        return

    def main(self):
        """
        Run the application.
        """
        if self.cov:
            self.cov.start()

        success = unittest.TextTestRunner(verbosity=2).run(self._suite()).wasSuccessful()

        if self.cov:
            self.cov.stop()
            self.cov.save()
        
        if not success:
            import sys
            sys.exit(1)
        return


# End of file
