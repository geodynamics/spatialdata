#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

from spatialdata.units.NondimElasticQuasistatic import NondimElasticQuasistatic

from pyre.units.length import meter
from pyre.units.pressure import pascal
from pyre.units.time import year
from pyre.units.mass import kilogram    

class TestNondimElasticQuasistatic(unittest.TestCase):

  def test_constructor(self):
    dim = NondimElasticQuasistatic()
    dim._configure()

    self.assertEqual(1.0e+3*meter, dim.lengthScale())
    self.assertEqual(3.0e+10*pascal, dim.pressureScale())
    self.assertEqual(1.0*year, dim.timeScale())

    vs = (1.0e+3*meter) / (1.0*year)
    rho = (3.0e+10*pascal) / (vs**2)
    self.assertEqual(rho, dim.densityScale())

    return


# End of file 
