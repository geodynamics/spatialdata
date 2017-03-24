#!/usr/bin/env python
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
import numpy

projection = "aea"
units = "km"
projOptions = "+lon_0=-100.0 +lat_0=30.0 +k=0.9996"
lonlatVals = numpy.array([ [-1.203425320000e+02,  5.323423000000e+01],
                           [-5.330394500000e+01,  3.334902000000e+01],
                           [ 3.422908500000e+01, -2.523422000000e+01],
                           [ 1.420845230000e+02, -3.439085000000e+01],
                           [ 4.990854300000e+01,  2.409830000000e+00] ],
                         dtype=numpy.float64)
xyVals = numpy.array([ [ -1.397886620000e+03,  2.729173050000e+03],
                       [  4.145823900000e+03,  1.412439200000e+03],
                       [  1.424820130000e+04,  6.884278430000e+03],
                       [ -1.424775469000e+04,  4.279122720000e+03],
                       [  1.205623096000e+04,  9.239581410000e+03] ],
                     dtype=numpy.float64)

class TestProjector(unittest.TestCase):


  def setUp(self):
    from spatialdata.geocoords.CSGeo import CSGeo
    cs = CSGeo()
    cs._configure()
    cs.initialize()
    self.cs = cs
    
    from spatialdata.geocoords.Projector import Projector
    projector = Projector()
    projector.inventory.projection = projection
    projector.inventory.units = units
    projector.inventory.projOptions = projOptions
    projector._configure()
    self.projector = projector
    return
  

  def test_initialize(self):
    self.projector.initialize(self.cs)

    proj = self.projector
    self.assertEqual(projection, proj.projection())
    self.assertEqual(units, proj.units())
    self.assertEqual(projOptions, proj.projOptions())

    return


# End of file 
