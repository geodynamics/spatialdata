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

from spatialdata.geocoords.CSCart import CSCart


class TestCSCart(unittest.TestCase):

    def test_constructor(self):
        cs = CSCart()
        cs._configure()
        self.assertEqual(3, cs.getSpaceDim())

    def test_accessors(self):
        cs = CSCart()
        cs.inventory.units = "km"
        cs.inventory.spaceDim = 2
        cs._configure()

        self.assertEqual(1.0e+3, cs.getToMeters())
        self.assertEqual(2, cs.getSpaceDim())


# End of file
