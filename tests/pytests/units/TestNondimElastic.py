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

from spatialdata.units.NondimElastic import NondimElastic

from pyre.units.length import meter
from pyre.units.pressure import pascal
from pyre.units.time import second
from pyre.units.mass import kilogram    

class TestNondimElastic(unittest.TestCase):

  def test_constructor(self):
    dim = NondimElastic()
    dim._configure()

    self.assertEqual(1.0*meter, dim._length)
    self.assertEqual(1.0*pascal, dim._pressure)
    self.assertEqual(1.0*second, dim._time)
    self.assertEqual(1.0*kilogram/meter**3, dim._density)

    return


  def test_initialize(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    self.failIf(dim.cppHandle is None)
    return


  def test_utonLength(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*meter
    value = 2.0*meter
    valueE = 0.25

    dim._length = scale
    self.assertEqual(valueE, dim.utonLength(value))
    return


  def test_ntouLength(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*meter
    valueE = 2.0*meter
    value = 0.25

    dim._length = scale
    self.assertEqual(valueE, dim.ntouLength(value))
    return


  def test_utonPressure(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*pascal
    value = 2.0*pascal
    valueE = 0.25

    dim._pressure = scale
    self.assertEqual(valueE, dim.utonPressure(value))
    return


  def test_ntouPressure(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*pascal
    valueE = 2.0*pascal
    value = 0.25

    dim._pressure = scale
    self.assertEqual(valueE, dim.ntouPressure(value))
    return


  def test_utonTime(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*second
    value = 2.0*second
    valueE = 0.25

    dim._time = scale
    self.assertEqual(valueE, dim.utonTime(value))
    return


  def test_ntouTime(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*second
    valueE = 2.0*second
    value = 0.25

    dim._time = scale
    self.assertEqual(valueE, dim.ntouTime(value))
    return


  def test_utonDensity(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*kilogram/meter**3
    value = 2.0*kilogram/meter**3
    valueE = 0.25

    dim._density = scale
    self.assertEqual(valueE, dim.utonDensity(value))
    return


  def test_ntouDensity(self):
    dim = NondimElastic()
    dim._configure()
    dim.initialize()

    scale = 8.0*kilogram/meter**3
    valueE = 2.0*kilogram/meter**3
    value = 0.25

    dim._density = scale
    self.assertEqual(valueE, dim.ntouDensity(value))
    return


# End of file 
