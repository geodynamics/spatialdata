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
    cs.units = "km"
    cs.spaceDim = 2
    cs.initialize()

    self.assertEqual(1.0e+3, cs.cppHandle.toMeters)
    self.assertEqual(2, cs.cppHandle.spaceDim)

    return


# End of file 
