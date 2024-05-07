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

from spatialdata.units.Nondimensional import Nondimensional

from pythia.pyre.units.length import meter
from pythia.pyre.units.pressure import pascal
from pythia.pyre.units.time import second
from pythia.pyre.units.mass import kilogram
from pythia.pyre.units.temperature import kelvin


class TestNondimensional(unittest.TestCase):

    def test_constructor(self):
        dim = Nondimensional()
        dim._configure()

        self.assertEqual(1.0 * meter, dim.getLengthScale())
        self.assertEqual(1.0 * pascal, dim.getPressureScale())
        self.assertEqual(1.0 * second, dim.getTimeScale())
        self.assertEqual(1.0 * kilogram / meter**3, dim.getDensityScale())
        self.assertEqual(1.0 * kelvin, dim.getTemperatureScale())

    def test_lengthScale(self):
        dim = Nondimensional()
        dim._configure()
        dim.setLengthScale(2.0 * meter)

        self.assertEqual(2.0 * meter, dim.getLengthScale())
        self.assertEqual(1.0 * pascal, dim.getPressureScale())
        self.assertEqual(1.0 * second, dim.getTimeScale())
        self.assertEqual(1.0 * kilogram / meter**3, dim.getDensityScale())

    def test_pressureScale(self):
        dim = Nondimensional()
        dim._configure()
        dim.setPressureScale(2.0 * pascal)

        self.assertEqual(1.0 * meter, dim.getLengthScale())
        self.assertEqual(2.0 * pascal, dim.getPressureScale())
        self.assertEqual(1.0 * second, dim.getTimeScale())
        self.assertEqual(1.0 * kilogram / meter**3, dim.getDensityScale())

    def test_timeScale(self):
        dim = Nondimensional()
        dim._configure()
        dim.setTimeScale(2.0 * second)

        self.assertEqual(1.0 * meter, dim.getLengthScale())
        self.assertEqual(1.0 * pascal, dim.getPressureScale())
        self.assertEqual(2.0 * second, dim.getTimeScale())
        self.assertEqual(1.0 * kilogram / meter**3, dim.getDensityScale())

    def test_densityScale(self):
        dim = Nondimensional()
        dim._configure()
        dim.setDensityScale(2.0 * kilogram / meter**3)

        self.assertEqual(1.0 * meter, dim.getLengthScale())
        self.assertEqual(1.0 * pascal, dim.getPressureScale())
        self.assertEqual(1.0 * second, dim.getTimeScale())
        self.assertEqual(2.0 * kilogram / meter**3, dim.getDensityScale())

    def test_temperatureScale(self):
        dim = Nondimensional()
        dim._configure()
        dim.setTemperatureScale(2.0 * kelvin)

        self.assertEqual(1.0 * meter, dim.getLengthScale())
        self.assertEqual(1.0 * pascal, dim.getPressureScale())
        self.assertEqual(1.0 * second, dim.getTimeScale())
        self.assertEqual(2.0 * kelvin, dim.getTemperatureScale())

    def test_nondimensionalize(self):
        dim = Nondimensional()
        dim._configure()

        scale = 8.0 * meter
        value = 2.0 * meter
        valueE = 0.25

        self.assertEqual(valueE, dim.nondimensionalize(value, scale))

    def test_dimensionalize(self):
        dim = Nondimensional()
        dim._configure()

        scale = 8.0 * meter
        value = 0.25
        valueE = 2.0 * meter

        self.assertEqual(valueE, dim.dimensionalize(value, scale))


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestNondimensional]

    suite = unittest.TestSuite()
    for cls in TEST_CLASSES:
        suite.addTests(loader.loadTestsFromTestCase(cls))
    return suite


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
