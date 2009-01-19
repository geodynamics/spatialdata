#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
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
