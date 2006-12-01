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

import numpy

lonlatNAD27ElevVals = numpy.array([
  [ -1.150000000000e+02,  3.900000000000e+01,  1.200000000000e+01],
  [ -1.203425320000e+02,  4.323423000000e+01,  1.010000000000e+01],
  [ -1.213425320000e+02,  4.523423000000e+01,  3.600000000000e+00],
  [ -1.153425320000e+02,  3.623423000000e+01,  7.200000000000e+00],
  [ -1.103425320000e+02,  3.923423000000e+01,  1.233000000000e+02],
  [ -1.073425320000e+02,  3.323423000000e+01,  3.460000000000e+01] ],
                                  numpy.float64)
xyzLocalVals = numpy.array([
  [ -1.284640403035e+06,  1.064304545254e+05, -1.314223692642e+05],
  [ -1.617989794934e+06,  6.524818198322e+05, -2.429529282853e+05],
  [ -1.637488936891e+06,  8.852730256818e+05, -2.774331803783e+05],
  [ -1.362847273202e+06, -1.913287267443e+05, -1.500646063011e+05],
  [ -8.881745585536e+05,  7.658679833419e+04, -6.239199171253e+04],
  [ -6.825105927499e+05, -6.111332573069e+05, -6.615476872030e+04] ],
                           numpy.float64)

class TestConvertApp(unittest.TestCase):

  def test_main(self):
    """
    Test main().
    """
    filename = "tmp.txt"

    from spatialdata.utils.PointsStream import PointsStream
    s = PointsStream()
    s.filename = filename
    s.fieldWidth = 20
    s.precision = 8
    
    s.write(lonlatNAD27ElevVals)

    from spatialdata.geocoords.CSGeo import CSGeo
    csNAD27 = CSGeo()
    csNAD27.ellipsoid = "clrk66"
    csNAD27.datumHoriz = "NAD27"
    csNAD27.datumVert = "mean sea level"

    from spatialdata.geocoords.CSGeoLocalCart import CSGeoLocalCart
    csLocal = CSGeoLocalCart()
    csLocal.originLon = -100.0
    csLocal.originLat = 39.0
    from pyre.units.length import m
    csLocal.originElev = 0.01*m
    csLocal.ellipsoid = "clrk66"
    csLocal.datumHoriz = "NAD27"
    csLocal.datumVert = "mean sea level"

    from spatialdata.utils.ChangeCoordSys import ChangeCoordSys
    converter = ChangeCoordSys()
    converter.csDest = csLocal
    converter.csSrc = csNAD27

    from spatialdata.utils.ConvertApp import ConvertApp
    app = ConvertApp()
    app.reader = PointsStream()
    app.reader.filename = filename
    app.writer = app.reader
    app.writer.fieldWidth = 20
    app.writer.precision = 8
    app.converter = converter
    app.main()

    points = s.read()
    self.assertEqual(len(xyzLocalVals.shape), len(points.shape))
    for dE,d in zip(xyzLocalVals.shape, points.shape):
      self.assertEqual(dE, d)
    for vE,v in zip(numpy.reshape(xyzLocalVals, -1),
                    numpy.reshape(points, -1)):
      self.assertAlmostEqual(1.0, vE/v, 6)
    return


# End of file 
