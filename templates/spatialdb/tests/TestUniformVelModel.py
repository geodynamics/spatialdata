#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================
#

import unittest

import numpy

class TestUniformVelModel(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.contrib.UniformVelModel import UniformVelModel
    db = UniformVelModel()
    db.inventory.label = "Uniform properties"
    db._configure()
    self._db = db

    from spatialdata.geocoords.CSGeo import CSGeo
    csQ = CSGeo()
    csQ.inventory.datumHoriz = "NAD27"
    csQ.inventory.datumVert = "mean sea level"
    csQ.inventory.ellipsoid = "clrk66"
    csQ._configure()
    csQ.initialize()
    self._csQ = csQ
    return


  def test_queryVp(self):
    locs = numpy.array( [[-118.520000,  34.120000,  -1400.00],
                         [-116.400000,  32.340000,  -1000.00]],
                        numpy.float64)
    queryVals = ["vp"]
    dataE = numpy.array([[4.5e+3],
                         [4.5e+3]],
                        numpy.float64)
    errE = [0, 0]
    
    db = self._db
    db.open()
    db.queryVals(queryVals)
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = []
    nlocs = locs.shape[0]
    for i in range(nlocs):
      e = db.query(data[i,:], locs[i,:], self._csQ)
      err.append(e)
    db.close()    

    self.assertEqual(len(errE), len(err))
    for vE, v in zip(errE, err):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)
    return


  def test_query(self):
    locs = numpy.array( [[-118.520000,  34.120000,  -1400.00],
                         [-116.400000,  32.340000,  -1000.00]],
                        numpy.float64)
    queryVals = ["density", "vs"]
    dataE = numpy.array([[2.5e+3, 2.6e+3],
                         [2.5e+3, 2.6e+3]],
                        numpy.float64)
    errE = [0, 0]
    
    db = self._db
    db.open()
    db.queryVals(queryVals)
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = []
    nlocs = locs.shape[0]
    for i in range(nlocs):
      e = db.query(data[i,:], locs[i,:], self._csQ)
      err.append(e)
    db.close()    

    self.assertEqual(len(errE), len(err))
    for vE, v in zip(errE, err):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)
    return


# End of file 
