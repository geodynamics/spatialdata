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
    from pyre.units.length import m
    cs.originElev = 12.0*m
    cs.ellipsoid = "clrk66"
    cs.datumHoriz = "NAD27"
    cs.datumVert = "mean sea level"
    cs.units = "km"
    cs.initialize()

    self.assertEqual(cs.ellipsoid, cs.cppHandle.ellipsoid)
    self.assertEqual(cs.datumHoriz, cs.cppHandle.datumHoriz)
    self.assertEqual(cs.datumVert, cs.cppHandle.datumVert)
    self.assertEqual(True, cs.isGeocentric)
    self.assertEqual(1.0e+3, cs.cppHandle.toMeters)

    (lon, lat, elev) = cs.cppHandle.getOrigin()
    self.assertAlmostEqual(cs.originLon, lon, 6)
    self.assertAlmostEqual(cs.originLat, lat, 6)
    self.assertAlmostEqual(cs.originElev.value, elev, 6)

    return

# version
__id__ = "$Id$"

# End of file 
