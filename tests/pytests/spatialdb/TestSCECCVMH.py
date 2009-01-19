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

class TestSCECCVMH(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.SCECCVMH import SCECCVMH
    db = SCECCVMH()
    db.inventory.dataDir = "/Users/brad/data/sceccvm-h/vx52/bin"
    db._configure()
    self._db = db
    return


  def test_query(self):
    locs = numpy.array( [[-118.520000,  34.120000,  -1400.00],
                         [-116.400000,  32.340000,  -1000.00]],
                        numpy.float64)
    from spatialdata.geocoords.CSGeo import CSGeo
    cs = CSGeo()
    cs.inventory.datumHoriz = "NAD27"
    cs.inventory.datumVert = "mean sea level"
    cs.inventory.ellipsoid = "clrk66"
    cs._configure()
    cs.initialize()
    queryVals = ["topo-elev", "moho-depth", "density"]
    dataE = numpy.array([[489.975189, -31178.105469,   2660.851074],
                         [801.209961, -34526.414062,   3022.192708]],
                        numpy.float64)
    errE = [0, 0]
    
    db = self._db
    db.open()
    db.queryVals(queryVals)
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = []
    nlocs = locs.shape[0]
    for i in xrange(nlocs):
      e = db.query(data[i,:], locs[i,:], cs)
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


  def test_querySquash(self):
    locs = numpy.array( [[-118.520000,  34.120000,  -1400.00-489.975189],
                         [-116.400000,  32.340000,  -1000.00-801.209961]],
                        numpy.float64)
    from spatialdata.geocoords.CSGeo import CSGeo
    cs = CSGeo()
    cs.inventory.datumHoriz = "NAD27"
    cs.inventory.datumVert = "mean sea level"
    cs.inventory.ellipsoid = "clrk66"
    cs._configure()
    cs.initialize()
    queryVals = ["topo-elev", "moho-depth", "density"]
    dataE = numpy.array([[489.975189, -31178.105469,   2660.851074],
                         [801.209961, -34526.414062,   3022.192708]],
                        numpy.float64)
    errE = [0, 0]
    
    db = self._db
    db.open()
    db.queryVals(queryVals)
    from pyre.units.length import km
    squashLimit = -2.5*km
    db.squash(True, squashLimit.value)
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = []
    nlocs = locs.shape[0]
    for i in xrange(nlocs):
      e = db.query(data[i,:], locs[i,:], cs)
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
