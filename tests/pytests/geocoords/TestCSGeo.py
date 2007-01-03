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
    cs.spaceDim = 2
    cs.initialize()

    self.assertEqual(cs.ellipsoid, cs.cppHandle.ellipsoid)
    self.assertEqual(cs.datumHoriz, cs.cppHandle.datumHoriz)
    self.assertEqual(cs.datumVert, cs.cppHandle.datumVert)
    self.assertEqual(cs.isGeocentric, cs.isGeocentric)
    self.assertEqual(1.0e+3, cs.cppHandle.toMeters)
    self.assertEqual(2, cs.cppHandle.spaceDim)

    return


# End of file 
