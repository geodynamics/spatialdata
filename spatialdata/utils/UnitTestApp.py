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

## @brief Python application for Python unit tests.

from pyre.applications.Script import Script

import unittest

class UnitTestApp(Script):
  """
  Test application.
  """

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
    success = unittest.TextTestRunner(verbosity=2).run(self._suite()).wasSuccessful()
    
    if not success:
      import sys
      sys.exit(1)
    return


# End of file 
