#!/usr/bin/env nemesis
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

from spatialdata.testing.TestCases import make_suite
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


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestNondimElasticDynamic]
    return make_suite(test_classes=TEST_CLASSES, loader=loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
