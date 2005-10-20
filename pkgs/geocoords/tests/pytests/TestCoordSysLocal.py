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

class TestCoordSysLocal(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.CoordSysLocal import CoordSysLocal
    coordSys = CoordSysLocal()
    coordSys.originLon = -120.0
    coordSys.originLat = 38.0
    coordSys.originElev = 12.0
    coordSys.ellipsoid = "clrk66"
    coordSys.datumHoriz = "NAD27"
    coordSys.datumVert = "mean sea level"
    coordSys.units = "km"
    coordSys.initialize()
    return

# version
__id__ = "$Id$"

# End of file 
