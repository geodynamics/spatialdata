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

class TestCSGeo(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.CSGeo import CSGeo
    cs = CSGeo()
    cs.ellipsoid = "clrk66"
    cs.datumHoriz = "NAD27"
    cs.datumVert = "mean sea level"
    cs.units = "km"
    cs.initialize()
    return

# version
__id__ = "$Id$"

# End of file 
