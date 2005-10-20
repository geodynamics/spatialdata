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

lonlatVals = [ [-1.203425320000e+02,  5.323423000000e+01],
               [-5.330394500000e+01,  3.334902000000e+01],
               [ 3.422908500000e+01, -2.523422000000e+01],
               [ 1.420845230000e+02, -3.439085000000e+01],
               [ 4.990854300000e+01,  2.409830000000e+00] ]
xyVals = [ [-6.277899090000e+03,  1.031520891000e+04],
           [-4.674048300000e+03,  4.847652140000e+03],
           [ 5.085303100000e+03, -1.214864990000e+03],
           [ 1.501732917000e+04,  1.114914645000e+04],
           [ 6.044641640000e+03,  1.856267650000e+03] ]

class TestProjector(unittest.TestCase):


  def setUp(self):
    from spatialdata.geocoords.CoordSysGeo import CoordSysGeo
    coordSys = CoordSysGeo()
    coordSys.initialize()
    
    from spatialdata.geocoords.Projector import Projector
    self.projector = Projector()
    
    self.projector.projection = "aea"
    self.projector.units = "km"
    self.projector.coordSys = coordSys
    return
  

  def test_initialize(self):
    self.projector.initialize()
    return


  def test_project(self):
    self.projector.initialize()
    xyValsT = self.projector.project(lonlatVals)
    self.assertEqual(len(xyVals), len(xyValsT))
    for (xy, xyT) in zip(xyVals, xyValsT):
      self.assertAlmostEqual(xy[0], xyT[0], 4)
      self.assertAlmostEqual(xy[1], xyT[1], 4)
    return

  def test_invproject(self):
    self.projector.initialize()
    lonlatValsT = self.projector.invproject(xyVals)
    self.assertEqual(len(lonlatVals), len(lonlatValsT))
    for (lonlat, lonlatT) in zip(lonlatVals, lonlatValsT):
      self.assertAlmostEqual(lonlat[0], lonlatT[0], 4)
      self.assertAlmostEqual(lonlat[1], lonlatT[1], 4)
    return

# version
__id__ = "$Id$"

# End of file 
