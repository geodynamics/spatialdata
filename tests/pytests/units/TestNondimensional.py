#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

import unittest

from spatialdata.units.Nondimensional import Nondimensional

from pyre.units.length import meter
from pyre.units.pressure import pascal
from pyre.units.time import second
from pyre.units.mass import kilogram    

class TestNondimensional(unittest.TestCase):

  def test_constructor(self):
    dim = Nondimensional()
    dim._configure()

    self.assertEqual(1.0*meter, dim._length)
    self.assertEqual(1.0*pascal, dim._pressure)
    self.assertEqual(1.0*second, dim._time)
    self.assertEqual(1.0*kilogram/meter**3, dim._density)

    return


  def test_initialize(self):
    dim = Nondimensional()
    dim._configure()
    dim.initialize()

    self.failIf(dim.cppHandle is None)
    return


  def test_lengthScale(self):
    dim = Nondimensional()
    dim._configure()
    dim._length = 2.0*meter

    self.assertEqual(2.0*meter, dim.lengthScale())
    self.assertEqual(1.0*pascal, dim.pressureScale())
    self.assertEqual(1.0*second, dim.timeScale())
    self.assertEqual(1.0*kilogram/meter**3, dim.densityScale())
    return


  def test_pressureScale(self):
    dim = Nondimensional()
    dim._configure()
    dim._pressure = 2.0*pascal

    self.assertEqual(1.0*meter, dim.lengthScale())
    self.assertEqual(2.0*pascal, dim.pressureScale())
    self.assertEqual(1.0*second, dim.timeScale())
    self.assertEqual(1.0*kilogram/meter**3, dim.densityScale())
    return


  def test_timeScale(self):
    dim = Nondimensional()
    dim._configure()
    dim._time = 2.0*second

    self.assertEqual(1.0*meter, dim.lengthScale())
    self.assertEqual(1.0*pascal, dim.pressureScale())
    self.assertEqual(2.0*second, dim.timeScale())
    self.assertEqual(1.0*kilogram/meter**3, dim.densityScale())
    return


  def test_densityScale(self):
    dim = Nondimensional()
    dim._configure()
    dim._density = 2.0*kilogram/meter**3

    self.assertEqual(1.0*meter, dim.lengthScale())
    self.assertEqual(1.0*pascal, dim.pressureScale())
    self.assertEqual(1.0*second, dim.timeScale())
    self.assertEqual(2.0*kilogram/meter**3, dim.densityScale())
    return


  def test_nondimensionalize(self):
    dim = Nondimensional()
    dim._configure()
    dim.initialize()

    scale = 8.0*meter
    value = 2.0*meter
    valueE = 0.25

    self.assertEqual(valueE, dim.nondimensionalize(value, scale))
    return


  def test_dimensionalize(self):
    dim = Nondimensional()
    dim._configure()
    dim.initialize()

    scale = 8.0*meter
    value = 0.25
    valueE = 2.0*meter

    self.assertEqual(valueE, dim.dimensionalize(value, scale))
    return


# End of file 
