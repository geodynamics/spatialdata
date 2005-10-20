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

class TestCoordSysGeo(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.CoordSysGeo import CoordSysGeo
    coordSys = CoordSysGeo()
    coordSys.ellipsoid = "clrk66"
    coordSys.datumHoriz = "NAD27"
    coordSys.datumVert = "mean sea level"
    coordSys.units = "km"
    coordSys.initialize()
    return

# version
__id__ = "$Id$"

# End of file 
