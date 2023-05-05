# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================
#
# @brief Python application for Python unit tests.
#
# We place this script in tests/pytests because we must initialize coverage
# *before* importing any spatialdata modules.

import unittest


class UnitTestApp():
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


# End of file
