#!/usr/bin/env nemesis
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================
#

import unittest

from spatialdata.units.NondimElasticQuasistatic import NondimElasticQuasistatic

from pythia.pyre.units.length import meter
from pythia.pyre.units.pressure import pascal
from pythia.pyre.units.time import year
from pythia.pyre.units.mass import kilogram


class TestNondimElasticQuasistatic(unittest.TestCase):

    def test_constructor(self):
        dim = NondimElasticQuasistatic()
        dim._configure()

        # Default values
        lengthScale = 1.0e+3 * meter
        pressureScale = 3.0e+10 * pascal
        timeScale = 1.0e+2 * year

        # Check defaults
        self.assertEqual(lengthScale, dim.getLengthScale())
        self.assertEqual(pressureScale, dim.getPressureScale())
        self.assertEqual(timeScale, dim.getTimeScale())

        velocityScale = lengthScale / timeScale
        densityScale = pressureScale / velocityScale**2
        self.assertEqual(densityScale, dim.getDensityScale())

        return


# End of file
