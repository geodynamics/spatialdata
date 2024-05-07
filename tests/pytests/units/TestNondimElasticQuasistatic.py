#!/usr/bin/env nemesis
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

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


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestNondimElasticQuasistatic]

    suite = unittest.TestSuite()
    for cls in TEST_CLASSES:
        suite.addTests(loader.loadTestsFromTestCase(cls))
    return suite


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
