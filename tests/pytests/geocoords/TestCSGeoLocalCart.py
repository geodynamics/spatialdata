#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

class TestCSGeoLocalCart(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.CSGeoLocalCart import CSGeoLocalCart
    cs = CSGeoLocalCart()
    cs.inventory.originLon = -120.0
    cs.inventory.originLat = 38.4
    from pyre.units.length import m
    cs.inventory.originElev = 12.0*m
    cs.inventory.ellipsoid = "clrk66"
    cs.inventory.datumHoriz = "NAD27"
    cs.inventory.datumVert = "mean sea level"
    cs.inventory.units = "km"
    cs._configure()
    cs.initialize()

    self.assertEqual("clrk66", cs.ellipsoid())
    self.assertEqual("NAD27", cs.datumHoriz())
    self.assertEqual("mean sea level", cs.datumVert())
    self.assertEqual(True, cs.isGeocentric())
    self.assertEqual(1.0e+3, cs.toMeters())
    self.assertEqual(3, cs.spaceDim())

    (lon, lat, elev) = cs.origin()
    self.assertAlmostEqual(-120.0, lon, 6)
    self.assertAlmostEqual(38.4, lat, 6)
    self.assertAlmostEqual(12.0, elev, 6)

    return

# version
__id__ = "$Id$"

# End of file 
