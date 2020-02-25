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

lonlatNAD27 = numpy.array([
    [3.900000000000e+01, -1.150000000000e+02],
    [4.323423000000e+01, -1.203425320000e+02],
    [4.523423000000e+01, -1.213425320000e+02],
    [3.623423000000e+01, -1.153425320000e+02],
    [3.923423000000e+01, -1.103425320000e+02],
    [3.323423000000e+01, -1.073425320000e+02]],
    numpy.float64)
lonlatWGS84 = numpy.array([
    [38.99994227694298, -115.00085076334376],
    [43.234128917800746, -120.34362083668957],
    [45.23410304341094, -121.34368736399294],
    [36.234196301769245, -115.3433730158481],
    [39.23419970865653, -110.34324423951884],
    [33.23430190357505, -107.34312119874491]],
    numpy.float64)

xyKm = numpy.array([
    [1.01, 2.02],
    [2.02, 3.02]],
    numpy.float64)


class TestConverter(unittest.TestCase):

    def test_geo(self):
        from spatialdata.geocoords.CSGeo import CSGeo
        csNAD27 = CSGeo()
        csNAD27.inventory.specification = "EPSG:4267"
        csNAD27.inventory.spaceDim = 2
        csNAD27._configure()

        csWGS84 = CSGeo()
        csWGS84.inventory.specification = "EPSG:4326"
        csWGS84.inventory.spaceDim = 2
        csWGS84._configure()

        from spatialdata.geocoords.Converter import convert
        lonlat = numpy.array(lonlatNAD27)
        convert(lonlat, csWGS84, csNAD27)

        self.assertEqual(len(lonlatWGS84.shape), len(lonlat.shape))
        for (ll, llT) in zip(numpy.reshape(lonlatWGS84, -1),
                             numpy.reshape(lonlat, -1)):
            self.assertAlmostEqual(ll, llT, 4)

    def test_cart(self):
        from spatialdata.geocoords.CSCart import CSCart
        csKm = CSCart()
        csKm.inventory.units = "km"
        csKm.inventory.spaceDim = 2
        csKm._configure()

        csM = CSCart()
        csM.inventory.units = "m"
        csM.inventory.spaceDim = 2
        csM._configure()

        from spatialdata.geocoords.Converter import convert
        xy = numpy.array(xyKm)
        convert(xy, csM, csKm)

        xyM = xyKm * 1.0e+3
        self.assertEqual(len(xyM.shape), len(xy.shape))
        for (xyE, xyT) in zip(numpy.reshape(xyM, -1),
                              numpy.reshape(xy, -1)):
            self.assertAlmostEqual(xyE, xyT, 4)


# End of file
