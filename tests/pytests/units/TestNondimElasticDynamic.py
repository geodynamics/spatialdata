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

from spatialdata.units.NondimElasticDynamic import NondimElasticDynamic

from pythia.pyre.units.length import meter
from pythia.pyre.units.pressure import pascal
from pythia.pyre.units.time import second
from pythia.pyre.units.mass import kilogram


class TestNondimElasticDynamic(unittest.TestCase):

    def test_constructor(self):
        dim = NondimElasticDynamic()
        dim._configure()

        # Default values
        velocityScale = 3.0e+3 * meter / second
        densityScale = 3.0e+3 * kilogram / meter**3
        timeScale = 1.0 * second

        lengthScale = velocityScale * timeScale
        pressureScale = densityScale * velocityScale**2

        # Check defaults
        self.assertEqual(lengthScale, dim.getLengthScale())
        self.assertEqual(pressureScale, dim.getPressureScale())
        self.assertEqual(timeScale, dim.getTimeScale())
        self.assertEqual(densityScale, dim.getDensityScale())

        return


# End of file
