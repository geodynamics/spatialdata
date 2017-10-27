#!/usr/bin/env python
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

class TestUserFunctionDB(unittest.TestCase):

  def setUp(self):
    db = UserFunctionDB()
    db.inventory.label = "test"
    db._configure()
    self._db = db
    return


  def test_constructor(self):
    # Trigger call to setUp().
    return

# End of file 
