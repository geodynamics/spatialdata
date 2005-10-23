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
    cs.initialize()
    return

# version
__id__ = "$Id$"

# End of file 
