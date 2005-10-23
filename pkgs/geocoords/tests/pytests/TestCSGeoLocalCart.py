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

class TestCSGeoLocalCart(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.CSGeoLocalCart import CSGeoLocalCart
    cs = CSGeoLocalCart()
    cs.originLon = -120.0
    cs.originLat = 38.0
    cs.originElev = 12.0
    cs.ellipsoid = "clrk66"
    cs.datumHoriz = "NAD27"
    cs.datumVert = "mean sea level"
    cs.units = "km"
    cs.initialize()
    return

# version
__id__ = "$Id$"

# End of file 
