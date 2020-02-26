#!/usr/bin/env nemesis
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

from spatialdata.geocoords.CSGeo import CSGeo


class TestCSGeo(unittest.TestCase):

    def test_constructor(self):
        cs = CSGeo()
        self.assertEqual(3, cs.getSpaceDim())

    def test_accessors(self):
        projString = "+proj=utm +zone=11"

        cs = CSGeo()
        cs.inventory.specification = projString
        cs.inventory.spaceDim = 2
        cs._configure()

        self.assertEqual(projString, cs.getString())
        self.assertEqual(2, cs.getSpaceDim())


# End of file
