# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================
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
