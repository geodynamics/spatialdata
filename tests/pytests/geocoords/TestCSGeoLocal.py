#!/usr/bin/env nemesis
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================
#

import unittest

from spatialdata.geocoords.CSGeoLocal import CSGeoLocal


class TestCSGeoLocal(unittest.TestCase):

    def test_constructor(self):
        cs = CSGeoLocal()
        cs._configure()
        self.assertEqual(3, cs.getSpaceDim())

    def test_accessors(self):
        projString = "EPSG:29610" # UTM Zone 10

        cs = CSGeoLocal()
        cs.inventory.crsString = projString
        cs.inventory.spaceDim = 2
        cs.inventory.originX = 20.0
        cs.inventory.originY = 21.0
        cs.inventory.yAzimuth = 30.0
        cs._configure()

        self.assertEqual(projString, cs.getString())
        self.assertEqual(2, cs.getSpaceDim())
        originX, originY, yAzimuth = cs.getLocal()
        self.assertEqual(20.0, originX)
        self.assertEqual(21.0, originY)
        self.assertEqual(30.0,  yAzimuth)


# End of file
