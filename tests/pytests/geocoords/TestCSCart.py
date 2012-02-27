#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

class TestCSCart(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.CSCart import CSCart
    cs = CSCart()
    cs.inventory.units = "km"
    cs.inventory.spaceDim = 2
    cs._configure()
    cs.initialize()

    self.assertEqual(1.0e+3, cs.toMeters())
    self.assertEqual(2, cs.spaceDim())

    return


# End of file 
