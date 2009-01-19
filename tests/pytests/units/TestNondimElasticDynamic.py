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

from spatialdata.units.NondimElasticDynamic import NondimElasticDynamic

from pyre.units.length import meter
from pyre.units.pressure import pascal
from pyre.units.time import second
from pyre.units.mass import kilogram    

class TestNondimElasticDynamic(unittest.TestCase):

  def test_constructor(self):
    dim = NondimElasticDynamic()
    dim._configure()

    vs = 3.0e+3*meter/second
    density = 3.0e+3*kilogram/meter**3
    period = 1.0*second

    shearModulus = density*vs**2
    wavelength = vs*period

    self.assertEqual(wavelength, dim.lengthScale())
    self.assertEqual(shearModulus, dim.pressureScale())
    self.assertEqual(period, dim.timeScale())
    self.assertEqual(density, dim.densityScale())

    return


# End of file 
