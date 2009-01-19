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
    cs.inventory.ellipsoid = "clrk66"
    cs.inventory.datumHoriz = "NAD27"
    cs.inventory.datumVert = "mean sea level"
    cs.inventory.units = "km"
    cs.inventory.spaceDim = 2
    cs._configure()
    cs.initialize()

    self.assertEqual("clrk66", cs.ellipsoid())
    self.assertEqual("NAD27", cs.datumHoriz())
    self.assertEqual("mean sea level", cs.datumVert())
    self.assertEqual(False, cs.isGeocentric())
    self.assertEqual(1.0e+3, cs.toMeters())
    self.assertEqual(2, cs.spaceDim())

    return


# End of file 
