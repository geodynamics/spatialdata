#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

class TestCSGeoProj(unittest.TestCase):

  def test_initialize(self):
    from spatialdata.geocoords.Projector import Projector
    proj = Projector()
    proj.inventory.projection = "aea"
    proj.inventory.units = "m"
    proj.inventory.projOptions = "+lon_0=-100.0 +lat_30.0 +k=0.9995"
    proj._configure()

    from spatialdata.geocoords.CSGeoProj import CSGeoProj
    cs = CSGeoProj()
    cs.inventory.ellipsoid = "clrk66"
    cs.inventory.datumHoriz = "NAD27"
    cs.inventory.datumVert = "mean sea level"
    cs.inventory.originLon = 105.0
    cs.inventory.originLat = 30.0
    cs.inventory.rotAngle = 0.0
    cs.inventory.units = "km"
    cs.inventory.spaceDim = 2
    cs.inventory.projector = proj
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
